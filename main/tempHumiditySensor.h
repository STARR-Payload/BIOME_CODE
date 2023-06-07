// BME680

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme;

void bmesetup() {

  
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, something is wrong");
    while (1);
  } 
  Serial.println("BME is working");
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

static void bmereadingcheck() {
  if (! bme.performReading()) {
    Serial.println("Failed read, something is wrong");
    return;
  }
}

float bmeTemp(){
  return bme.temperature; // C
}

float bmePressure() {
  return bme.pressure / 100.0; // hPa
}

float bmehumdity(){
  return bme.humidity; // %
}

float bmeGas() {
  return bme.gas_resistance / 1000.0; // KOhms
}

float bmeAlti() {
  return bme.readAltitude(SEALEVELPRESSURE_HPA); // meters 
}

