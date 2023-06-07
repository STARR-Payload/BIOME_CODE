// Libraries for DS18B20 sensor
// OneWire - https://www.pjrc.com/teensy/td_libs_OneWire.html
// DallasTemperature - https://github.com/milesburton/Arduino-Temperature-Control-Library

#include <OneWire.h>
#include <DallasTemperature.h>

// Define temperature precision in bits (from 9 to 12)
#define TEMP_PRECISION 12;

// Define Valve 1 i/o pin
#define DATA_BUS 6

// Setup OneWire instance
OneWire oneWire(DATA_BUS);

// Pass OneWire instance to create DallasTemperature object
DallasTemperature sensor(&oneWire);

// Return sensor temperature in celcius
float getTempInC() {
  sensor.requestTemperatures();
  return sensor.getTempCByIndex(0);
}

void setup() {
  // Open serial port at 9600 baud
  Serial.begin(9600);
  // Setup sensor communication
  DeviceAddress deviceAddress;
  sensor.begin();
  if (sensor.getAddress(deviceAddress, 0)) sensor.setResolution(deviceAddress, TEMP_PRECISION);
}

void loop() {
  // Print temperature in 1 second intervals
  Serial.print(getTempInC(), 5);
  Serial.println(" C");
  delay(1000);
}
