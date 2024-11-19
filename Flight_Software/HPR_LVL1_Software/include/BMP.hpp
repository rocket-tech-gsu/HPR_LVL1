#include <Arduino.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>

class BMP280Sensor {
public:
    int CS_PIN = 10;
    int MOSI_PIN = 11;  
    int MISO_PIN = 13;
    int SCK_PIN = 13;
    bool startup();         // Initialize sensor
    float readTemperature();   // Read temperature
    float readPressure();      // Read pressure
    float readAltitude(float seaLevelPressure = 1013.25); // Read altitude


private:
    Adafruit_BMP280 bmp;
         // BMP280 object (from Adafruit library)
};

bool BMP280Sensor::startup() {
    if (!bmp.begin(CS_PIN)) {  // Initialize with SPI pins
        return false;
    }
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