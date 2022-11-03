

int solenoidPin = 5; //This is the output pin on the Arduino we are using


void setup() {
  // put your setup code here, to run once:
  pinMode(solenoidPin, OUTPUT);
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


void solenoidOn() {
  digitalWrite(solenoidPin, HIGH); 
}

void solenoidOff() {
  digitalWrite(solenoidPin, LOW);
}