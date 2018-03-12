#include "DCmotor.h"
#define speed 800

DCmotor dc(D3,D4,D3,D4);

char input;

void setup()
{
  Serial.begin(115200);
  dc.setSpeed(speed);
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
      dc.startMotorB(1);
      
  }
  else if(input == '6') //MotorA and MotorB backward
  {
      dc.startMotorA(0);
      dc.startMotorB(0);
          
  }
  else if(input == '7') //MotorA forward and MotorB backward
  {
      dc.startMotorA(1);
      dc.startMotorB(0);
          
  }
  else if(input == '8') //MotorA backward and MotorB forward
  {
      dc.startMotorA(0);
      dc.startMotorB(1);
          
  }
}

