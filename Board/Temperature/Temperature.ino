#include <DHT.h>  
#include "Relay.h"

#define RELAYPINA D0
#define RELAYPINB D1
#define DHTTYPE DHT11
#define DHTPIN  D4

DHT dht(DHTPIN, DHTTYPE, 15);
Relay relay(RELAYPINA, RELAYPINB);

void setup()
{
  Serial.begin(115200);
  dht.begin();
}

void loop()
{
  float temperature = dht.readTemperature();
  Serial.print("temp : ");
  Serial.println(temperature);

  if(temperature > 30 )
  {
    Serial.println("startDownTemperature");
    relay.startDownTemperature();
  }
}

