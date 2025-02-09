#include <SoftwareSerial.h>
#include <ModbusMaster.h>
#include "LOVATO.h";

ModbusMaster node;
String dataString = "";

int NumberOfParameters = sizeof(parameters) / sizeof(int);    // Measurement parameters
float Acquired_Data[1][140];
float ParameterFailureValue = 77.7;  // Value to indicate failure (example value)
int MeterNo = 0;  // Assuming meter 0 for now
uint8_t result;
int16_t datas[2]; // Store register data

SoftwareSerial modbusSerial(16, 17);

void setup() {
  Serial.begin(115200);
  modbusSerial.begin(9600, SWSERIAL_8N1, 16, 17);  // 9600 baud, 8N1 configuration
  node.begin(1, modbusSerial);  // Modbus ID = 1 (change if needed)
}

void readModbusValues() {
  uint8_t result;
  uint16_t high, low;
  uint32_t value;
  dataString = "";  // Clear previous data

  for (int i = 0; i < sizeof(parameters) / sizeof(parameters[0]); i++) {
    result = node.readInputRegisters(parameters[i].registerAddress, parameters[i].words);

    if (result == node.ku8MBSuccess) {
      high = node.getResponseBuffer(0);
      low = node.getResponseBuffer(1);
      value = ((uint32_t)high << 16) | low;

      dataString += String(value / parameters[i].scaleFactor);
    } else {
      dataString += String(ParameterFailureValue); // Print failure value instead of error
    }

    if (i < sizeof(parameters) / sizeof(parameters[0]) - 1) {
      dataString += " ";  // Add comma except for last value
    }
  }

  Serial.println(dataString);  // Print all values in one line
}

void loop() {
  readModbusValues();
  delay(5000);  // Read every 5 seconds
}
