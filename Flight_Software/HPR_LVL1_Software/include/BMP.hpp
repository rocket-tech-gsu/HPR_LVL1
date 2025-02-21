/* 
developed by "Rocket Technologies GSU"
This Library is a wrapper on Popular Arduino Libraries.

DO NOT need Connections Information becuase it uses:
- I2C Protocol
Meaning 127 devices can connect on one common SDA(Serial Data Line)
Each Device has a unique address though.

Default Wiring & Address:
SDA on BMP280 - GPIO 21
Default Memory Address of BMP280 - 0x76

*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

class BMP280Sensor {
public:
bool startup();         // Initialize sensor
float readTemperature();   // Read temperature
float readPressure();      // Read pressure
float readAltitude(float seaLevelPressure = 1013.25); // Read altitude


private:
Adafruit_BMP280 bmp;
// BMP280 object (from Adafruit library)
};

bool BMP280Sensor::startup() {
    // Check if the BMP280 sensor is connected
    Wire.begin(); // Initialize I2C communication
    if (!bmp.begin(0x76)) { // 0x76 is the I2C address of BMP280
        Serial.println("BMP280 not detected! Check wiring.");
        return false;
    }
    Serial.println("BMP280 sensor detected!");

    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */                
                Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    return true;
}

float BMP280Sensor::readTemperature() {
  return bmp.readTemperature();
  //return type is in Celcius
}

float BMP280Sensor::readPressure() {
  return bmp.readPressure();
  //return type is in Pa
}

float BMP280Sensor::readAltitude(float seaLevelPressure) {
  return bmp.readAltitude(seaLevelPressure);
  //return type is in meters
}