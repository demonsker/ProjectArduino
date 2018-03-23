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

int stopDistance, loadcell;
double distance;  
double weight;

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

    stopDistance = 0;
    loadcell = 0;
    distance = 0.00;  
    weight = 0.00;
}

void loop()
{   
  netPie.loopConnect();
}

void startWeight()
{
    //GO!!
    dc.startMotorA(1);
    dc.startMotorB(1);
    
    do
    {   
        distance = uls.readDistance();
        Serial.println(distance);
        send_data("WebControl");
        delay(500);
    }while(distance < stopDistance);

    dc.stopMotorA();
    dc.stopMotorB();
    
    //Servo start!!
    sm1.write(0);
    sm2.write(180);
    loadcell = 1;
    send_data("WebControl");
    
    delay(5000);
    
    weight = get_units_kg();
    loadcell = 0;
    send_data("WebControl");

    sm1.write(180);
    sm2.write(0);
    
    //Back!!
    dc.startMotorA(0);
    dc.startMotorB(0);    

    
    while(distance > 5)
    {
        distance = uls.readDistance();
        Serial.println(distance);
        send_data("WebControl");
        delay(500);
    }
    
    dc.stopMotorA();
    dc.stopMotorB(); 

    netPie.sendMessage("WebControl", "Ready");
}

void ReceiveMessage(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Receive message : ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);

    stopDistance   = atoi ((char *)msg);
    startWeight();
}

void send_data(char* target){
    String message = toJSON();
    netPie.sendMessage(target, message);
}

String toJSON()
{
    String json = "{";
    json += "\"distance\":" + String(distance) + ",";
    json += "\"loadcell\":" + String(loadcell) + ",";
    json += "\"weight\":" + String(weight);
    json += "}";   
    return json;
}

float get_units_kg()
{
  return (scale.get_units()*0.453592);
}

