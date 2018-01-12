#include "ServoMotor.h"

ServoMotor sm(D0,D1);

void setup()
{
  Serial.begin(115200);
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
    Serial.println("Start UP");
    sm.startLiftUp();
  }
  else if(input == '2')
  {
    Serial.println("Start DOWN");
    sm.startLiftDown();
  }
  else if(input == '3')
  {
    Serial.println("0 Degree");
    sm.changeDegree(0);
  }
  else if(input == '4')
  {
    Serial.println("90 Degree");
    sm.changeDegree(90);
  }
  else if(input == '5')
  {
    Serial.println("180 Degree");
    sm.changeDegree(180);
  }
  else if(input == '6')
  {
    Serial.println("OpenFood servo1");
    sm.openFood(1);
  }
  else if(input == '7')
  {
    Serial.println("OpenFood servo2");
    sm.openFood(2);
  }
  else if(input == '8')
  {
    Serial.println("CloseFood servo1");
    sm.closeFood(1);
  }
  else if(input == '9')
  {
    Serial.println("CloseFood servo2");
    sm.closeFood(2);
  }
}
