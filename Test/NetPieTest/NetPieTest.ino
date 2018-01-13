#include "NETPIE.h"

NETPIE netPie;

void setup()
{
    netPie.initialize();
    netPie.getMicrogear().on(MESSAGE,ReceiveMessage); 
    netPie.connectWIFI();
    netPie.connect();
}

void loop()
{
    netPie.loopConnect();
}

void ReceiveMessage(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Receive message : ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
}