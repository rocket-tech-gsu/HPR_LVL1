#include <Arduino.h>
#include <HardwareSerial.h>

class GPS{
    private:
        int RX = 16;
        int TX = 17;

        HardwareSerial &gpsSerial;

    public:
        GPS(HardwareSerial &serial) : gpsSerial(serial) {}

        HardwareSerial &getGPSSerial();

        void set_rx_tx(int r, int t);
        int get_rx();
        int get_tx();
        String *parsed_data(String nmea);
        String get_latitude(String* fields);
        String get_longitude(String* fields);
        float get_altitude(String* fields);
        bool is_fixed(String* fields); 
        bool startup(); // To handle calls without arguments(default args will become RX, TX)
        bool startup(int r, int t);     
};

// Parses the data into an array of strings with fields

HardwareSerial& GPS::getGPSSerial()
{ 
    return gpsSerial; 
}

void GPS::set_rx_tx(int r, int t)
{
    RX = r;
    TX = t;
}
int GPS::get_rx()
{
    return RX;
}
int GPS::get_tx()
{
    return TX;
}
bool GPS::startup(){
    return startup(RX, TX);
}
bool GPS::startup(int r, int t)
{
    try{
        TX = t;
        RX = r;

        gpsSerial = HardwareSerial(1);
        gpsSerial.begin(9600, SERIAL_8N1, TX, RX);

        // Add the code you provided
        gpsSerial.println("$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"); // Set NMEA output
        gpsSerial.println("$PMTK220,1000*1F"); // Set 1 Hz update rate
        return true;
    } catch(bool) {
        Serial.printf(" GPS Initilization Failed ");
        return false;
    }
    
}

String* GPS::parsed_data(String nmea) {
    String* fields = new String[15];  // Create a dynamic array for fields
    if (nmea.startsWith("$GPGGA")) {
        int nxt_index = 0;
        int substr_start = 0;

        for (int i = 0; i < nmea.length(); i++) {
            if (nmea.charAt(i) == ',' || i == nmea.length() - 1) {
                if (i == nmea.length() - 1) {
                    i++; // Include last character if we reach the end without a comma
                }

                if (nxt_index < 15) { // Avoid overflow
                    fields[nxt_index] = nmea.substring(substr_start, i);
                    nxt_index++;
                }

                substr_start = i + 1; // Move start to character after comma
            }
        }
    }
    return fields;
}


String GPS::get_latitude(String* fields)
{
    if (fields[0].equals("$GPGGA") && !(fields[2].equals("")))
    {
        //return fields[2] + ", " + fields[3];
        //    **Conversion
        float decimal = fields[2].toFloat();
        int degrees = ((int)decimal / 100);
        int minutes = (int)(decimal - 100*degrees);
        float seconds = (decimal - trunc(decimal))*60;
        return String(degrees) + "°" + String(minutes) + "\'" + String(seconds) + "\"" + fields[3]; 
        return String(degrees) + "°";
    } else {
        return "No info on Latitude";
    }
}
String GPS::get_longitude(String* fields)
{
    if (fields[0].equals("$GPGGA") && !(fields[4].equals("")))
    {
        //return fields[4] + ", " + fields[5];
        //Conversion
        float decimal = fields[4].toFloat();
        int degrees = ((int)decimal / 100);
        int minutes = (int)(decimal - 100*degrees);
        float seconds = (decimal - trunc(decimal))*60;
        return String(degrees) + "°" + String(minutes) + "\'" + String(seconds) + "\"" + fields[5]; 
    } else {
        return "No info on Longitude";
    }
    
}
float GPS::get_altitude(String* fields)
{
    if (!fields[9].equals(""))
    {
        return fields[9].toFloat();
    } else {
        return -1.00;
    }
}
bool GPS::is_fixed(String* fields)
{
    if ((fields[6] == "1") || (fields[6] == "2"))
    {
        return true;
    } else {
        return false;
    }
}

/*
    How to use:

    sample code(main.cpp)

    #include <gps.hpp>
    #include <HardwareSerial.h>

    #define GPS_RX_PIN 16  // GPS TX pin to ESP32 RX (GPIO 0)
    #define GPS_TX_PIN 17  // GPS RX pin to ESP32 TX (GPIO 4)

    GPS gps(Serial1);  // Initialize GPS with Serial1

    HardwareSerial gpsSerial(1);


    void setup() {

        Serial.begin(115200);
        gps.startup(GPS_RX_PIN, GPS_TX_PIN);
        // int RX = 4;
        // int TX = 0;

        // Serial.begin(115200);  // Serial Monitor output
        // gpsSerial.begin(9600, SERIAL_8N1, RX, TX);
    }



    void loop() {
        if (gps.getGPSSerial().available()) {  // Check if there's GPS data available
            String nmeaSentence = gps.getGPSSerial().readStringUntil('\n');  // Read one NMEA sentence
            // Serial.print("NMEA Sentence: ");  // Print the NMEA sentence
            // Serial.println(nmeaSentence);

            // Optional: Check if the sentence is of type GPGGA
            if (nmeaSentence.startsWith("$GPGGA")) {
                Serial.println("GPGGA Sentence Detected!");
                Serial.println(gps.get_latitude(gps.parsed_data(nmeaSentence)));
                Serial.println(gps.get_longitude(gps.parsed_data(nmeaSentence)));
                Serial.println(gps.get_altitude(gps.parsed_data(nmeaSentence)));
                Serial.println(gps.parsed_data(nmeaSentence)[0]);
            }
        }

        delay(10);  // Delay for readability
    }
*/
