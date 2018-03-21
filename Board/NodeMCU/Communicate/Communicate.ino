#include <SoftwareSerial.h>
#include "NETPIE.h"

#define RX D5
#define TX D6

SoftwareSerial NodeSerial(RX, TX);
NETPIE netPie("HappyPigsty", "zw0HnvDcL9VY4qA", "BDiOw4Twn98leHH6ATHDkV7fD");

float weight1;
float weight2;

void setup()
{
  Serial.begin(115200);
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);
  NodeSerial.begin(4800);

  netPie.getMicrogear().on(MESSAGE, ReceiveMessage);
  netPie.setAlias("Board2");
  netPie.setWIFI("SR_NewBorn", "0874847756");
  netPie.connectWIFI();
  netPie.connect();

  weight1 = 0.00;
  weight2 = 0.00;
}

void loop()
{
  netPie.loopConnect();
  
  while ( NodeSerial.available() > 0)
  {
    weight1 = NodeSerial.parseFloat();
    weight2 = NodeSerial.parseFloat();
  }

  delay(500);
}

void ReceiveMessage(char *topic, uint8_t* msg, unsigned int msglen)
{
  Serial.print("Receive message : ");
  msg[msglen] = '\0';
  Serial.print((char *)msg );
}

void send_data(char* target){
    String message = toJSON();
    netPie.sendMessage(target, message);
}

String toJSON()
{
    String json = "{";
    json += "\"foodweight1\":" + String(weight1) + ",";
    json += "\"foodweight2\":" + String(weight2);
    json += "}";   
    return json;
}


