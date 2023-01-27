

int firstSolenoidPin = 5;
int secondSolenoidPin = 6;
int thirdSolenoidPin = 7;
int fourthSolenoidPin = 8; 


void setup() {
  // put your setup code here, to run once:
  pinMode(firstSolenoidPin, OUTPUT);
  pinMode(secondSolenoidPin, OUTPUT);
  pinMode(thirdSolenoidPin, OUTPUT);
  pinMode(fourthSolenoidPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void getData() {
 // call all data gathering functions and write to sd card


  
}


float getTemperature() {
  // return float of the temperature of sensor in degrees

}


void solenoidOn(int SolenoidPin) {
  digitalWrite(SolenoidPin, HIGH); 
}

void solenoidOff(SolenoidPin) {
  digitalWrite(SolenoidPin, LOW);
}
