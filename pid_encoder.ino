#include <ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>
#include "pid.h"

#define PIN_A PB12
#define PIN_B PB13

#define pwm PB14
#define dir PB15

HardwareSerial Serial3(PA10,PA9);

long long int motorSpeed;    //current speed of motor
long long int outputSpeed;  //speed of motor after pid
unsigned long currentTime;
unsigned long lastTime=0;

float desigredSpeed=0; //get it from the topic
pid mypid(0);  //object of the class with setpoint 0

void message(const std_msgs::Float32 &msg){ //function of subscriber node to get setpoint
      desigredSpeed=msg.data;
}

ros::NodeHandle nh;
std_msgs::Int32 counts;
ros::Publisher chatter("chatter", &counts);  //publisher of counter
ros::Subscriber<std_msgs::Float32> sub("speed",&message);  //subscriber



long long int counter =0;  //for motor A and its encoder

void setup() {
  Serial3.begin(115200);
  (nh.getHardware())->setPort(&Serial3);
  (nh.getHardware())->setBaud(115200);
  
  nh.initNode();
  nh.advertise(chatter); 
  nh.subscribe(sub);
  
  attachInterrupt(PIN_A,  encoder_1,       CHANGE);
  attachInterrupt(PIN_B,  encoder_2,       CHANGE);
  
  currentTime=millis();
  lastTime=millis();
  
  mypid.setPIDParameters(12.0,20.0,0.8);  //set kp ,ki and kd
  mypid.setStartTime(currentTime);    //set start time
}  

void loop() {
  counts.data = counter;
  chatter.publish(&counts);
  nh.spinOnce();

  mypid.setPoint(desigredSpeed);
  currentTime=millis();
  motorSpeed=measureSpeed();  //we measure rpm (per minute)
  outputSpeed=mypid.compute(currentTime,motorSpeed);  //calculate the outputspeed of motor

  
  if(outputSpeed>=0){
      analogWrite(pwm,outputSpeed);
      digitalWrite(dir,HIGH);  //forward direction
    }
    else{
      analogWrite(pwm,abs(outputSpeed));
      digitalWrite(dir,LOW); //reverse direction
      }
}



void encoder_1(void){   //for pin 1 for encoder 1
    if(digitalRead(PIN_A) != digitalRead(PIN_B)){
        counter++;
      }
     else{
        counter--;
      }
  }

void encoder_2(void){     //for pin 2 for encoder 1
    if(digitalRead(PIN_A) == digitalRead(PIN_B)){
        counter++;
      }
     else{
        counter--;
      }
  }
long long int measureSpeed(){  //measure rpm
    long long int rpm =(counter/2400)/((currentTime-lastTime)/60000);
    lastTime=currentTime;
    return rpm;
  }
