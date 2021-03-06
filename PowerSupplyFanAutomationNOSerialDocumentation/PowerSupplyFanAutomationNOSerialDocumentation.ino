#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 9

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);
//declare the device addresses for each temperature sensor; it's in an array, so the index of OutT is 0, InT0 is 1, InT1 is 2, InT2 is 3.
//This is the only thing you have to worry about when replacing and configuring the temperature sensors, and I think you can figure out the formatting.
//If anything falls out, digital pin 2 is for the sensors, digital pin 3 is overheat, and the fan plugs into the relay shield's COM1 and NO1
DeviceAddress tempSensorSerial[4]= {
  {0x28, 0xFF, 0x63, 0x40, 0x20, 0x17, 0x03, 0x03}, 
  {0x28, 0xFF, 0x42, 0xA3, 0x20, 0x17, 0x04, 0x74},
  {0x28, 0xFF, 0x34, 0x44, 0x20, 0x17, 0x03, 0xC9},
  {0x28, 0xFF, 0xD2, 0x49, 0x20, 0x17, 0x03, 0x12}};

float OutT;
float InT0;
float InT1;
float InT2;
bool Fan;
float Overheat = 50; //temperature threshold at which to flash a warning light if any inside temperature sensors pass it

void setup() {
  pinMode(7, OUTPUT);
  sensors.begin();
  sensors.setResolution(tempSensorSerial[0], TEMPERATURE_PRECISION);
  sensors.setResolution(tempSensorSerial[1], TEMPERATURE_PRECISION);
  sensors.setResolution(tempSensorSerial[2], TEMPERATURE_PRECISION);
  sensors.setResolution(tempSensorSerial[3], TEMPERATURE_PRECISION);
}

void loop() {
  sensors.requestTemperatures(); 
  OutT = sensors.getTempC(tempSensorSerial[0]);
  InT0 = sensors.getTempC(tempSensorSerial[1]);
  InT1 = sensors.getTempC(tempSensorSerial[2]);
  InT2 = sensors.getTempC(tempSensorSerial[3]);
  Fan = ((InT0 > OutT) && (InT1 > OutT) && (InT2 > OutT));
  if (Fan) {
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }
  digitalWrite(3, ((InT0 >= Overheat) || (InT1 >= Overheat) || (InT2 >= Overheat)));
  delay (500);
}
