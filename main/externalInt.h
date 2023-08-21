int outletTempSensorOne = 2;
int outletTempSensorTwo = 3;
int outletTempSensorThree = 5;
int outletTempSensorFour = 6;
int buzzerPin = 7;
const int mosfetOne = 8;
const int mosfetTwo = 9;
const int mosfetThree = 10;

int secret[] = {
    2,1,2,1,0,1,1,1,1,0,1,2,1,0,1,1,0,1,1,1,0,2,0,1,1,0,1,2,0,1,2,0,2,1,0,0,1,2,1,1,0,1,0,2,2,0,2,2,0,1,0,1,2,1,0,0,1,1,1,2,0,1,0,2,1,0,2,0,1,0,1,2,1,0,0,0,0
};


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
        delay(250);
        break;
      case 1:
        buzzer(5);
        delay(250);
        break;
      case 2:
        buzzer(10);
        delay(250);
        break;
    }
  }
}
