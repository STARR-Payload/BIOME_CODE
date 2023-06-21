/*
 Copyright 2023 STARR Student Group at University of ALberta
 2023 Christiaan Lemmer Venter christiaanlemmer@hotmail.com
  
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
//#include "softwareTeam.h"
#include "magnetometerSensor.h"
#include "gasSensor.h"
#include "sdReadWrite.h"
#include "serialData.h"
#include "tempHumiditySensor.h"
#include "externalInt.h"

unsigned long startMillis;
unsigned long currentMillis;

int BattVolts = 0;

dataPacket Datapacket;

enum DataPosition {
                  newPacketFlag = 0, PacketIdentity, PacketData,
                  valveOneTemp, valveTwoTemp, valveThreeTemp, valveFourTemp, 
                  SPGCO2, SPGEth, SPGVTOL, SPGH2, 
                  ACCELx, ACCELy, ACCELz, GYROx, GYROy, GYROz, 
                  BMETemp, BMEAltitude, BMEPressure, 
                  BatteryVolts, Valve1, Valve2, Valve3,
                  NumberOfItems // <- to be used later for better data packet length checking 
                  };


void sensorToSD(int newPacketBool) {
  /*
  
  Packet in Cycle, Packet Identifier, Packet Data
  valveOneTemp, valveTwoTemp, valveThreeTemp, valveFourTemp, 
  SPGCO2, SPGEth, SPGVTOL, SPGH2, 
  ACCELx, ACCELy, ACCELz, GYROx, GYROy, GYROz, 
  BMETemp, BMEAltitude, BMEPressure, MISSING SOME NO? 
  BattVolts;
  Valve1, Valve2, Valve3;

  */

  long long int data[NumberOfItems]; 

  sensors_vec_t ICMAccelerationPacket;
  sensors_vec_t ICMGyroPacket;


  ICMAccelerationPacket = ICM20469Accelread();
  ICMGyroPacket = ICM20469Gyroread();

  



  data[newPacketFlag] = newPacketBool;
  data[PacketIdentity] = Datapacket.type;
  data[PacketData] = Datapacket.data;


  data[BMETemp] = BME680TempRead();
  data[BMEAltitude] = BME680AltitudeRead();
  data[BMEPressure] = BME680PressureRead();


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

  data[BatteryVolts] = BattVolts;




  SDWrite(data, "1.txt");

  return;
}





void VoltDataPacket(dataPacket Datapacket) {
  if (Datapacket.type == '?') {
      BattVolts = Datapacket.data;
    }
}



void setup() {
  Serial.begin(9600); // (baud of Eggtimer Quantum Alti)

  // intialize pins for solenoid control 
	pinMode(mosfetOne, OUTPUT);
	pinMode(mosfetTwo, OUTPUT);
	pinMode(mosfetThree, OUTPUT);

	// intialize pin for buzzer control 
	pinMode(buzzerPin, OUTPUT);

  int check = 0;

  check += SDsetup();
  check += SPG30Setup();
  check += ICM20649Setup();
  check += LIS3MDLSetup();
	check += BME680Setup();
  //airflowSetupAll();

  if (check != 0) {
    buzzer(5); // half second buzz see Documentation.txt for more info
    delay(2000);
  }


  BME680readingCheck();
  SPG30readingCheck(); 
  LIS3MDLreadingCheck();
  ICM20649readingCheck();

	startMillis = millis();  //initial start time
}


void stateLiftoff() {


  while(1) {
    if (serialDataLeft() == 1) {
        Datapacket = serialRead();
    }

    if (Datapacket.type == '@') {
        if (Datapacket.data == 5) { // nose over is detected leave liftoff state
          
        }
      }

      // need to add a redundancy 
  }
}

void stateDescent() {

  
  while(1) {
    if (serialDataLeft() == 1) {
      Datapacket = serialRead();
    }
    if (Datapacket.type == '@') {
      if (Datapacket.data == 9) { // we have landed... One small step for man one giant leap for some stupid uni kids
        stateLanded();
      }
    }

    // Now need to add all the data collection under descent 

    // need to add a redundancy 
  }
}




void stateLanded() {
  while (1) { 
    delay(10000);
    buzzer(5);
  }
}



void loop() {
	/**************************************************************************/
    /*
    Control Flow:
     - Continiously check for packet then log data until launch is detected 
      - Jump to launch state
      - Launch state returns meaning it has detected descent
      - Jump to descent state
      - Descent state returns meaning it has detected landing
      - Jump to landed state
    */
    /**************************************************************************/
  
  int newPacket = 0;


  if (serialDataLeft() == 1) {
    Datapacket = serialRead();
  }
  if (Datapacket.type == '@') {
    if (Datapacket.data == 2) { // off to see the wizard
      stateLiftoff();
    }
  }
  
  // add check for acceleration 

  sensorToSD(newPacket);


}

