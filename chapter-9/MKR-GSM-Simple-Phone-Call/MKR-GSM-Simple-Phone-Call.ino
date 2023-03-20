#include <MKRGSM.h>

#include "arduino_secrets.h"

const char PHONE[] = SECRET_PHONE;

GSM gsmAccess;
GSMVoiceCall vcs;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);

  // connection state
  bool connected = false;

  
  while (!connected) {
    if (gsmAccess.begin() == GSM_READY) {
      connected = true;
    } else {
      Serial.println("Error connecting, repeating attempt ...");
      delay(1000);
    }
  }

  Serial.println("GSM module initialized.");

  callAndHangUp();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void callAndHangUp() {
  Serial.print("Attempting to call: ");
  Serial.println(PHONE);

  if(vcs.voiceCall(PHONE)) {
    Serial.println("Call established, hanging up in 3 seconds.");
    delay(3000);
    vcs.hangCall();
  }
  Serial.println("Call ended");
}
