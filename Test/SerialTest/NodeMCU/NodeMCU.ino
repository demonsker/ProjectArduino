#include <SoftwareSerial.h>

#define RX D5
#define TX D6

SoftwareSerial NodeSerial(RX,TX);

void setup()
{
    Serial.begin(115200);
    pinMode(RX, INPUT);
    pinMode(TX, OUTPUT);
    NodeSerial.begin(4800);
}

void loop()
{
    while( NodeSerial.available() > 0)
    {
        float val = NodeSerial.parseFloat();
        if(NodeSerial.read() == '\n')
        {
            Serial.println(val);
        }
    }
    delay(1000);
}
