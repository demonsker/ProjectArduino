#include "Relay.h"

Relay relay(6,7);
Relay relay2(8,9);
  
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
    Serial.println("start3");
    relay2.startDownTemperature();
  }
  else if(input == '4')
  {
    Serial.println("start4");
    relay2.startCleaning();
  }
  else if(input == '5')
  {
    Serial.println("stopTemperature");
    relay.stopTemperature();
  }
  else if(input == '6')
  {
    Serial.println("stopCleaning");
    relay.stopCleaning();
  }
  else if(input == '7')
  {
    Serial.println("stop3");
    relay2.stopCleaning();
  }
  else if(input == '8')
  {
    Serial.println("stop4");
    relay2.stopCleaning();
  }
}
