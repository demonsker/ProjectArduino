#include <Servo.h>

Servo servo1;
Servo servo2;

void setup()
{
  Serial.begin(115200);
  servo1.attach(D5);
  servo2.attach(D6);

  servo1.write(0);
  servo2.write(180);
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
    servo1.write(0);
    servo2.write(180);
  }
  else if(input == '2')
  {
    Serial.println("90 Degree");
    servo1.write(90);
    servo2.write(90);
  }
  else if(input == '3')
  {
    Serial.println("180 Degree");
    servo1.write(180);
    servo2.write(0);
  }
}
