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

#include "tempHumiditySensor.h"

/*
Pin Layout
 
 
 
*/

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

 

void buzzer() {
  digitalWrite(buzzerPin, HIGH);
  delay(1000);
  digitalWrite(buzzerPin, LOW);
}


void relayOn(int relayPin) { 
  digitalWrite(relayPin, HIGH); 
}

void relayOff(int relayPin) {
  digitalWrite(relayPin, LOW);
}





void setup() {
  Serial.begin(9600);
  bmesetup();
  bmeTempPrint();

  // intialize pins for solenoid control 
  pinMode(relayOne, OUTPUT);
  pinMode(relayTwo, OUTPUT);
  pinMode(relayThree, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  
}

void loop() {
 
  
  

}

