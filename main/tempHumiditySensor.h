// BME680

#include <flagsapi.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME680 bme;


uint16_t BME680Setup() {

  if (!bme.begin()) {
    return 1;
  } 
  
  Serial.println("BME Found!");
  Serial.println();
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
  return 0;
}

uint16_t BME680readingCheck() {
  return 0;
}

float BME680TempRead(){
  //bme.performReading();
  return bme.temperature; // C
}

float BME680PressureRead() {
  bme.performReading();
  return bme.pressure / 100.0; // hPa
}

float BME680humdityRead(){
  bme.performReading();
  return bme.humidity; // %
}

float BME680GasRead() {
  bme.performReading();
  return bme.gas_resistance / 1000.0; // KOhms
}

float BME680AltitudeRead() {
  bme.performReading();
  return bme.readAltitude(SEALEVELPRESSURE_HPA); // meters 
}