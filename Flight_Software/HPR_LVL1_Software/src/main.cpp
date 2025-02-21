#include <Arduino.h>
#include <../include/gps.hpp>
#include <../include/BMP.hpp>
#include <../include/SD_Card.hpp>
#include <../include/MPU6050.hpp>

// Pin definitions
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

// Global objects
HardwareSerial gpsSerial(1);
GPS gps(gpsSerial);
BMP280Sensor bmp;
MPU6050Sensor accelerometer;
SDCardManager sdCard(4);


//// TODO: Write a function for count down as per the protocol in the readme ////

// // Function to format data for SD card logging
// String formatDataString(String lat, String lon, float alt, float temp, float pressure, float* accel) {
//     String dataString = String(millis()) + ",";
//     dataString += lat + "," + lon + "," + String(alt) + ",";
//     dataString += String(temp) + "," + String(pressure) + ",";
//     dataString += String(accel[0]) + "," + String(accel[1]) + "," + String(accel[2]);
//     return dataString;
// }

void setup() {
    Serial.begin(115200);
    delay(1000);  // Give serial monitor time to start
    
    // Test GPS setup
    Serial.println("\n--- Testing GPS Setup ---");
    if (gps.startup(GPS_RX_PIN, GPS_TX_PIN)) {
        Serial.println("GPS initialized successfully");
    } else {
        Serial.println("GPS initialization failed");
    }
    
    // Test BMP280 setup
    Serial.println("\n--- Testing BMP280 Setup ---");
    if (bmp.startup()) {
        Serial.println("BMP280 initialized successfully");
    } else {
        Serial.println("BMP280 initialization failed");
    }
    
    // Test GY-61 setup
    Serial.println("\n--- Testing GY-61 Setup ---");
    if (accelerometer.startup()) {
        Serial.println("GY-61 initialized successfully");
    } else {
        Serial.println("GY-61 initialization failed");
    }
    
    // Test SD Card setup
    Serial.println("\n--- Testing SD Card Setup ---");
    sdCard.startup();
    
    sdCard.writeFile("/data.txt", "Hello, ESP32!\n");
    // Create a CSV for storing Sensor Data: "Sensors.csv"
    // sdCard.writeFile(".","Time,Latitude,Longitude,Altitude,Temperature,Pressure,AccelX,AccelY,AccelZ");
}

void loop() {
    static unsigned long lastPrint = 0;
    const unsigned long PRINT_INTERVAL = 1000; // Print every second
    
    if (millis() - lastPrint >= PRINT_INTERVAL) {
        lastPrint = millis();
        
        // GPS Data
        if (gpsSerial.available()) {
            String nmea = gpsSerial.readStringUntil('\n');
            if (nmea.startsWith("$GPGGA")) {
                String* parsed = gps.parsed_data(nmea);
                String latitude = gps.get_latitude(parsed);
                String longitude = gps.get_longitude(parsed);
                float gpsAltitude = gps.get_altitude(parsed);
                
                Serial.println("\n--- GPS Data ---");
                Serial.println("Latitude: " + latitude);
                Serial.println("Longitude: " + longitude);
                Serial.println("GPS Altitude: " + String(gpsAltitude) + "m");
                Serial.println("Fix Status: " + String(gps.is_fixed(parsed) ? "Fixed" : "No Fix"));
                
                delete[] parsed;
            }
        }
        
        // BMP280 Data
        float temperature = bmp.readTemperature();
        float pressure = bmp.readPressure();
        float bmpAltitude = bmp.readAltitude();
        
        Serial.println("\n--- BMP280 Data ---");
        Serial.println("Temperature: " + String(temperature) + "Â°C");
        Serial.println("Pressure: " + String(pressure) + "Pa");
        Serial.println("BMP Altitude: " + String(bmpAltitude) + "m");
        
        // Accelerometer Data
        Serial.println("\n--- Accelerometer Data ---");
        
        accelerometer.printReadings();
        SensorData accelerations = accelerometer.readSensor();

        // // Log data to SD card
        // if (gpsSerial.available()) {
        //     String nmea = gpsSerial.readStringUntil('\n');
        //     if (nmea.startsWith("$GPGGA")) {
        //         String* parsed = gps.parsed_data(nmea);
        //         String dataString = formatDataString(
        //             gps.get_latitude(parsed),
        //             gps.get_longitude(parsed),
        //             gps.get_altitude(parsed),
        //             temperature,
        //             pressure,
        //             accelerations
        //         );
        //         sdCard.Write(dataString);
        //         delete[] parsed;
        //     }
        // }
        
        Serial.println("\n------------------------");
    }
}