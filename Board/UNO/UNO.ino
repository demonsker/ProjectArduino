#include "HX711.h"
#include "Relay.h"
#include <SoftwareSerial.h>


#define RX 3
#define TX 2
#define calibration_factor1 49973
#define calibration_factor2 50000
#define EMPTY 0.1
#define FULL 2.0

HX711 scale1(A0, A1);
HX711 scale2(A2, A3);
Relay relay(4, 5);
SoftwareSerial ArduinoSerial(RX, TX);

int Status;

void setup() {
  Serial.begin(115200);
  ArduinoSerial.begin(4800);

  scale1.set_scale();
  scale2.set_scale();
  scale1.tare();
  scale2.tare();
  scale1.set_scale(calibration_factor1);
  scale2.set_scale(calibration_factor2);

  Status = 1;
}

void loop() {
  double data1 = get_units_kg_1();
  double data2 = get_units_kg_2();

  Serial.println("food1 : " + String(data1) );
  Serial.println("food2 : " + String(data2) );
  if (Status == 1)
  { if (data1 <= EMPTY)
    {
      ArduinoSerial.print(data1);
      ArduinoSerial.print("\n");
      startFood1(1);
      Status = 0;
    }
    if (data2 <= EMPTY)
    {
      ArduinoSerial.print(data2);
      ArduinoSerial.print("\n");
      startFood2(1);
      Status = 0;
    }
  }
  else
  {
    if (data1 >= FULL)
    { startFood1(0);
      Status = 1;
    }
    if (data2 >= FULL)
    { startFood2(0);
      Status = 1;
    }
  }
  delay(500);
}

float get_units_kg_1()
{
  return (scale1.get_units() * 0.453592);
}

float get_units_kg_2()
{
  return (scale2.get_units() * 0.453592);
}

void startFood1(int type)
{
  (type == 1) ? relay.startDownTemperature() : relay.stopTemperature();
}

void startFood2(int type)
{
  (type == 1) ? relay.startCleaning() : relay.stopCleaning();
}

