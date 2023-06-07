// ICM20649

#include <Adafruit_ICM20649.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_ICM20649 icm;
uint16_t measurement_delay_us = 65535; // Delay between measurements for testing




void accelsetup(void) {
  

  // Try to initialize!
  if (!icm.begin_I2C()) {

    Serial.println("Could not find a valid ICM20649 sensor, something is wrong");
    while (1) {
      delay(10);
    }
  }



  Serial.println("ICM20649 Found!");

  icm.setAccelRange(ICM20649_ACCEL_RANGE_16_G); 
    
  icm.setGyroRange(ICM20649_GYRO_RANGE_500_DPS); 
  



  // DECIDE ON THIS ALL BELOW it was given baseline but i want to explore more 

  //  icm.setAccelRateDivisor(4095);
  uint16_t accel_divisor = icm.getAccelRateDivisor();
  float accel_rate = 1125 / (1.0 + accel_divisor);

  Serial.print("Accelerometer data rate divisor set to: ");
  Serial.println(accel_divisor);
  Serial.print("Accelerometer data rate (Hz) is approximately: ");
  Serial.println(accel_rate);

  //  icm.setGyroRateDivisor(255);
  uint8_t gyro_divisor = icm.getGyroRateDivisor();
  float gyro_rate = 1100 / (1.0 + gyro_divisor);

  Serial.print("Gyro data rate divisor set to: ");
  Serial.println(gyro_divisor);
  Serial.print("Gyro data rate (Hz) is approximately: ");
  Serial.println(gyro_rate);
  Serial.println();
}





void accelloop() {

  //  /* Get a new normalized sensor event */
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  icm.getEvent(&accel, &gyro, &temp);

  delay(100);
}



// PROBLEM HERE WITH THE EVENT HANDLER !!!!!!!!!!!!!!!!!!!!

/*
float accelTemp() {
  return temp.temperature; // C
}

float accelX() {
  return accel.acceleration.x;  // m/s^2
}

float accelY() {
  return accel.acceleration.y;  // m/s^2
}

float accelZ() {
  return accel.acceleration.z;  // m/s^2
}


float gyroX() {
  return gyro.gyro.x // rads/s
}


float gyroY() {
  return gyro.gyro.y // rads/s
}


float gyroZ() {
  return gyro.gyro.z // rads/s
}
*/