// SPG30
/*
 Copyright 2023 STARR Student Group at University of ALberta
 Lead: 2023, Christiaan Lemmer Venter, christiaanlemmer@hotmail.com
  
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
 
  1. Redistributions of source code must retain the above copyright notice,
     this list of conditions and the disclaimer below in the documentation
     and/or other materials provided with the distribution.
 
  2. Neither the name of the copyright holder nor the names of its
     contributors may be used to endorse or promote products derived from this
     software without specific prior written permission.
     
  3. Explict permission has been granted by an official current member of the STARR 
     student group at the University of ALberta that has granted authority over this 
     code and affiliated works. 
 
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

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