// C++ code
#include <Wire.h>
int temperatueRead = 0;
int temperatureWrite = 5;
int temperature=0;

void setup()
{
  pinMode(temperatueRead,INPUT);
  pinMode(temperatureWrite,OUTPUT);
  Serial.begin(9600);
  Wire.begin(9);
  Wire.onRequest(sendData);
}

void loop()
{
  //int temp=analogRead(temperatueRead);
  //int temperature=map(temp,20,358,0,100);
  ///analogWrite(temperature,temperatureWrite);
  //Serial.println(temperature);
  delay(1000); // Wait for 1000 millisecond(s)
}
void sendData(){//function to send data
  int temp=analogRead(temperatueRead);
  int temperature=map(temp,20,358,0,100);
  Wire.write(temperature);
}
