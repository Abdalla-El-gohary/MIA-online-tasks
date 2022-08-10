// C++ code
//
int moisture=1;
int moistureLevel;
void setup()
{
  Serial.begin(9600);
  pinMode(moisture, INPUT);
}

void loop()
{
  moistureLevel=analogRead(moisture);
  
  Serial.println(moistureLevel);
  Serial.write(moistureLevel);//send data tp mc3
  delay(500);
}
