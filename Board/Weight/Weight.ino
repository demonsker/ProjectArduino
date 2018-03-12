#include "UltraSonic.h"
#include "DCmotor.h"
#include <Servo.h>

#define speed 800
Servo sm1;
Servo sm2;
DCmotor dc(D3,D4,D3,D4);
UltraSonic uls(D8,D9);

void setup()
{
    Serial.begin(115200);
    dc.setSpeed(speed);
    sm1.attach(D5);
    sm2.attach(D6);

    
    sm1.write(0);
    sm2.write(180);
}

void loop()
{   
  char input = '0';

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
        stop = 30;
    else if(type == 2) 
        stop = 45;

    distance = uls.readDistance();
    Serial.println(distance);

    dc.startMotorA(1);
    dc.startMotorB(1);
   
    while(distance < stop)
    {   
        distance = uls.readDistance();
        Serial.println(distance);
    }

    dc.stopMotorA();
    dc.stopMotorB();
    sm1.write(180);
    sm2.write(0);

    delay(3500);

    sm1.write(0);
    sm2.write(180);
    dc.startMotorA(0);
    dc.startMotorB(0);    

    while(distance > 5)
    {
        distance = uls.readDistance();
        Serial.println(distance);
    }
    
    dc.stopMotorA();
    dc.stopMotorB(); 
}
