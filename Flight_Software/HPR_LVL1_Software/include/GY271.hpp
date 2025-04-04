#include <Wire.h>
#include <HMC5883L_Simple.h>

HMC5883L_Simple Compass;

struct SensorData{
    float x;
    float y;
    float z;
    float heading;

}

class Magnetometer {
    

public:
    int x;
    int y;
    int z;
    SensorData val;
    bool startup();
    SensorData getReadings();

private:
};

bool Magnetometer::startup() {
    Serial.begin(9600);
    Wire.begin();
    
    // Initialize Compass settings
    if(!Compass.SetDeclination(23, 35, 'E')||!Compass.SetSamplingMode(COMPASS_SINGLE)
    ||!Compass.SetScale(COMPASS_SCALE_088)||!Compass.SetOrientation(COMPASS_HORIZONTAL_X_NORTH)
    ||Compass.calibrate()){
        return false;
    }
    //getCalibrationOffsets() returns the calibration offsets
    //SetDataRate(rate) can also be initialized for 10/50/100hz
    return true;
}

SensorData Magnetometer::getReadings() {
    val.heading = Compass.GetHeadingDegrees();
    compass.GetRawAxes(&val.x, &val.y, &val.z);

    return val;
    
}


//usage>>




//the magnetometer has two modes for sampling: single and continous. The difference being that continuous is always reading values, whilst single only samples when you call it. 

// Magnetic Declination is the correction applied according to your present location, so it should be tuned to the location of the launch site in the final flight software.

// The scale is sorted from most sensitive to least sensitive, there is a default option, but if we want to account for high noise probability we should choose one on the upper bound of these options: Options are 088, 130 (default), 190, 250, 400, 470, 560, 810

// Orientation: Allows to configure different mounting axis: 

// COMPASS_HORIZONTAL_X_NORTH (default), the compass is oriented horizontally, top-side up. when pointing North the X silkscreen arrow will point North

// COMPASS_HORIZONTAL_Y_NORTH, top-side up, Y is the needle,when pointing North the Y silkscreen arrow will point North

// COMPASS_VERTICAL_X_EAST,    vertically mounted (tall) looking at the top side, when facing North the X silkscreen arrow will point East

// COMPASS_VERTICAL_Y_WEST,    vertically mounted (wide) looking at the top side, when facing North the Y silkscreen arrow will point West
// GY-271 set up and usage^^^