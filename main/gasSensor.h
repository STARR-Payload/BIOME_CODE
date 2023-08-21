// SPG30

#include <flagsapi.h>
#include "Adafruit_SGP30.h"
Adafruit_SGP30 sgp;


uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}

uint16_t SPG30Setup() {

  if (! sgp.begin()){
    return 1;
  }
  
  uint16_t TVOC_base, eCO2_base;
  if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
    Serial.println("Failed to get baseline readings");
    return 1;
  Serial.println("Got good baseline readings");
  }
  Serial.println("SPG30 Found!");
  Serial.println();
  return 0;
}

uint16_t SPG30readingCheck() {
  if (! sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return 1;
  }
  if (! sgp.IAQmeasureRaw()) {
    Serial.println("Raw Measurement failed");
    return 1;
  } else return 0;
}

float SPG30TVOCread() {
  sgp.IAQmeasure();
  return sgp.TVOC; // ppb
}

float SPG30CO2read() {
  sgp.IAQmeasure();
  return sgp.eCO2; // ppm
}

float SPG30H2read() {
  sgp.IAQmeasureRaw();
  return sgp.rawH2; // 
}

float SPG30ETHread() {
  sgp.IAQmeasureRaw();
  return sgp.rawEthanol; //
}