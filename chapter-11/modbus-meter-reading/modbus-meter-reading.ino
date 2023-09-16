#include <ArduinoRS485.h>
#include <ArduinoModbus.h>

unsigned long lastRead = millis();
const int myDelay = 60000;

void setup() {
  //initialize the serial port
  Serial.begin(115200);
  delay(1500);
  //start the modbus RTU client
  if (!ModbusRTUClient.begin(9600)) {
    Serial.println("Unable to initialize Modbus RTU Client"); //there was an error
  }
}

void loop() {
  if (millis() - lastRead > myDelay) {
    lastRead = millis();
    float consumption = getEnergy();
    Serial.print("kWh: ");
    Serial.println(consumption);
  }
}

//get the voltage reading
float getVoltage() {
  float v = 0.;
  //read the holding register values from the meter
  if (!ModbusRTUClient.requestFrom(0x01, HOLDING_REGISTERS, 0x000C, 2)) {
    Serial.print("Error reading voltage: ");
    Serial.println(ModbusRTUClient.lastError());
  }
  else {
    uint16_t w1 = ModbusRTUClient.read(); //read the first word from the buffer
    uint16_t w2 = ModbusRTUClient.read(); //read the second word from the buffer
    //concatenate both words to get the voltage in mV using a binary shift
    uint32_t dw = w1 << 16 | w2;
    v = dw / 1000.0; //convert to volts
  }
  return v;
}

//get the energy reading
double getEnergy() {
  double kWh = 0.;
  //read the holding register values from the meter
  if (!ModbusRTUClient.requestFrom(0x01, HOLDING_REGISTERS, 0x0109, 3)) {
    Serial.print("Error reading energy consumption: ");
    Serial.println(ModbusRTUClient.lastError());
  }
  else {
    uint16_t w1 = ModbusRTUClient.read(); //read the first word from the buffer
    uint16_t w2 = ModbusRTUClient.read(); //read the second word from the buffer
    uint16_t w3 = ModbusRTUClient.read(); //read the third word from the buffer
    //concatenate all words to get the energy comsumption in watts using a binary shift
    uint32_t dw = w1 << 32 | w2 << 16 | w3;
    kWh = dw / 1000.0; //convert to kWh
  }
  return kWh;
}