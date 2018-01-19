#include <SoftwareSerial.h>

#define RX 3
#define TX 2

SoftwareSerial ArduinoSerial(RX,TX);

void setup()
{
    Serial.begin(115200);
    ArduinoSerial.begin(4800);
}

void loop()
{
    ArduinoSerial.print(10);
    ArduinoSerial.print("\n");
    delay(1000);
}
