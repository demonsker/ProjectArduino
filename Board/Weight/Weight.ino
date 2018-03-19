#include "UltraSonic.h"
#include "DCmotor.h"
#include "NETPIE.h"
#include "HX711.h"
#include <Servo.h>

#define speed 1023
#define calibration_factor 49456
Servo sm1, sm2;
DCmotor dc(D3,D4,D3,D4);
UltraSonic uls(D8,D9);
HX711 scale(D2, D7);
NETPIE netPie("HappyPigsty","zw0HnvDcL9VY4qA","BDiOw4Twn98leHH6ATHDkV7fD");

int delay_time = 0;

void setup()
{
    Serial.begin(115200);
    dc.setSpeed(speed);
    sm1.attach(D5);
    sm2.attach(D6);

    sm1.write(180);
    sm2.write(0);
 
    netPie.getMicrogear().on(MESSAGE,ReceiveMessage);
    netPie.setAlias("Board");
    netPie.setWIFI("SR_NewBorn", "0874847756");
    netPie.connectWIFI();
    netPie.connect();

    scale.set_scale();
    scale.tare(); 
    scale.set_scale(calibration_factor);
}

void loop()
{   
  netPie.loopConnect();
  
  char input = '0';

  if(Serial.available())
  {
    input = Serial.read();
    Serial.println(input);
  } 
  
}

void ReceiveMessage(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Receive message : ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);

    delay_time   = atoi ((char *)msg);
    startWeight();
}

void startWeight()
{
    double distance;  
    double weight;  

    distance = uls.readDistance();
    send_data("WebControl", "distance", distance);
    
    dc.startMotorA(1);
    dc.startMotorB(1);

    delay(delay_time);

    dc.stopMotorA();
    dc.stopMotorB();
    sm1.write(0);
    sm2.write(180);

    send_data("WebControl", "loadcell", 1);
    delay(5000);
    weight = get_units_kg();
    send_data("WebControl", "weightcar", weight);
    
    send_data("WebControl", "loadcell", 0);
    sm1.write(180);
    sm2.write(0);


    distance = uls.readDistance();
    send_data("WebControl", "distance", distance);
    
    dc.startMotorA(0);
    dc.startMotorB(0);    
    
    delay(delay_time);
    
    dc.stopMotorA();
    dc.stopMotorB(); 

    distance = uls.readDistance();
    Serial.println(distance);
    send_data("WebControl", "distance", distance);
}

void send_data(char* target, String key, double value){
    String message = key + " " + String(value);
    netPie.sendMessage(target, message);
    Serial.println(message);
}

float get_units_kg()
{
  return (scale.get_units()*0.453592);
}


