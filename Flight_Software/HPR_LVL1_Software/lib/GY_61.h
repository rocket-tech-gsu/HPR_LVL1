#include <Arduino.h>

class GY_61{
    private:
        // Pin assignments
        const int xPin = 18;  // X output connected to GPIO18
        const int yPin = 19;  // Y output connected to GPIO19
        const int zPin = 21;  // Z output connected to GPIO21
    public:

        // Constants for GY-61 (ADXL335)
        const float ZERO_G_VOLTAGE = 1.65;  // Zero-g voltage (1.65V at 3.3V supply)
        const float GRAVITY = 9.81;         // Gravity constant in m/s^2
        float SENSITIVITY = 0.3;      // Sensitivity (0.3 V/g)

        // Methods Declaration
        float readVoltage(int pin);
        float *readVoltages();
        float voltageToAcceleration(float voltage);
        float *ReadAccelerations(void);
        bool startup(void);
};


bool GY_61::startup(void){
    float VectorSum;
    // try to read voltage values
    if (8 <= VectorSum && VectorSum <= 12){
        // if we can read it, then GY_61 is working, we'll retrun true
        return true;
    }
    return false;
    // return true;
}

// Read analog voltage from a pin
float GY_61::readVoltage(int pin) {
    int rawValue = analogRead(pin);                   // Read raw ADC value (0 to 4095)
    return (rawValue / 4095.0) * 3.3;                 // Convert to voltage (3.3V range)
}


// Voltages to acceleration in m/s^2
float GY_61::voltageToAcceleration(float voltage) {
    return ((voltage - ZERO_G_VOLTAGE) / SENSITIVITY) * GRAVITY;
}

float *GY_61::ReadAccelerations(void) {
    // Read voltages from the sensor
    float xVoltage = readVoltage(xPin);
    float yVoltage = readVoltage(yPin);
    float zVoltage = readVoltage(zPin);

    // Convert voltages to acceleration (m/s^2)
    float xAccel = voltageToAcceleration(xVoltage);
    float yAccel = voltageToAcceleration(yVoltage);
    float zAccel = voltageToAcceleration(zVoltage);

    // Print acceleration values
    Serial.print("X-Axis: "); Serial.print(xAccel); Serial.print(" m/s^2, ");
    Serial.print("Y-Axis: "); Serial.print(yAccel); Serial.print(" m/s^2, ");
    Serial.print("Z-Axis: "); Serial.println(zAccel); Serial.print(" m/s^2\n");

    delay(500);  // Wait before the next reading
    float accelerations[] = {xAccel,yAccel,zAccel};
    return accelerations;
}

// // Store all three voltages in a list for easy manipulation
// float *GY_61::readVoltages() {
//     // Return a list of Acc_X, Acc_Y, Acc_Z
//     float accelerations[] = {readVoltage(xPin), readVoltage(yPin), readVoltage(zPin)};
//     return accelerations;
// }
