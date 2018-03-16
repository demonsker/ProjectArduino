#include "UltraSonic.h"
#include "DCmotor.h"
#include "NETPIE.h"
#include <Servo.h>

#define speed 1023
Servo sm1;
Servo sm2;
DCmotor dc(D3,D4,D3,D4);
UltraSonic uls(D8,D9);
NETPIE netPie("HappyPigsty","zw0HnvDcL9VY4qA","BDiOw4Twn98leHH6ATHDkV7fD");

void setup()
{
    Serial.begin(115200);
    dc.setSpeed(speed);
    sm1.attach(D5);
    sm2.attach(D6);

    
    sm1.write(0);
    sm2.write(180);
    /*netPie.getMicrogear().on(MESSAGE,ReceiveMessage);
    netPie.setAlias("Board");
    netPie.setWIFI("Your ASUS", "0874847756");
    netPie.connectWIFI();
    netPie.connect();*/
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

void ReceiveMessage(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Receive message : ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
    startWeight(1);
}

void startWeight(int type)
{
    int delay_time;

    if(type == 1)
        delay_time = 1000;        
    else if(type == 2) 
        delay_time = 1500;       
        
    dc.startMotorA(1);
    dc.startMotorB(1);
    
    delay(delay_time);

    dc.stopMotorA();
    dc.stopMotorB();
    sm1.write(180);
    sm2.write(0);

    delay(3000);

    sm1.write(0);
    sm2.write(180);
    
    dc.startMotorA(0);
    dc.startMotorB(0);    

    delay(delay_time);
    
    dc.stopMotorA();
    dc.stopMotorB(); 
}
