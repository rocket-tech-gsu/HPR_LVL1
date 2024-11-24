//  This file is supposed to be a test file for GY_61 Module:
//  It is a part of unit testing, that we do here at @RocketTech!

#include <../lib/GY_61.h>

// Initialize the GY_61 Object:
GY_61 accelerometer;
float *accelerations;

// We will return 0 for failure, 1 for success:
int Setup(){
    Serial.begin(115200);
    if (!accelerometer.startup()){
        return 0;
    }
}

int Loop(){
    accelerations = accelerometer.ReadAccelerations();
    Serial.printf("Acceleration along x is: %f, along y is: %f, along z is: %f", accelerations[0], accelerations[1], accelerations[2]);
    delay(150);
}
