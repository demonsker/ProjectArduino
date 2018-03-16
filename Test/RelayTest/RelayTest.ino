#include "Relay.h"
#include <DHT.h>
#define DHTTYPE DHT11           // Define type of sensor 
#define DHTPIN  5            // Define connected pin

Relay relay(6,7);
DHT dht(DHTPIN, DHTTYPE, 15);
  
void setup()
{
    Serial.begin(115200);
}

void loop()
{
  char input;

  if(Serial.available())
  {
    input = Serial.read();
    Serial.println(input);
  }
  
  if(input == '0')
  {
    Serial.println("Stop All");
    relay.stopAllPin();
  }
  else if(input == '1')
  {
    Serial.println("startDownTemperature");
    relay.startDownTemperature();
  }
  else if(input == '2')
  {
    Serial.println("startCleaning");
    relay.startCleaning();
  }
  else if(input == '3')
  {
    Serial.println("stopTemperature");
    relay.stopTemperature();
  }
  else if(input == '4')
  {
    Serial.println("stopCleaning");
    relay.stopCleaning();
  }
}
