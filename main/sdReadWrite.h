#include <flagsapi.h>
#include <SD.h>
#define DATASECTIONLENGTH 24
File myFile;

uint16_t SDsetup() {
  if (!SD.begin(4)) {
    return 1;
  }
  Serial.println("SD Found!");
  Serial.println("");
  return 0;
}

void SDWrite(float data[DATASECTIONLENGTH], String file) { // DONE
  /* Params: 
  1) data array that contains all sensor data for that interval
  2) file object to write too

  Function:
  1) 

  Return:
  1) VOID
  */

  myFile = SD.open(file, FILE_WRITE);

  for (int i = 0; i < DATASECTIONLENGTH; i++) {
    if (i == 0) { 
      myFile.println(data[i]);
      } else { 
      myFile.print(","); 
      myFile.print(data[i]);
    }
  }
  // close the file:
  myFile.close();
       
}