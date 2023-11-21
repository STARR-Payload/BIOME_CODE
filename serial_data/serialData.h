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



//http://eggtimerrocketry.com/wp-content/uploads/2021/05/Eggtimer-Telemetry-Data-Format.pdf

static const char TerminatorByte = '>'; // Terminator byte - ohhhh no whats happening I feel different..... ARGGGG I AM THE TERMINATOR, ILL BE BACK

typedef struct dataPacket{
    char type;
    long long int data;
} dataPacket;

int serialDataLeft() {
  return Serial.available() > 0 ? 1 : 0;
}

dataPacket serialRead() {
    String DataStr;
    dataPacket Datapacket;
    char startByte = Serial.read();
    DataStr = Serial.readStringUntil(TerminatorByte);
    Datapacket.type = startByte;
    int DataInt = DataStr.toInt();
    Datapacket.data = DataInt;
    return Datapacket;
}