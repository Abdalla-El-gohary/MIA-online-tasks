// C++ code
#include <Wire.h>
int motorPinClk =5;
int motorPinAntiClk =6;
void setup()
{
  Wire.begin();
  pinMode(motorPinClk,OUTPUT);
  pinMode(motorPinAntiClk,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int t;//to detect the temperature
  int m;//te detect the moisture
  Wire.requestFrom(9,1);
  while(Wire.available()){
    t=Wire.read();
  }
  if(Serial.available()>0){
    m=Serial.parseInt();
    
  }
  if(t>40){
    digitalWrite(motorPinAntiClk,HIGH);
    digitalWrite(motorPinClk,LOW);
  }
  else if(t<20){
    
    digitalWrite(motorPinClk,HIGH);
    digitalWrite(motorPinAntiClk,LOW);
  }
  else{
    digitalWrite(motorPinClk,LOW);
    digitalWrite(motorPinAntiClk,LOW);
  }
  Serial.print(t);
  Serial.print(",");
  Serial.print(m);
  delay(500);
  
}
