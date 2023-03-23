#include <MKRGSM.h>

GSM gsmAccess;
GSM_SMS sms;

char fromNo[20];
char msg[180];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
  bool connected = false;
  while (!connected) {
    if (gsmAccess.begin() == GSM_READY) {
      connected = true;
    } else {
      Serial.println("Couldn't initialize modem, waiting ...");
      delay(1000);
    }
  }
  Serial.println("Modem initialized, waiting ...");  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (sms.available()) {
    sms.remoteNumber(fromNo, 20);
    Serial.print("Message from: ");
    Serial.println(fromNo);
    int i = 0;
    int j;
    while ( (j = sms.read()) != -1) {
      msg[i++] = (char) j;
    }
    Serial.println(msg);
  }
}
