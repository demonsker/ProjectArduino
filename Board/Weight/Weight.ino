#include "UltraSonic.h"
#include "DCmotor.h"
#include "ServoMotor.h"

UltraSonic uls(D0,D1);
DCmotor dc(D2,D3,D4,D5);
ServoMotor sm(D6,D7);

void setup()
{
    Serial.begin(115200);
}

void loop()
{   
    double distance = uls.readDistance();
    Serial.println(distance);

    if(distance < 20)
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
      //Start read weight
      delay(5000);
      sm.startLiftDown();
      dc.startMotorA(0);
      dc.startMotorB(1);
}

