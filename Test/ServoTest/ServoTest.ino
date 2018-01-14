#include <Servo.h>

Servo servo;

void setup()
{
  Serial.begin(115200);
  servo.attach(8);
}

void loop()
{ 
  char input;

  if(Serial.available())
  {
    input = Serial.read();
    Serial.println(input);
  } 
  
  if(input == '1')
  {
    Serial.println("0 Degree");
    servo.write(0);
  }
  else if(input == '2')
  {
    Serial.println("90 Degree");
    servo.write(90);
  }
  else if(input == '3')
  {
    Serial.println("180 Degree");
    servo.write(180);
  }
}
