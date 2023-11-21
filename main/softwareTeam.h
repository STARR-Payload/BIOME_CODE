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

#include <OneWire.h>
#include <DallasTemperature.h>


void airflowSetup(int valveNumber);

// Define precision of recorded temperature in bits.
// Ranges from 9 to 12 bits, with 12 corresponsing to 
// 4 decimal places and 9 corresponding to 1 decimal place.
enum Precision {minPrec = 9, lowPrec = 10, highPrec = 11, maxPrec = 12};
int tempPrecision = lowPrec;

// Define i/o pins for valves (index 0 corresponds to valve 1's pin and so forth)
OneWire sensorPins[] = {6, 5, 3, 2};
const int numOfSensors = sizeof(sensorPins) / sizeof(OneWire);

// Define DallasTemperature instances for sensors
DallasTemperature sensors[numOfSensors];

// Determines if a sensor has been initialized (1 = Yes, 0 = No)
int isIni[numOfSensors] = {0};

// Initializes all valve sensors
void airflowSetupAll() {
  Serial.println("Initializing all valve sensors...");
  for (int i = 1; i <= numOfSensors; i++) {
      airflowSetup(i);
  }
  Serial.println("All valve sensors are initialized.");
}

// Initializes individual valve sensors
void airflowSetup(int valveNumber) {
  Serial.print("Initializing valve " + String(valveNumber) + ": ");

  // Initialize sensor if it hasn't been already
  int index = valveNumber-1;
  if (!isIni[index]) {
      DeviceAddress deviceAddress;

      sensors[index].setOneWire(&sensorPins[index]);
      sensors[index].begin();
      if (sensors[index].getAddress(deviceAddress, 0)) sensors[index].setResolution(deviceAddress, tempPrecision);
      isIni[index] = 1;
  }

  Serial.println("Done");
}

// Returns temperature of individual valve sensor
float airflowTemp(int valveNumber) {
  int index = valveNumber-1;
  sensors[index].requestTemperatures();
  return sensors[index].getTempCByIndex(0);
}