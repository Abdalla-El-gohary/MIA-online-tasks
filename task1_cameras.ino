#include <Event.h>
#include <Timer.h>
#include <Wire.h>
Timer time;


#define imu_address 0x68 
#define GYRO_ZOUT_H 0x47  
#define GYRO_ZOUT_L 0x48 

#define dir 7   //pin of cytron motor driver for control direction of motor
#define pwm 6    //pin of cytron motor driver to contrl the speed of motor


float GyroX, GyroY, GyroZ;   //store at it the reading of the angular velocity at x,y and z
float roll=0, pitch=0, yaw=0;  //Angels of 3-axis   // roll and pitch for any future modifications in the system                  
float GyroErrorX=0, GyroErrorY=0, GyroErrorZ=0;      // store the error of Gyroscope (calibration)
unsigned long elapsedTime, currentTime, previousTime=0;  //time variables for gyro


unsigned long  current_time, previous_time=0;  //time variables for pid controller
float target_angle;//The angle we want to reach
float kp=4.6; //the values of kp, ki, and kd may be edited (we should test the program in reality
float ki=2.2;
float kd=0.8;
double error_sum=0,last_error=0; 
long int pid_output=0;

void setup(){
    pinMode(pwm,OUTPUT);
    pinMode(dir,OUTPUT);
    Wire.begin();           //TO BEGIN I2C COMMUNICATIONS
    Wire.beginTransmission(imu_address);   //start communiction wwith IMU sensor
    Wire.write(0x6B);    //GYRO configuration
    Wire.write(0x00);
    Wire.endTransmission(true);
    Serial.begin(9600);      //To print on serial monitor
    calculate_IMU_error();    //to detect error of gyroscope before starting
    previousTime=millis();//start time of gyro
    time.every(100,getAngle);//calculate the angles x,y and z every 100 ms
    previous_time=millis();//start time of pid
    time.every(100,pid_controller);  //control system to calculate the output that the motors should take

}

void loop(){
    time.update();
    if(Serial.available()){     //check if there is a data sent to the serial monitor
       target_angle=Serial.parseFloat();    //we used parsefloat to able able to read float values from serial monitor
    }
    //Serial.println(pid_output);
    if(pid_output >255 || pid_output <-255){
        if(pid_output >255){
            digitalWrite(dir,HIGH);   // rotate the cameras clockwise with maximum speed
            analogWrite(pwm,255);
          }
          else{
             digitalWrite(dir,LOW); // rotate the cameras counter_clockwise with maximum speed
             analogWrite(pwm,255);
            }
      }
      else if(pid_output >=0){
            digitalWrite(dir,HIGH);   // rotate the cameras clockwise with needed speed
            analogWrite(pwm,abs(pid_output));
      }
      else{
            digitalWrite(dir,LOW);   // rotate the cameras counter_clockwise with needed speed
            analogWrite(pwm,abs(pid_output));
        }
    
    
    
}

void getAngle(){   //Function that Read gyroscope data and calculate angels of x,y and z using integration
  
    Wire.beginTransmission(imu_address);
    Wire.write(0x43); // Gyro data first register address 0x43
    Wire.endTransmission(false);
    Wire.requestFrom(imu_address, 6, true); // Read 4 registers total, each axis value is stored in 2 registers

    
    while(Wire.available()!=6);       //To make sure that the 6 bytes were sent successfully
    GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // For a 250deg/s range we have to divide first the raw value by 131, according to the datasheet  32768/250=131
    GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
    GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;

    
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
   
    
    
    //Serial.println(yaw);   // Print the value of Yaw angle on the serial monitor
    previousTime = currentTime; // update the previous time
  
  }






void calculate_IMU_error(void) {  //fuction to calibrate the geroscope
  int c = 0;
  // Read gyro values 200 times
  while (c < 3000) {
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
  //Divide the sum by 3000 to get the error value
  GyroErrorX = GyroErrorX / 3000;
  GyroErrorY = GyroErrorY / 3000;
  GyroErrorZ = GyroErrorZ / 3000;
}

void pid_controller(){
    current_time=millis();
    double error = target_angle - yaw;
    error_sum+= error *(current_time - previous_time);
    double slope_error = (error - last_error)/(current_time - previous_time);
    pid_output =kp * error + ki *error_sum + kd *slope_error;
    previous_time = current_time;
    last_error = error;
  }
