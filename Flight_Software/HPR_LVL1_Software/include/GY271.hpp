#ifndef GY271_SENSOR_HPP
#define GY271_SENSOR_HPP

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_Sensor.h>
#include <math.h> // for atan2, PI

/*
  developed by "Rocket Technologies GSU"
  This Library is a wrapper on Popular Arduino Libraries.

  For the GY-271 Magnetometer Breakout Sensor using I2C.

  Default Wiring & Address:
    - SDA: GPIO 21
    - SCL: GPIO 22
    - HMC5883L I2C Address: 0x1E (handled internally by the Adafruit library)

  The library uses a declination angle (in radians) to correct the heading.
  Adjust the declination angle to match your geographic location.
*/

// Data structure for storing magnetometer readings
struct MagnetometerData {
    float x;       // Magnetic field along X-axis (uT)
    float y;       // Magnetic field along Y-axis (uT)
    float z;       // Magnetic field along Z-axis (uT)
    float heading; // Calculated heading (in degrees)
};

class GY271Sensor {
public:
    // Constructor: Initializes the sensor object with a unique ID.
    GY271Sensor() : mag(12345), declinationAngle(0.22) {}

    /**
     * @brief Initializes the magnetometer sensor.
     * 
     * This function begins I2C communication, initializes the sensor, and
     * displays its details via the Serial monitor.
     * 
     * @return true if the sensor is detected and initialized, false otherwise.
     */
    bool startup() {
        Wire.begin();  // Initialize I2C
        if (!mag.begin()) {
            Serial.println("GY271Sensor: No HMC5883 detected! Check wiring!");
            return false;
        }
        
        // Display sensor details for verification
        sensor_t sensor;
        mag.getSensor(&sensor);
        Serial.println("------------------------------------");
        Serial.print("Sensor:       "); Serial.println(sensor.name);
        Serial.print("Driver Ver:   "); Serial.println(sensor.version);
        Serial.print("Unique ID:    "); Serial.println(sensor.sensor_id);
        Serial.print("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
        Serial.print("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
        Serial.print("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
        Serial.println("------------------------------------");
        Serial.println("");
        delay(500);
        
        return true;
    }

    /**
     * @brief Reads the sensor and returns magnetometer data.
     * 
     * It retrieves the magnetic field measurements, calculates the heading 
     * (with declination correction), and returns the values in a MagnetometerData struct.
     * 
     * @return MagnetometerData containing x, y, z values (in micro-Tesla) and heading (in degrees).
     */
    MagnetometerData readSensor() {
        MagnetometerData data;
        sensors_event_t event;
        mag.getEvent(&event);
        
        data.x = event.magnetic.x;
        data.y = event.magnetic.y;
        data.z = event.magnetic.z;
        
        // Calculate heading in radians
        float heading = atan2(event.magnetic.y, event.magnetic.x);
        // Apply declination correction
        heading += declinationAngle;
        
        // Normalize to 0 ~ 2PI
        if (heading < 0)
            heading += 2 * PI;
        if (heading > 2 * PI)
            heading -= 2 * PI;
        
        // Convert radians to degrees
        data.heading = heading * 180.0 / PI;
        return data;
    }

private:
    // Instance of the Adafruit_HMC5883_Unified sensor
    Adafruit_HMC5883_Unified mag;
    // Declination angle in radians (default ~0.22 rad; adjust as needed)
    float declinationAngle;
};

#endif // GY271_SENSOR_HPP
