// SD

#include <flagsapi.h>
#include <SD.h>
#define DATASECTIONLENGTH 24
File dataFile;


uint16_t SDsetup() {
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    return 1;
  }
  Serial.println("Initialization done.");
  return 0;
}

void SDWrite(long long int data[DATASECTIONLENGTH], String file){

    dataFile = SD.open(file, FILE_WRITE);

    if (dataFile) {
        Serial.print("SD WRITE");
        for (int i = 0; i < DATASECTIONLENGTH; i++){
          dataFile.print(data[i]);
        }
        dataFile.println();
        dataFile.close();
    } else {
        Serial.println("error opening test.txt");
  }
}