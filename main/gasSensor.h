// SPG30

#include <Wire.h>
#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;


uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}

void gassetup() {

  if (! sgp.begin()){
    Serial.println("Could not find a valid SPG30 sensor, something is wrong");
    while (1);
  }
  
  for (int i = 0; i++; i < 30) {
    uint16_t TVOC_base, eCO2_base;
    if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
      Serial.println("Failed to get baseline readings");
      return;
    }
    Serial.print("****Baseline values: eCO2: 0x"); Serial.print(eCO2_base, HEX);
    Serial.print(" & TVOC: 0x"); Serial.println(TVOC_base, HEX);
  }

  Serial.println("SPG30 is working");
}

void gasreadingCheck() {

  if (! sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return;
  }

  if (! sgp.IAQmeasureRaw()) {
    Serial.println("Raw Measurement failed");
    return;
  }

}




float gasTVOC() {
  return sgp.TVOC; // ppb
}


float gasCO2 () {
  return sgp.eCO2; // ppm
}

float gasH2 () {
  return sgp.rawH2; // 
}

float gasEth() {
  return sgp.rawEthanol; //
}



