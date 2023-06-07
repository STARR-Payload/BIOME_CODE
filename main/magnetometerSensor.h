// LIS3MDL

#include <Wire.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>

Adafruit_LIS3MDL lis3mdl;


void magsetup(void) {


  // Try to initialize!
  if (!lis3mdl.begin_I2C()) {
    Serial.println("Could not find a valid LIS3MDL sensor, something is wrong");
    while (1) { delay(10); }
  }

  Serial.println("LIS3MDL Found!");

  lis3mdl.setPerformanceMode(LIS3MDL_MEDIUMMODE);
  Serial.print("Performance mode set to: ");
  switch (lis3mdl.getPerformanceMode()) {
    case LIS3MDL_LOWPOWERMODE: Serial.println("Low"); break;
    case LIS3MDL_MEDIUMMODE: Serial.println("Medium"); break;
    case LIS3MDL_HIGHMODE: Serial.println("High"); break;
    case LIS3MDL_ULTRAHIGHMODE: Serial.println("Ultra-High"); break;
  }

  lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);
  Serial.print("Operation mode set to: ");
  // Single shot mode will complete conversion and go into power down
  switch (lis3mdl.getOperationMode()) {
    case LIS3MDL_CONTINUOUSMODE: Serial.println("Continuous"); break;
    case LIS3MDL_SINGLEMODE: Serial.println("Single mode"); break;
    case LIS3MDL_POWERDOWNMODE: Serial.println("Power-down"); break;
  }

  lis3mdl.setDataRate(LIS3MDL_DATARATE_155_HZ);
  // You can check the datarate by looking at the frequency of the DRDY pin
  Serial.print("Data rate set to: ");
  switch (lis3mdl.getDataRate()) {
    case LIS3MDL_DATARATE_0_625_HZ: Serial.println("0.625 Hz"); break;
    case LIS3MDL_DATARATE_1_25_HZ: Serial.println("1.25 Hz"); break;
    case LIS3MDL_DATARATE_2_5_HZ: Serial.println("2.5 Hz"); break;
    case LIS3MDL_DATARATE_5_HZ: Serial.println("5 Hz"); break;
    case LIS3MDL_DATARATE_10_HZ: Serial.println("10 Hz"); break;
    case LIS3MDL_DATARATE_20_HZ: Serial.println("20 Hz"); break;
    case LIS3MDL_DATARATE_40_HZ: Serial.println("40 Hz"); break;
    case LIS3MDL_DATARATE_80_HZ: Serial.println("80 Hz"); break;
    case LIS3MDL_DATARATE_155_HZ: Serial.println("155 Hz"); break;
    case LIS3MDL_DATARATE_300_HZ: Serial.println("300 Hz"); break;
    case LIS3MDL_DATARATE_560_HZ: Serial.println("560 Hz"); break;
    case LIS3MDL_DATARATE_1000_HZ: Serial.println("1000 Hz"); break;
  }

  lis3mdl.setRange(LIS3MDL_RANGE_4_GAUSS);  // most accurate one possible


  lis3mdl.setIntThreshold(500);
  lis3mdl.configInterrupt(false, false, true,  // enable z axis
                          true,                // polarity
                          false,               // don't latch
                          true);               // enabled!
}

void magloop() {
  lis3mdl.read();  // get X Y and Z data at once
  // Then print out the raw data
  Serial.print("\nX:  ");
  Serial.print(lis3mdl.x);
  Serial.print("  \tY:  ");
  Serial.print(lis3mdl.y);
  Serial.print("  \tZ:  ");
  Serial.println(lis3mdl.z);

  /* Or....get a new sensor event, normalized to uTesla */
  sensors_event_t event;
  lis3mdl.getEvent(&event);
  /* Display the results (magnetic field is measured in uTesla) */
  Serial.print("\tX: ");
  Serial.print(event.magnetic.x);
  Serial.print(" \tY: ");
  Serial.print(event.magnetic.y);
  Serial.print(" \tZ: ");
  Serial.print(event.magnetic.z);
  Serial.println(" uTesla ");

  delay(100);
  Serial.println();
}


// AGAIN ISSUE WITH EVENT HANDLER 


float magX() {
  return;  
}