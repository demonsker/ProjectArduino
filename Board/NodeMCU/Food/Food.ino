#include "UltraSonic.h"
#include "NETPIE.h"

#define pigDistance 10

UltraSonic ultra1(D0, D1);
UltraSonic ultra2(D2, D3);
NETPIE netPie("HappyPigsty", "zw0HnvDcL9VY4qA", "BDiOw4Twn98leHH6ATHDkV7fD");

int carStatus;
double distance1, distance2;

void setup()
{
  Serial.begin(115200);
  netPie.getMicrogear().on(MESSAGE, ReceiveMessage);
  netPie.setAlias("Board2");
  netPie.setWIFI("SR_NewBorn", "0874847756");
  netPie.connectWIFI();
  netPie.connect();

  carStatus = 1;
  distance1 = 0.00;
  distance2 = 0.00;
}

void loop()
{
  netPie.loopConnect();
  
  distance1 = ultra1.readDistance();
  distance2 = ultra2.readDistance();
  Serial.println("distance1 : " + String(distance1) );
  Serial.println("distance2 : " + String(distance2) );
  send_data("WebControl");

  if (carStatus == 1)
  { 
    if (distance1 < pigDistance)
      {
        netPie.sendMessage("Board", 500);
        carStatus = 0;
      }
    else if (distance2 < pigDistance)
      {
        netPie.sendMessage("Board", 1000);
        carStatus = 0;
      }
  }

  delay(500);

}

void ReceiveMessage(char *topic, uint8_t* msg, unsigned int msglen)
{
  Serial.print("Receive message : ");
  msg[msglen] = '\0';
  if (strcmp((char *)msg, "ready") == 0) 
      carStatus = 1;
}

void send_data(char* target){
    String message = toJSON();
    netPie.sendMessage(target, message);
}

String toJSON()
{
    String json = "{";
    json += "\"pigdistance1\":" + String(distance1) + ",";
    json += "\"pigdistance2\":" + String(distance2);
    json += "}";   
    return json;
}
