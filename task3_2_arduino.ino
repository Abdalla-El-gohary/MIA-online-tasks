#include <Event.h>
#include <Timer.h>
#include <Wire.h>
Timer time;


#define imu_address 0x68 
#define GYRO_ZOUT_H 0x47 
#define GYRO_ZOUT_L 0x48 



int16_t GyroX, GyroY, GyroZ;   //store at it the reading of the angular velocity at x,y and z
int16_t roll=0, pitch=0, yaw=0;                    
int16_t GyroErrorX=0, GyroErrorY=0, GyroErrorZ=0;      // store the error of Gyroscope (calibration)
long long elapsedTime, currentTime, previousTime=0;  //time varibles


void setup(){
    Wire.begin();           //TO BEGIN I2C COMMUNICATIONS
    Wire.beginTransmission(imu_address);   //start communiction wwith IMU sensor
    Wire.write(0x6B);
    Wire.write(0x00);
    Wire.endTransmission(true);
    Serial.begin(9600);      //To print on serial monitor
    calculate_IMU_error();    //to detect error of gyroscope before starting
    time.every(100,getAngle);//calculate the angles x,y and z every 100 ms

}
void getAngle(){   //Function that Read gyroscope data and calculate angels of x,y and z using integration
  
    Wire.beginTransmission(imu_address);
    Wire.write(0x43); // Gyro data first register address 0x43
    Wire.endTransmission(false);
    Wire.requestFrom(imu_address, 6, true); // Read 4 registers total, each axis value is stored in 2 registers

    
    while(Wire.available()!=6);       //To make sure that the 6 bytes were sent successfully
    GyroX = (Wire.read() << 8 | Wire.read()) / 131; // For a 250deg/s range we have to divide first the raw value by 131, according to the datasheet  32768/250=131
    GyroY = (Wire.read() << 8 | Wire.read()) / 131;
    GyroZ = (Wire.read() << 8 | Wire.read()) / 131;

    
    // Correct the outputs with the calculated error values
    GyroX = GyroX - GyroErrorX ; // GyroErrorX 
    GyroY = GyroY - GyroErrorY; // GyroErrorY 
    GyroZ = GyroZ - GyroErrorZ; // GyroErrorZ 

    
    currentTime = millis();           
    elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
    
    //Integration to get the angles
    roll = roll + GyroX * elapsedTime;      // deg/s * s = deg
    pitch = pitch + GyroY * elapsedTime;    
    yaw =  yaw + GyroZ * elapsedTime;
   
    
    
    Serial.println(yaw);   // Print the value of Yaw angle on the serial monitor
    previousTime = currentTime; // update the previous time
  
  }
void loop(){
    time.update();
}








void calculate_IMU_error(void) {  //fuction to calibrate the geroscope
  int c = 0;
  // Read gyro values 200 times
  while (c < 200) {
    Wire.beginTransmission(imu_address);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(imu_address, 6, true);
    while(Wire.available()!=6);
    GyroX = Wire.read() << 8 | Wire.read();
    GyroY = Wire.read() << 8 | Wire.read();
    GyroZ = Wire.read() << 8 | Wire.read();
    // Sum all readings
    GyroErrorX = GyroErrorX + (GyroX / 131.0);
    GyroErrorY = GyroErrorY + (GyroY / 131.0);
    GyroErrorZ = GyroErrorZ + (GyroZ / 131.0);
    c++;
  }
  //Divide the sum by 200 to get the error value
  GyroErrorX = GyroErrorX / 200;
  GyroErrorY = GyroErrorY / 200;
  GyroErrorZ = GyroErrorZ / 200;
}
