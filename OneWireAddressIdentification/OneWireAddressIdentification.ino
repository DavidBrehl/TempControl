#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 9

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

DeviceAddress Therm;

void setup() {
  Serial.begin(9600);
  sensors.begin();
  sensors.getAddress(Therm, 0);
  sensors.setResolution(Therm, TEMPERATURE_PRECISION);
  Serial.print ("Therm address: ");
  printAddress(Therm);
}

void loop() { 
}

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
