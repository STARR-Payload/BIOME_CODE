//http://eggtimerrocketry.com/wp-content/uploads/2021/05/Eggtimer-Telemetry-Data-Format.pdf

// Trigger Bytes 
static const char FlightTimeChar = '#'; // Bytes Initial Waiting Launched NoseOver Drogue FS/Main Landed
static const char AltitudeChar = '{'; // Altitude/100 Feet
static const char PreD3AltitudeChar = '<'; // Altitude (Quark Pre-D3)
static const char VelocityChar = '-'; // Velocity fps
static const char AccelerationChar = '*'; // Acceleration * 10 fps2
static const char FlightPhaseChar = '@'; // Flight Phase state
static const char ChannelEnabledChar = '~'; // Channel Enabled state
static const char ChannelDisabledChar = '-'; // Channel Disabled state
static const char ChannelFiredChar = 'n'; // Channel Fired state
static const char TemperatureChar = '!'; // Temperature * 10 C
static const char NameCallsignChar = '='; // Name/Callsign text
static const char BatteryVoltageChar = '?'; // Battery Voltage * 10 V
static const char ApogeeChar = '%'; // Apogee ft
static const char MaxVelocityChar = '^'; // Max Velocity fps
static const char MaxAccelerationChar = '['; // Max Acceleration G's

static const char TerminatorByte = '>'; // Terminator byte - ohhhh no whats happening I feel different..... ARGGGG I AM THE TERMINATOR, ILL BE BACK

// Data Length in Bytes
int FlightTimeLength = 6; // Flight Time (secs) - 6 bytes
int AltitudeLength = 5; // Altitude/100 Feet - 5 bytes
int PreD3AltitudeLength = 7; // Altitude (Quark Pre-D3) - 7 bytes
int VelocityLength = 7; // Velocity (fps) - 7 bytes
int AccelerationLength = 6; // Acceleration (10 fps2) - 6 bytes
int FlightPhaseLength = 3; // Flight Phase state - 3 bytes
int ChannelEnabledLength = 8; // Channel Enabled state - 8 bytes
int ChannelDisabledLength = 8; // Channel Disabled state - 8 bytes
int ChannelFiredLength = 4; // Channel Fired state - 4 bytes
int TemperatureLength = 6; // Temperature (10 C) - 6 bytes
int NameCallsignLength = 10; // Name/Callsign text - 10 bytes
int BatteryVoltageLength = 5; // Battery Voltage (10 V) - 5 bytes
int ApogeeLength = 7; // Apogee (ft) - 7 bytes
int MaxVelocityLength = 6; // Max Velocity (fps) - 6 bytes
int MaxAccelerationLength = 5; // Max Acceleration (G's) - 5 bytes


typedef struct dataPacket{
    char type;
    long long int data;
};


int read() {
    if (Serial.available() > 0) {
        
    }
}

