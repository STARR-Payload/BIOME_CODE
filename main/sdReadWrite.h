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