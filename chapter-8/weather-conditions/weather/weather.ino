#include <PortentaEthernet.h>
#include <Ethernet.h>
#include <SPI.h>
#include <Arduino_JSON.h>

unsigned long lastRead = millis();
const int myDelay = 3600000;

char server[] = "dataservice.accuweather.com";
EthernetClient client;

void setup() {
  pinMode(LEDR, OUTPUT);
  Serial.begin(115200);
  if (Ethernet.begin() == 0) {
    Serial.println("Unable to configure Ethernet via DHCP ...");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet hardware missing. Aborting ...");
      while (true); 
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Please connect an Ethernet cable and reboot the MCU");
    }
  } else {
    Serial.print("IP Address assigned: ");
    Serial.println(Ethernet.localIP());
    delay(1000);
    Serial.println("Ready ...");
  }
}

void loop() {
  if (millis() - lastRead > myDelay) {
    lastRead = millis();

    client.stop();

    if (client.connect(server, 80)) {
      client.println("GET /currentconditions/v1/255089?apikey=tA&details=true HTTP/1.1");
      client.println();
      client.println("Connection: close");
      client.println();

      String res = String("");
      while (client.available()) {
        res.concat(client.read());
      }

      JSONVar myArray = JSON.parse(res);
      if (JSON.typeof(myArray) == "undefined") {
        Serial.println("Unable to parse API response");
      } else if (myArray.length() == 1) {
        JSONVar myObj = myArray[0];
        if (myObj.hasOwnProperty("Temperature")) {
          JSONVar myTemp = myObj["Temperature"];
          if (myTemp.hasOwnProperty("Metric")) {
            JSONVar myTempMetric = myTemp["Metric"];

            if (myTempMetric.hasOwnProperty("Value")) {
              double c = (double) myTempMetric["Value"];
              double intensity = c * 255 / 85;
              analogWrite(LEDR, intensity);
            } else {
              Serial.println("Missing Value in Metric object");
            }
          } else {
            Serial.println("Missing Metric object in Temperature object");
          }
        } else {
          Serial.println("Missing Temperature object");
        }
      } else {
        Serial.println("Unexpected number of elements in the array");
      }
    } else {
      Serial.println("Unable to connect to the AccuWeather server");
    }
  }
}
