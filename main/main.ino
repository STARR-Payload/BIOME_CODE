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

#include <assert.h>
#include "accelerometerSensor.h"
#include "softwareTeam.h"
#include "magnetometerSensor.h"
#include "gasSensor.h"
#include "sdReadWrite.h"
#include "tempHumiditySensor.h"
#include "externalInt.h"
#include "timer.h"
#include "conv.h"

unsigned long startMillis;
int currentValve = 0; 
Timer timerThirdy;
Timer timerToApogee;
Timer timerUnderMain; 
int check;
int mosfetList[] = {mosfetOne, mosfetTwo, mosfetThree};
float currentAccelVector = 0;
struct Queue myQueue = {0, 0, 25}; // front, rear, size
sensors_vec_t ICMAccelerationPacket;
sensors_vec_t ICMGyroPacket;
float data[DATASECTIONLENGTH]; 


void valveDeploy() { // Switch case logic to increment through valve deployments 

  switch (currentValve) {
    case 0:
      Serial.println("Valve 1 Open");
      mosfetOn(mosfetOne);
      break;

    case 1:
      Serial.println("Valve 2 Open, Valve 1 Closed");
      mosfetOff(mosfetOne);
      mosfetOn(mosfetTwo);
      break;

    case 2:
      Serial.println("Valve 3 Open, Valve 2 Closed");
      mosfetOff(mosfetTwo);
      mosfetOn(mosfetThree);
      break;

    case 3:
      Serial.println("Valve 3 Closed");
      mosfetOff(mosfetThree);
      currentValve = 0;
      stateMainDeploy();
      break;
  }
  currentValve++;
}

enum DataPosition { // Stores position of all sensor data in data array
                  elapsedTime = 0,
                  valveOneTemp, valveTwoTemp, valveThreeTemp, valveFourTemp, 
                  SPGCO2, SPGEth, SPGVTOL, SPGH2, 
                  ACCELx, ACCELy, ACCELz, GYROx, GYROy, GYROz, 
                  BMETemp, BMEHumidity, BMEPressure, 
                  LIS3MDLcoorX, LIS3MDLcoorY, LIS3MDLcoorZ,
                  Valve,
                  };

void sensorToSD() { // Will collect all sensor data and store in a data array 

  data[elapsedTime] = millis() - startMillis;

  ICMAccelerationPacket = ICM20469Accelread();
  ICMGyroPacket = ICM20469Gyroread();

  bme.performReading();

  data[valveOneTemp] = airflowTemp(1);
  data[valveTwoTemp] = airflowTemp(2);
  data[valveThreeTemp] = airflowTemp(3);
  data[valveFourTemp] = airflowTemp(4);

  data[SPGCO2] = SPG30CO2read();
  data[SPGEth] = SPG30ETHread();
  data[SPGVTOL] = SPG30TVOCread();
  data[SPGH2] = SPG30H2read();

  data[ACCELx] = ICMAccelerationPacket.x;
  data[ACCELy] = ICMAccelerationPacket.y;
  data[ACCELz] = ICMAccelerationPacket.z;

  data[GYROx] = ICMGyroPacket.x;
  data[GYROy] = ICMGyroPacket.y;
  data[GYROz] = ICMGyroPacket.z;

  data[BMETemp] = bme.temperature;  // SLOWWWWW
  data[BMEPressure] = bme.pressure; // SLOWWWWW
  data[BMEHumidity] = bme.humidity; // SLOWWWWW

  data[LIS3MDLcoorX] = LIS3MDLReadX();
  data[LIS3MDLcoorY] = LIS3MDLReadY();
  data[LIS3MDLcoorZ] = LIS3MDLReadZ();

  data[Valve] = currentValve; 

  SDWrite(data, "PayloadData.txt");

  // sensorToSD is now complete 
}

void stateLiftoff() { // Will begin as soon as we detect lift off and will begin countdown to apogee
  Serial.println("OFF TO SEE THE WIZARD!!!");
  timerToApogee.start();
  while (1) {
    timerToApogee.update();
    sensorToSD();
  }
}


void stateDescent() { // Will trigger at apogee and begin valve deployment process 
  Serial.println("DESCENT!!!!");
  timerToApogee.stop(); 
  valveDeploy();
  timerThirdy.start();

  while (1) {
    timerThirdy.update();
    sensorToSD();
  }

}

void stateMainDeploy() { // After all valves are deployed we begin countdown to the end
  Serial.println("MAIN DEPLOY!!!");
  timerThirdy.stop();
  timerUnderMain.start();
  
  while (1) {
    timerUnderMain.update();
    sensorToSD();
  }
}


void stateLanded() { // Will turn off remaining timer and stop collecting sensor data
  timerUnderMain.stop();
  Serial.println("PLEASE CRANK THE SILLY THING AROUND");
  Serial.println("TIME TO GO TO SLEEP ILL MISS YOU :(");
  while (1) decoder();
}


void setup() {
  Serial.begin(9600);
  delay(5000);
  Serial.println("\n \n \n \n \t \t \t NEW LOAD");

  // intialize pins for solenoid control 
	pinMode(mosfetOne, OUTPUT);
	pinMode(mosfetTwo, OUTPUT);
	pinMode(mosfetThree, OUTPUT);

	// intialize pin for buzzer control 
	pinMode(buzzerPin, OUTPUT);

  // Perform all setup functions for all sensors and use check as a flag for if anything goes wrong
  check += SDsetup();
  check += SPG30Setup();
  check += BME680Setup();
  check += ICM20649Setup();
  check += LIS3MDLSetup();
  airflowSetupAll();

  Serial.println("");
  Serial.println("**************************************************************************");
  Serial.println("SETUP CHECK");
  assert(!check);
  Serial.println("SETUP PASSED");
  Serial.println("**************************************************************************");

  // Perform a check that we can poll all sensors for data 
  check += SPG30readingCheck();
  check += BME680readingCheck(); 
  check += ICM20649readingCheck();
  check += LIS3MDLreadingCheck();
  
  Serial.println("READING CHECK");
  assert(!check);
  Serial.println("READING PASSED");
  Serial.println("**************************************************************************");

  /* 
    Setup all inturupt timers that will be used
  1) Timer of 30 seconds that begins at apogee and deploys a new set of valves 
  2) Timer of 22 seconds that begins at launch and begins countdown to apogee
  3) Timer of 10 minutes that begins when all valves are done collecting and begins countdown to sleep mode
  */ 
  Serial.println("TIMER SETUP");
  timerThirdy.setInterval(30000, 3); // 30000 = 30 seconds
  timerThirdy.setCallback(valveDeploy);
  timerToApogee.setTimeout(22000); // 22000 = 22 seconds
  timerToApogee.setCallback(stateDescent);
  timerUnderMain.setTimeout(600000); // 600000 = 10 minutes 
  timerUnderMain.setCallback(stateLanded);
  Serial.println("TIMER PASSED");
  Serial.println("**************************************************************************");

  // Perform a few loops of sensor data aquisition to remove any starting outliers 
  Serial.println("DUMMY DATA TEST (WILL TAKE A FEW SECONDS)");
  for (int i = 0; i < 150; i++) {
    currentAccelVector = ICM20469NormVector();
    push(&myQueue,currentAccelVector);
  }
  for (int i = 0; i < 10; i++) {
    ICMAccelerationPacket = ICM20469Accelread();
    ICMGyroPacket = ICM20469Gyroread();
    bme.performReading();
    SPG30CO2read();
    SPG30ETHread();
    SPG30TVOCread();
    SPG30H2read();
    LIS3MDLReadX();
    LIS3MDLReadY();
    LIS3MDLReadZ();
    airflowTemp(1);
    airflowTemp(2);
    airflowTemp(3);
    airflowTemp(4);
  }
  Serial.println("DUMMY DATA PASS");
  Serial.println("**************************************************************************");
  Serial.println("\n \n \n \n \t \t \t WE ARE READY FOR LAUNCH");

	startMillis = millis();  //initial start time

  // Setup is now complete
}

void loop() {
  // Will begin after setup and will continiously update average acceleration to check for launch conditions 

  delayMicroseconds(38000);

  //stateLiftoff(); // REMOVE BEFORE FLIGHT 
  //Serial.println("In Main Loop"); // REMOVE BEFORE FLIGHT
  //printQueue(&myQueue); // REMOVE BEFORE FLIGHT
  //Serial.println(convolve(myQueue.data)); // REMOVE BEFORE FLIGHT
 
  push(&myQueue,ICM20469NormVector());

  if (launchDetecter(myQueue.data)) {
    stateLiftoff();
  }
  
}