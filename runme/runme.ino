/*
 Copyright 2023 STARR Student Group at University of ALberta
  
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

/*
Pin Layout
 
 
 
*/


int firstSolenoidPin = 5;
int secondSolenoidPin = 6;
int thirdSolenoidPin = 7;
int safetyTime; // to be talked about 
int magnetometerAddress = 0x1C;
int airQualitySensorAddress = 0x58;
unsigned long time;

void getData() {
 // call all data gathering functions and write to sd card


  
}


void solenoidOn(int SolenoidPin) {
  digitalWrite(SolenoidPin, HIGH); 
}

void solenoidOff(int SolenoidPin) {
  digitalWrite(SolenoidPin, LOW);
}


void redudancyMode(int timeElapsed) {


}



void checkTimePassed() {


}



int checkGs() {

  // grab accelerometer data 
  int gs;

  if (gs > 2) {
    return 1;
  } else {
    return 0;
  }

}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // intialize pins for solenoid control 
  pinMode(firstSolenoidPin, OUTPUT);
  pinMode(secondSolenoidPin, OUTPUT);
  pinMode(thirdSolenoidPin, OUTPUT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
 
  int launchCheck = checkGs();
  while (launchCheck) {
    launchCheck = checkGs();
  }

  // we have liftoff 


  unsigned long intialTime = millis(); 

  // checks time passed from epoch
  time = millis() - intialTime;
  Serial.print("\n");

}

