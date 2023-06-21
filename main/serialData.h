//http://eggtimerrocketry.com/wp-content/uploads/2021/05/Eggtimer-Telemetry-Data-Format.pdf

// Trigger Bytes 

/*
static const char FlightTimeChar = '#'; // Bytes Initial Waiting Launched NoseOver Drogue FS/Main Landed
static const char AltitudeChar = '{'; // Altitude/100 Feet
static const char PreD3AltitudeChar = '<'; // Altitude (Quark Pre-D3)
static const char VelocityChar = '-'; // Velocity fps
static const char FlightPhaseChar = '@'; // Flight Phase state
static const char ChannelEnabledChar = '~'; // Channel Enabled state
static const char ChannelDisabledChar = '-'; // Channel Disabled state
static const char ChannelFiredChar = 'n'; // Channel Fired state
static const char TemperatureChar = '!'; // Temperature * 10 C
static const char NameCallsignChar = '='; // Name/Callsign text
static const char BatteryVoltageChar = '?'; // Battery Voltage * 10 V
static const char ApogeeChar = '%'; // Apogee ft
static const char MaxVelocityChar = '^'; // Max Velocity fps
*/

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

