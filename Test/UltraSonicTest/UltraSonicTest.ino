#include "UltraSonic.h"

UltraSonic us(D0,D1);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  double distance = us.readDistance();
  Serial.println(distance);
}
