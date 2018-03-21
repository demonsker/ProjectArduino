#include <DHT.h>
#include "Relay.h"
#include "UltraSonic.h"
#include "NETPIE.h"

#define DHTTYPE DHT11
#define DHTPIN  D4
#define pigDistance 10

DHT dht(DHTPIN, DHTTYPE, 15);
Relay relay(D0, D1);
UltraSonic ultra1(D0, D1);
UltraSonic ultra2(D2, D3);
NETPIE netPie("HappyPigsty", "zw0HnvDcL9VY4qA", "BDiOw4Twn98leHH6ATHDkV7fD");

float temperature;
int downtemp, clean;
int carStatus;
double distance1, distance2;

void setup()
{
  Serial.begin(115200);
  dht.begin();
  netPie.getMicrogear().on(MESSAGE, ReceiveMessage);
  netPie.setAlias("Board2");
  netPie.setWIFI("SR_NewBorn", "0874847756");
  netPie.connectWIFI();
  netPie.connect();

  temperature = 0.00;
  downtemp = 0;
  clean = 0;
  carStatus = 1;
  distance1 = 0.00;
  distance2 = 0.00;
}

void loop()
{
  netPie.loopConnect();

  temperature = dht.readTemperature();
  distance1 = ultra1.readDistance();
  distance2 = ultra2.readDistance();
  Serial.println("temp : " + String(temperature) );
  Serial.println("distance1 : " + String(distance1) );
  Serial.println("distance2 : " + String(distance2) );
  send_data("WebControl");

  if (temperature >= 40 )
  {
    relay.startDownTemperature();
    downtemp = 1;
  }
  else
  {
    relay.stopTemperature();
    downtemp = 0;
  }


  if (carStatus == 1)
  { 
    if (distance1 < pigDistance)
      {
        netPie.sendMessage("Board", 500);
        carStatus = 0;
      }
    else if (distance2 < pigDistance)
      {
        netPie.sendMessage("Board", 1000);
        carStatus = 0;
      }
  }

  delay(500);
}

void ReceiveMessage(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("Receive message : ");
  msg[msglen] = '\0';
  Serial.println((char *)msg);
  
  if (strcmp((char *)msg, "clean") == 0) {
    Serial.println("startCleaning");
    relay.startCleaning();
    clean = 1;
  }
  else if (strcmp((char *)msg, "stopclean") == 0)
  { 
    Serial.println("stopCleaning");
    relay.stopCleaning();
    clean = 0;
  }
  else if (strcmp((char *)msg, "downtemp") == 0)
  { 
    Serial.println("startDownTemp");
    relay.startDownTemperature();
    downtemp = 1;
  }
  else if (strcmp((char *)msg, "stopdowntemp") == 0)
  { 
    Serial.println("stopDownTemp");
    relay.stopTemperature();
    downtemp = 0;
  }
  else if (strcmp((char *)msg, "ready") == 0) 
      carStatus = 1;
  
  send_data("WebControl");
}

void send_data(char* target){
    String message = toJSON();
    netPie.sendMessage(target, message);
}

String toJSON()
{
    String json = "{";
    json += "\"temp\":" + String(temperature) + ",";
    json += "\"down\":" + String(downtemp) + ",";
    json += "\"clean\":" + String(clean) + ",";
    json += "\"pigdistance1\":" + String(distance1) + ",";
    json += "\"pigdistance2\":" + String(distance2);
    json += "}";   
    return json;
}

