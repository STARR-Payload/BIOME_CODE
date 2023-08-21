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