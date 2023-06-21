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
  
  Serial.println("BME is working");
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  return 0;
}

uint16_t BME680readingCheck() {
  if (! bme.performReading()) {
    Serial.println("Failed read, something is wrong");
    return 1;
  } else return 0;
}

float BME680TempRead(){
  return bme.readTemperature(); // C
}

float BME680PressureRead() {
  return bme.readPressure() / 100.0; // hPa
}

float BME680humdityRead(){
  return bme.readHumidity(); // %
}

float BME680GasRead() {
  return bme.readGas() / 1000.0; // KOhms
}

float BME680AltitudeRead() {
  return bme.readAltitude(SEALEVELPRESSURE_HPA); // meters 
}



