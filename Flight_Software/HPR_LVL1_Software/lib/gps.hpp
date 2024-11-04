#include <vector>
#include <sstream>

struct Location {
    std::string latitude;
    std::string longitude;
    std::string altitude;
    std::string time;
    bool valid;
};

class GPS{
    private:
    public:
        std::vector<std::string> GPS::parsed_data(std::string& str);
        Location GPS::get_loco(std::string& str);
        bool GPS::startup(Location loco);
};

//Parses the data into an array of strings with fields
std::vector<std::string> GPS::parsed_data(std::string& str)
{
    std::vector<std::string> result;
    size_t pos = 0;
    std::string part;

    while ((pos = str.find(',')) != std::string::npos)
    {
        part = str.substr(0,pos);
        result.push_back(part);
        str.erase(0, pos + 1);
    }
    result.push_back(str);

    return result;
}

Location GPS::get_loco(std::string& str)
{
    struct Location loco;
    std::vector<std::string> fields = parsed_data(str);
    /*
        TODO get latitude, longitude, and altitude
            make a case statement for:
                $GPGGA sentance--Done
                $GPGGA,170834,4124.8963,N,08151.6838,W,1,05,1.5,280.2,M,-34.0,M,,,*59
                $GPRMC sentance--InProg
                $GPGSV sentance--InProg
                $GPGLL sentance--InProg
                $GPVTG sentance--InProg
                $GPGSA sentance--InProg
    */ 
    if (fields[0] == "$GPGGA")
    {   
        //getting values of latitude and longitude as well as if the gps signal is valid(All are strings)
        loco.latitude = fields[2].substr(0, fields[2].length() - (fields[2].length() - fields[2].find("."))) + "d " + fields[2].substr(fields[2].find(".") + 1,7) + "' " + fields[3];
        loco.longitude = fields[4].substr(0, fields[4].length() - (fields[4].length() - fields[4].find("."))) + "d " + fields[4].substr(fields[4].find(".") +1,7) + "' " + fields[5];
        loco.time = fields[1].substr(0,2) + ":" + fields[1].substr(2,2) + ":" + fields[1].substr(4,2) + " UTC";
        loco.altitude = fields[9];
        if ((fields[6] == "1") || (fields[6] == "2"))
        {
            loco.valid = true;
        } else {
            loco.valid = false;
        }
    //Not sure if I should code all of these but I will comment them out just in case
    // } else if (fields[0] == "$GPRMC")
    // {

    // } else if (fields[0] == "$GPGSV")
    // {

    // } else if (fields[0] == "$GPGLL")
    // {

    // } else if (fields[0] == "$GPVTG")
    // {

    // } else if (fields[0] == "$GPGSA")
    // {

    } else {
        //Catch all (error message)
        fprintf(stderr, "Invalid sentance type.\n");
    }

    return loco;
}

bool GPS::startup(Location loco)
{
    if (loco.valid == true)
    {
        return true;
    } else {
        return false;
    }
}

/*
    How to Use:
        1. In the main loop, first check if the gps signal is available. ex:
            if (gpsSerial.available()) {
                //Do Stuff
            } else {
                Serial.println("Error Message");
            }
        2. If the gpsSerial is available, we have access to the location variables, latitude, longitude, altitude, and time
            String nmea = gpsSerial.readStringUntil('\n'); //contains the information we need
            Location loc = GPS::get_loco(nmea);            //parses the line and stores it into a location variable
            
            if (loc.valid) {                               //If the GPS is fixed(valid), we can print out and see it's contents 
                Serial.print("Latitude: ");                //So far they aren't numerical yet, I will change this soon but this is just to view its contents
                Serial.println(loc.latitude);
                Serial.print("Longitude: ");
                Serial.println(loc.longitude);
                Serial.print("Altitude: ");
                Serial.println(loc.altitude);

            } else {                                       //If signal is not fixed, it is invalid, so we can't use it
                Serial.println("Invalid or No Fix");
            }
*/