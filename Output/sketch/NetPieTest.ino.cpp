#include <Arduino.h>
#line 1 "c:\\Users\\EucliwoodX\\Desktop\\ProjectArduino\\Test\\NetPieTest\\NetPieTest.ino"
#line 1 "c:\\Users\\EucliwoodX\\Desktop\\ProjectArduino\\Test\\NetPieTest\\NetPieTest.ino"
#include "NETPIE.h"

NETPIE netPie;

#line 5 "c:\\Users\\EucliwoodX\\Desktop\\ProjectArduino\\Test\\NetPieTest\\NetPieTest.ino"
void setup();
#line 13 "c:\\Users\\EucliwoodX\\Desktop\\ProjectArduino\\Test\\NetPieTest\\NetPieTest.ino"
void loop();
#line 18 "c:\\Users\\EucliwoodX\\Desktop\\ProjectArduino\\Test\\NetPieTest\\NetPieTest.ino"
void ReceiveMessage(char *topic, uint8_t* msg, unsigned int msglen);
#line 5 "c:\\Users\\EucliwoodX\\Desktop\\ProjectArduino\\Test\\NetPieTest\\NetPieTest.ino"
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
