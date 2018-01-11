#include <DHT.h>  

#define DHTTYPE DHT11           // Define type of sensor 
#define DHTPIN  D4

DHT dht(DHTPIN, DHTTYPE, 15);
void setup()
{
  Serial.begin(115200);
  dht.begin();
}

void loop()
{
  float temp = dht.readTemperature();
  Serial.print("temp : ");
  Serial.println(temp);
}

