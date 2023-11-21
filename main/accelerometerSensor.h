// ICM20649
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

#include <flagsapi.h>
#include <Adafruit_ICM20649.h>
#include <Adafruit_Sensor.h>
Adafruit_ICM20649 icm;
sensors_event_t accel;
sensors_event_t gyro;
sensors_event_t temp;


uint16_t ICM20649Setup(void) {

  if (!icm.begin_I2C()) {
    return 1;
  }

  Serial.println("ICM20649 Found!");

  icm.setAccelRange(ICM20649_ACCEL_RANGE_30_G); 
    
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
  return !(icm.getEvent(&accel, &gyro, &temp));
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

float ICM20469NormVector() {
  icm.getEvent(&accel, &gyro, &temp);
  return accel.acceleration.y + accel.acceleration.x + accel.acceleration.z;

}