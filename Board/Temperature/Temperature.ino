#include <DHT.h>
#include "Relay.h"
#include "NETPIE.h"

#define DHTTYPE DHT11
#define DHTPIN  D4

DHT dht(DHTPIN, DHTTYPE, 15);
Relay relay(D0, D1);
NETPIE netPie("HappyPigsty", "zw0HnvDcL9VY4qA", "BDiOw4Twn98leHH6ATHDkV7fD");

float temperature;
int downtemp, clean;

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
}

void loop()
{
  netPie.loopConnect();

  float temperature = dht.readTemperature();
  Serial.print("temp : ");
  Serial.println(temperature);
  send_data("WebControl");

  if (temperature >= 40 )
  {
    relay.startDownTemperature();
  }
  else
  {
    relay.stopTemperature();
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
    json += "\"clean\":" + String(clean);
    json += "}";   
    return json;
}

