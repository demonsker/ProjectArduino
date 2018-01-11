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
    delay(3000);
    Serial.println("Start DOWN");
    sm.startLiftDown();
    
    input = '0';
  }

}

