int buzzerPin = 7;
int mosfetOne = 6;
int mosfetTwo = 8;
int mosfetThree = 9;
int outletTempSensorOne = 2;
int outletTempSensorTwo = 3;
int outletTempSensorThree = 4;
int outletTempSensorFour = 5;


/*

  SD CARD:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

*/


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