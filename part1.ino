// C++ code

int moisurepower = 0;
int moisurepin = 1;
int forcepin = 2;
int moisureRead;
int forceRead;
int motorPin = 11;
int ledPin = 10;
int pushButton = 2;
int counter=0;
int fillTank = 4;
int secondMotor =5;
int time;
void count(){
 counter++;
}
void turnMotor(){
  for(int i=0;i<10000;i++){
  digitalWrite(secondMotor,HIGH);
  }
}
void setup()
{
  pinMode(moisurepower,OUTPUT);
  pinMode(moisurepin,INPUT);
  pinMode(forcepin,INPUT);
  pinMode(motorPin,OUTPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(pushButton,INPUT_PULLUP);
  pinMode(fillTank,INPUT);
  pinMode(secondMotor,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pushButton),count,CHANGE);
  Serial.begin(9600);
  //pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(A0,HIGH);
  moisureRead = analogRead(moisurepin);
  int reverseMoisure = map(moisureRead,0,876,255,0);
  forceRead = analogRead(forcepin);
  int reverseForce = map(forceRead,0,914,255,0);
  analogWrite(motorPin,reverseMoisure);
  analogWrite(ledPin,reverseForce);
  Serial.println(counter);
  digitalWrite(secondMotor,LOW);
  int check = digitalRead(fillTank);
  int on=0;
  if(check == HIGH){
      digitalWrite(secondMotor,HIGH);
    delay(10000);
  }
  delay(1000);
}
