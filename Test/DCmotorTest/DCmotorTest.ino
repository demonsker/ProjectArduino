#include "DCmotor.h"

DCmotor dc(D0,D1,D2,D3);

char input;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  
  if(Serial.available())
  {
    input = Serial.read();
    Serial.println(input);
  }

  if(input == '0')  //Stop All Motor
  {
    dc.stopMotorA();
    dc.stopMotorB();
  }
  else if(input == '1') //MotorA forward only
    {
      dc.stopMotorB();
      dc.startMotorA(1);
    }
  else if(input == '2') //MotorA backward only
  {
      dc.stopMotorB();
      dc.startMotorA(0);
  }
  else if(input == '3') //MotorB forward only
  {
      dc.stopMotorA();
      dc.startMotorB(1);
  }
  else if(input == '4') //MotorB backward only
  {
      dc.stopMotorA();
      dc.startMotorB(0);
  }
  else if(input == '5') //MotorA and MotorB forward
  {
      dc.startMotorA(1);
      dc.startMotorB(0);
      
  }
  else if(input == '6') //MotorA and MotorB backward
  {
      dc.startMotorA(0);
      dc.startMotorB(1);
          
  }
}

