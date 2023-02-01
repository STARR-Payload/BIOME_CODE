

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

/*
Pin Layout
 
 
 
*/

int buzzerPin = 6;
int firstSolenoidPin = 7;
int secondSolenoidPin = 8;
int thirdSolenoidPin = 9;



//int sdChipSelectPin = 4;
//int sdSCK = 13;
//int sdMOSIPin = 11; 
//int sdMISOpin = 12;




int magnetometerAddress = 0x1C;
int airQualityAddress = 0x58;
int accelerometerAddress = 0x68;
int tempPressureHumidityGasAddress = 0x77;



int safetyTime; // to be talked about 
unsigned long time;
unsigned long intialTime = millis(); 
 



void buzzer(int time) { // time will be in seconds
  digitalWrite(buzzerPin, HIGH);
  delay(time * 1000);
  digitalWrite(buzzerPin, LOW);

}


void solenoidOn(int SolenoidPin) { // easy on for solenoid 
  digitalWrite(SolenoidPin, HIGH); 
}

void solenoidOff(int SolenoidPin) { // easy off for solenoid
  digitalWrite(SolenoidPin, LOW);
}

void redudancyMode(int timeElapsed) { // will be called on if alti fails


}



int checkGs() { // will be called on by loop to check when we have launch and set epoch time, should probably pass g instead 

  // grab accelerometer data 
  int gs;
  delay(500);

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
  pinMode(buzzerPin, OUTPUT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
 
  int launchCheck = checkGs();
  while (launchCheck) {
    launchCheck = checkGs();
    
  }

  // we have liftoff 


  
  

  // checks time passed from epoch
  time = millis() - intialTime;
  Serial.print(intialTime);

}

