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



#include "accelerometerSensor.h"
//#include "softwareTeam.h"
#include "magnetometerSensor.h"
#include "gasSensor.h"
#include "sdReadWrite.h"
#include "serialData.h"
#include "tempHumiditySensor.h"


int buzzerPin = 7;
int relayOne = 6;
int relayTwo = 8;
int relayThree = 9;
int outletTempSensorOne = 2;
int outletTempSensorTwo = 3;
int outletTempSensorThree = 4;
int outletTempSensorFour = 5;

int magnetometerAddress = 0x1C;
int airQualityAddress = 0x58;
int accelerometerAddress = 0x68;
int tempPressureHumidityGasAddress = 0x77;

unsigned long startMillis;
unsigned long currentMillis;

void buzzer(int time) { // time is in 1/10 second so if time == 10 then buzz for 1 sec
  	digitalWrite(buzzerPin, HIGH);
  	delay(time * 100);
  	digitalWrite(buzzerPin, LOW);
}

int voltCheck() {
  return;
}

void relayOn(int relayPin) { 
  	digitalWrite(relayPin, HIGH); 
}

void relayOff(int relayPin) {
  	digitalWrite(relayPin, LOW);
}

void dataToSD() {



  //valveOneTemp, valveTwoTemp, valveThreeTemp, valveFourTemp, SGPCO2, SGPEth, SGPVTOL, SGPH2, ACCELx, ACCELy, ACCELz, GYROx, GYROy, GYROz, BMETemp, BMEAltitude, BMEPressure, BattVolts;
  //RELAY1, RELAY2, RELAY3;


}

void dataLoop(dataPacket Datapacket) { // here when we reach nose over


  if (Datapacket.type == '@') {
    if (Datapacket.data == 9) { // we have landed... One small step for man one giant leap for some stupid uni kids
      return;
    }
  }
  return; // temp so we actually exit 
}




void setup() {
  Serial.begin(9600); // <- going to need work (serial rate of alti)
	
  SDsetup();
  accelsetup(); // needs serial baud rate flushing
  gassetup();
  magsetup();
	bmesetup();



  bmereadingcheck();

  


	// intialize pins for solenoid control 
	pinMode(relayOne, OUTPUT);
	pinMode(relayTwo, OUTPUT);
	pinMode(relayThree, OUTPUT);

	// intialize pin for buzzer control 
	pinMode(buzzerPin, OUTPUT);

	startMillis = millis();  //initial start time
}




void loop() {
	
  dataPacket Datapacket;
  //float valveOneTemp, valveTwoTemp, valveThreeTemp, valveFourTemp, SGPCO2, SGPEth, SGPVTOL, SGPH2, ACCELx, ACCELy, ACCELz, GYROx, GYROy, GYROz, BMETemp, BMEAltitude, BMEPressure, BattVolts;
  //int RELAY1, RELAY2, RELAY3;



	// code to loop until we have launch conditions
	while(1) {
    if (serialDataLeft() == 1) {
      Datapacket = serialRead();
    }
    if (Datapacket.type == '@') {
      if (Datapacket.data == 2) { // we have launched 
        break;
      }
    }
		// get accelerometer reading from sensor 
    break; // temp so it doesnt keep looping 
	}
	


  if (serialDataLeft() == 1) { // keep reading packets until we get nose over
    Datapacket = serialRead();
  }



  if (Datapacket.type == '@') {
    if (Datapacket.data == 5) { // we have nose over start data collection loop
      dataLoop(Datapacket); // should prob make a new packet in dataloop no? 
    }
  }


  // here once we landed 
  while (1) {
    delay(10000);
    buzzer(5);
  }
	
}

