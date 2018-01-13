# 1 "c:\\Users\\EucliwoodX\\Desktop\\ProjectArduino\\Test\\NetPieTest\\NetPieTest.ino"
# 1 "c:\\Users\\EucliwoodX\\Desktop\\ProjectArduino\\Test\\NetPieTest\\NetPieTest.ino"
# 2 "c:\\Users\\EucliwoodX\\Desktop\\ProjectArduino\\Test\\NetPieTest\\NetPieTest.ino" 2

NETPIE netPie;

void setup()
{
    netPie.initialize();
    netPie.getMicrogear().on(1,ReceiveMessage);
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
