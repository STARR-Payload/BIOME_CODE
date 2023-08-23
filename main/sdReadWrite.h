#include <flagsapi.h>
#include <SD.h>
#define DATASECTIONLENGTH 22



uint16_t SDsetup() {
  if (!SD.begin(4)) {
    return 1;
  }
  Serial.println("SD Found!");
  Serial.println("");
  if (SD.exists("STARDATA.txt")) SD.remove("STARDATA.txt");
  return 0;
}

/*
 * Function:  SDWrite 
 * --------------------
 *  Writes all sensor data to SD card in correct format
 *
 *  data, file: data array consisting of all sensor results, file is a file object to write to 
 *
 *  returns: VOID
 */
void SDWrite(float data[DATASECTIONLENGTH], String file) { 

  File myFile = SD.open("STARDATA.txt", FILE_WRITE);
  if (myFile) {
    for (int i = 0; i < DATASECTIONLENGTH; i++) {
      if (i == 0) { 
        myFile.print(data[i]);
        } else { 
        myFile.print(","); 
        myFile.print(data[i]);
      }
    } 
    myFile.println("");
  }
  // close the file:
  myFile.close();
       
}