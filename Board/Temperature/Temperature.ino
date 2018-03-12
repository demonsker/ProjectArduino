#include <DHT.h>  
#include "Relay.h"
#include "NETPIE.h"

#define WIFI "Your ASUS"
#define PWD "0874847756"
#define ALIAS "Board"

#define RELAYPINA D0
#define RELAYPINB D1
#define DHTTYPE DHT11
#define DHTPIN  D4

DHT dht(DHTPIN, DHTTYPE, 15);
Relay relay(RELAYPINA, RELAYPINB);
NETPIE netPie("HappyPigsty","zw0HnvDcL9VY4qA","BDiOw4Twn98leHH6ATHDkV7fD");

void setup()
{
  Serial.begin(115200);
  dht.begin();
  netPie.getMicrogear().on(MESSAGE,ReceiveMessage);
  netPie.setAlias(ALIAS);
  netPie.setWIFI(WIFI, PWD);
  netPie.connectWIFI();
  netPie.connect();
}

void loop()
{
  netPie.loopConnect();
  
  float temperature = dht.readTemperature();
  Serial.print("temp : ");
  Serial.println(temperature);
  netPie.sendMessage("WebControl", temperature);

  if(temperature > 30 )
  {
    Serial.println("startDownTemperature");
    relay.startDownTemperature();
  }

  delay(500);
}

void ReceiveMessage(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Receive message : ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
}

