#include "UltraSonic.h"
#include "DCmotor.h"
#include "LoadCell.h"
#include <Servo.h>

Servo sm1;
Servo sm2;
DCmotor dc(2,3,4,5);
UltraSonic uls(6,7);
LoadCell lc(0);

void setup()
{
    Serial.begin(115200);
    sm1.attach(8);
    sm2.attach(9);
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
    startWeight(1);
  else if(input == '2')
    startWeight(2);
  
}

void startWeight(int type)
{
    int stop;
    double distance;

    if(type == 1)
        stop = 40;
    else if(type == 2) 
        stop = 20;

    distance = uls.readDistance();
    
    dc.startMotorA(1);
    dc.startMotorB(0);

    while(distance > stop)
    {
        distance = uls.readDistance();
        Serial.println(distance);
    }

    dc.stopMotorA();
    dc.stopMotorB();
    sm1.write(180);
    sm2.write(180);

    delay(5000);

    sm1.write(0);
    sm2.write(0);
    dc.startMotorA(0);
    dc.startMotorB(1);    

    while(distance < 60)
    {
        distance = uls.readDistance();
        Serial.println(distance);
    }
    
    dc.stopMotorA();
    dc.stopMotorB();
}
