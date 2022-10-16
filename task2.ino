#include <ros.h>
#include <std_msgs/Int16.h>

#define PIN_A PB12
#define PIN_B PB13


ros::NodeHandle nh;
std_msgs::Int16 counts;
ros::Publisher chatter("chatter", &counts);



int counter =0;  //for motor A and its encoder
void setup() {
  nh.initNode();
  nh.advertise(chatter); 
  attachInterrupt(digitalPinToInterrupt(PIN_A),  encoder_1,       CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_B),  encoder_2,       CHANGE);
  // put your setup code here, to run once:

}

void loop() {
  counts.data = counter;
  chatter.publish(&counts);
            nh.spinOnce();
            delay(1000);

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