#include "UltraSonic.h"
#include "DCmotor.h"
#include "ServoMotor.h"
#include "LoadCell.h"

ServoMotor sm(D6,D7);
DCmotor dc(D0,D1,D2,D3);
UltraSonic uls(D5,D4);
LoadCell lc(D0);

void setup()
{
    Serial.begin(115200);
}

void loop()
{   
    double distance = uls.readDistance();
    Serial.println(distance);

    if(distance > 0 && distance < 20)
    {
      startWeight();
    }
    
}

void startWeight()
{
      dc.startMotorA(1);
      dc.startMotorB(0);
      delay(1000);
      dc.stopMotorA();
      dc.stopMotorB();
      sm.startLiftUp();

      lc.readWeight();
      delay(5000);
      
      sm.startLiftDown();
      dc.startMotorA(0);
      dc.startMotorB(1);
      delay(1000);
      dc.stopMotorA();
      dc.stopMotorB();
}

