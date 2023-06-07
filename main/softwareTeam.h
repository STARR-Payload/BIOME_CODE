#include <OneWire.h>
#include <DallasTemperature.h>

// Define precision of temperature in bits
#define TEMP_PRECISION 12

// Define i/o pins for valves (index 0 corresponds to valve 1's pin and so forth)
OneWire sensorPins[] = {6, 5, 3, 2};
const int numOfSensors = sizeof(sensorPins) / sizeof(OneWire);

// Define DallasTemperature instances for sensors
DallasTemperature sensors[numOfSensors];

// Determines if a sensor has been initialized (1 = Yes, 0 = No)
int isIni[numOfSensors] = {0};

// Initializes all valve sensors
void airflowSetupAll() {
    Serial.println("Initializing all valve sensors...");
    for (int i = 1; i <= numOfSensors; i++) {
        airflowSetup(i);
    }
    Serial.println("All valve sensors are initialized.");
}

// Initializes individual valve sensors
void airflowSetup(int valveNumber) {
    Serial.print("Initializing valve " + String(valveNumber) + ": ");

    // Initialize sensor if it hasn't been already
    int index = valveNumber-1;
    if (!isIni[index]) {
        DeviceAddress deviceAddress;

        sensors[index].setOneWire(&sensorPins[index]);
        sensors[index].begin();
        if (sensors[index].getAddress(deviceAddress, 0)) sensors[index].setResolution(deviceAddress, TEMP_PRECISION);
        isIni[index] = 1;
    }

    Serial.println("Done");
}

// Return temperature of individual valve sensor
float airflowTemp(int valveNumber) {
    int index = valveNumber-1;
    sensors[index].requestTemperatures();
    return sensors[index].getTempCByIndex(0);
}