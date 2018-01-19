#include "NETPIE.h"

NETPIE netPie("HappyPigsty","zw0HnvDcL9VY4qA","BDiOw4Twn98leHH6ATHDkV7fD");

void setup()
{
    netPie.getMicrogear().on(MESSAGE,ReceiveMessage);
    netPie.setAlias("Board");
    netPie.setWIFI("Your ASUS", "0874847756");
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
