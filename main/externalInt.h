int outletTempSensorOne = 2;
int outletTempSensorTwo = 3;
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

int outletTempSensorThree = 5;
int outletTempSensorFour = 6;
int buzzerPin = 7;
const int mosfetOne = 8;
const int mosfetTwo = 9;
const int mosfetThree = 10;
int secret[] = {2,1,2,1,0,1,1,1,1,0,1,2,1,0,1,1,0,1,1,1,0,2,0,1,1,0,1,2,0,1,2,0,2,1,0,0,1,2,1,1,0,1,0,2,2,0,2,2,0,1,0,1,2,1,0,0,1,1,1,2,0,1,0,2,1,0,2,0,1,0,1,2,1,0,0,0,0};


void buzzer(int time) { // time is in 1/10 second so if time == 10 then buzz for 1 sec
  	digitalWrite(buzzerPin, HIGH);
  	delay(time * 100);
  	digitalWrite(buzzerPin, LOW);
}

void mosfetOn(int relayPin) { 
  	digitalWrite(relayPin, HIGH); 
}

void mosfetOff(int relayPin) {
  	digitalWrite(relayPin, LOW);
}

void decoder() { // dont worry about it
  for (int i = 0; i < sizeof(secret)/sizeof(int); i ++) {
    switch (secret[i]) {
      case 0:
        delay(250); // 250
        break;
      case 1:
        buzzer(5); // 5
        delay(250); // 250
        break;
      case 2:
        buzzer(10); // 10
        delay(250); // 250
        break;
    }
  }
}
