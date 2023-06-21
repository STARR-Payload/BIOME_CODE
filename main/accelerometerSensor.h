// ICM20649

#include <flagsapi.h>
#include <Adafruit_ICM20649.h>
#include <Adafruit_Sensor.h>


Adafruit_ICM20649 icm;
uint16_t measurement_delay_us = 65535; // Delay between measurements for testing

sensors_event_t accel;
sensors_event_t gyro;
sensors_event_t temp;




uint16_t ICM20649Setup(void) {
  
  //115200 baud rate 

  if (!icm.begin_I2C()) {
    return 1;
  }

  Serial.println("ICM20649 Found!");

  icm.setAccelRange(ICM20649_ACCEL_RANGE_16_G); 
    
  icm.setGyroRange(ICM20649_GYRO_RANGE_500_DPS); 
  
  uint16_t accel_divisor = icm.getAccelRateDivisor();
  float accel_rate = 1125 / (1.0 + accel_divisor);

  Serial.print("Accelerometer data rate divisor set to: ");
  Serial.println(accel_divisor);
  Serial.print("Accelerometer data rate (Hz) is approximately: ");
  Serial.println(accel_rate);

  uint8_t gyro_divisor = icm.getGyroRateDivisor();
  float gyro_rate = 1100 / (1.0 + gyro_divisor);

  Serial.print("Gyro data rate divisor set to: ");
  Serial.println(gyro_divisor);
  Serial.print("Gyro data rate (Hz) is approximately: ");
  Serial.println(gyro_rate);
  Serial.println();

  return 0;
}


uint16_t ICM20649readingCheck() {
  return icm.getEvent(&accel, &gyro, &temp);
}



sensors_vec_t ICM20469Accelread() {
  icm.getEvent(&accel, &gyro, &temp);
  return accel.acceleration;
}


sensors_vec_t ICM20469Gyroread() {
  icm.getEvent(&accel, &gyro, &temp);
  return gyro.gyro;
}



float ICM20469Tempread() {
  icm.getEvent(&accel, &gyro, &temp);
  return temp.temperature;
}



