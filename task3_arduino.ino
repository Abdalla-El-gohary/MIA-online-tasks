#include "Event.h"
#include "Timer.h"
Timer myTimer;
long resoulation= 2400;   //resoulation of encoder

int counter_1=0;  //for motor A and its encoder
int counter_2=0;  //for motor B and its encoder

//Arduino mega
const byte pinEncoder_1 =2;
const byte pinEncoder_2 =3;   //1,2 for encoder 1

const byte pinEncoder_3 =18;
const byte pinEncoder_4 =19;   //3,4 for encoder 2


const byte switchPin =4;      // we use a switch to decide the desired angle


//L293D pin
byte input_1 =13;  //input 1,2 and enable 1 for motor A
byte input_2 =12;
byte input_3 =9;     //input 3,4 and enable 2 for motor B
byte input_4 =8;
byte enable_1 =11;
byte enable_2 =10;




void encoder_1(void){   //for pin 1 for encoder 1
    if(digitalRead(pinEncoder_1) != digitalRead(pinEncoder_2)){
        counter_1++;
      }
     else{
        counter_1--;
      }
  }

void encoder_2(void){     //for pin 2 for encoder 1
    if(digitalRead(pinEncoder_1) == digitalRead(pinEncoder_2)){
        counter_1++;
      }
     else{
        counter_1--;
      }
  }


void encoder_3(void){  //for pin 1 for encoder 2
    if(digitalRead(pinEncoder_3) != digitalRead(pinEncoder_4)){
        counter_2++;
      }
     else{
        counter_2--;
      }
  }

void encoder_4(void){  //for pin 2 for encoder 2
    if(digitalRead(pinEncoder_3) == digitalRead(pinEncoder_4)){
        counter_2++;
      }
     else{
        counter_2--;
      }
  }

void setup() {
  pinMode(switchPin,INPUT);

  //Encoder_1
  pinMode(pinEncoder_1,INPUT_PULLUP);
  pinMode(pinEncoder_2,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinEncoder_1),encoder_1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinEncoder_2),encoder_2,CHANGE);
  //Encoder_2
  pinMode(pinEncoder_3,INPUT_PULLUP);
  pinMode(pinEncoder_4,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinEncoder_3),encoder_3,CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinEncoder_4),encoder_4,CHANGE);
  

  myTimer.every(100,blink);  //blink is a function that check the conditon of the switch state every 100 millisecond and rotate motor

}

void loop() {
  myTimer.update();

}
void blink(void){  
    if(digitalRead(switchPin)==LOW){    //if switch off, arm 1 should stop at 60 degree and arm 2 should stop ar 0 degree
        if(counter_1 <resoulation/6){   //rotate clockwise
            digitalWrite(enable_1,HIGH);
            digitalWrite(input_1,HIGH);
            digitalWrite(input_2,LOW);
        }
        else if(counter_1 >resoulation/6){   //rotate counterclockwise
            digitalWrite(enable_1,HIGH);
            digitalWrite(input_1,LOW);
            digitalWrite(input_2,HIGH);
        }
        else{  // we want to stop motor A at 60 degree so we will check the counter and when it become 2400/6=400 we will stop it
            digitalWrite(enable_1,LOW);
            digitalWrite(input_1,LOW);
            digitalWrite(input_2,LOW);
        } 


        if(counter_2==0){
            digitalWrite(enable_2,LOW);
            digitalWrite(input_3,LOW);
            digitalWrite(input_4,LOW);
        } 
        else if(counter_2>0){           //rotate counterclockwise
            digitalWrite(enable_2,HIGH);
            digitalWrite(input_3,LOW);
            digitalWrite(input_4,HIGH);
        } 
        else if(counter_2<0){             //rotate clockwise
            digitalWrite(enable_2,HIGH);
            digitalWrite(input_3,HIGH);
            digitalWrite(input_4,LOW);
        }
        
    }
    else{    // the switch is 1 state
        if(counter_1 <resoulation/6){   //rotate clockwise
            digitalWrite(enable_1,HIGH);
            digitalWrite(input_1,HIGH);
            digitalWrite(input_2,LOW);
        }
        else if(counter_1 >resoulation/6){   //rotate counterclockwise
            digitalWrite(enable_1,HIGH);
            digitalWrite(input_1,LOW);
            digitalWrite(input_2,HIGH);
        }
        else{  // we want to stop motor A at 60 degree so we will check the counter and when it become 2400/6=400 we will stop it
            digitalWrite(enable_1,LOW);
            digitalWrite(input_1,LOW);
            digitalWrite(input_2,LOW);
        }

        
        if(counter_2 <resoulation/4){
            digitalWrite(enable_2,HIGH);
            digitalWrite(input_3,HIGH);
            digitalWrite(input_4,LOW);
        }
        else if(counter_2 > resoulation/4){
            digitalWrite(enable_2,HIGH);
            digitalWrite(input_3,LOW);
            digitalWrite(input_4,HIGH); 
        }
        else{     // it means that the arm is 90 degree already
            digitalWrite(enable_2,LOW);
            digitalWrite(input_3,LOW);
            digitalWrite(input_4,LOW);
        }
  }
}
