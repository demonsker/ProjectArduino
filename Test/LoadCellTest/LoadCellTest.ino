#include "HX711.h"

#define calibration_factor 49183 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define DOUT  D5
#define CLK  A0

HX711 scale(DOUT, CLK);

void setup() {
  Serial.begin(115200);
  Serial.println("HX711 scale demo");
  scale.set_scale();
  scale.tare(); 
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
}
void loop() {
  String data = String(get_units_kg(), 4);
  Serial.print(data);
  Serial.println(" kg");
}

float get_units_kg()
{
  return(scale.get_units()*0.453592);
}
