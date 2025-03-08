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


bool Sensor_tests = true;
const int BuzzerPIN = 12;

bool beforeFlight = false;
bool inFlight = false;
bool afterApogee = false;

// Flight detection variables
int indexer = 0;
const int N = 5;
const int M = 8;
float currMean = 0.0;
float prevMean = 0.0;
float currPressureArray[N]; // Using N
float prevPressureArray[N]; // Using N
float pressure;
float bmpAltitude;
float temperature;

float currLandingArray[M]; // Using M
float prevLandingArray[M]; // Using M

float prevLandingMean = 0.0;
float currLandingMean = 0.0;
float landingVariance = 0.0;
int landed_counter = 0;

// Event Status Variables:
bool Mission_Completed = false;
bool Apogee = false;
bool isLaunched = false;
bool isLanded = false;

int Threshold = 20;
int launch_counter = 0;
int apogee_counter = 0;
bool postVarianceCheck = false;
unsigned long startTime = 0;

// TODO: Write a function for count down as per the protocol in the readme ////

void setup() {
    Serial.begin(115200);
    delay(1000);  // Give serial monitor time to start
    
    // Test GPS setup
    Serial.println("\n--- Testing GPS Setup ---");
    if (gps.startup(GPS_RX_PIN, GPS_TX_PIN)) {
        Serial.println("GPS initialized successfully");
    } else {
        Serial.println("GPS initialization failed");
        Sensor_tests = false;
    }
    
    // Test BMP280 setup
    Serial.println("\n--- Testing BMP280 Setup ---");
    if (bmp.startup()) {
        Serial.println("BMP280 initialized successfully");
    } else {
        Serial.println("BMP280 initialization failed");
        Sensor_tests = false;
    }
    
    // Test GY-61 setup
    Serial.println("\n--- Testing GY-61 Setup ---");
    if (accelerometer.startup()) {
        Serial.println("GY-61 initialized successfully");
    } else {
        Serial.println("GY-61 initialization failed");
        Sensor_tests = false;
    }
    
    ////////// All Sensors Successfull: //////////
    if (Sensor_tests == false){ // two beeps
        tone(BuzzerPIN,1000);
        delay(2000);
        noTone(BuzzerPIN);
        delay(1000);
        tone(BuzzerPIN, 1000);
        delay(2000);
        noTone(BuzzerPIN);
    }
    else{
        tone(BuzzerPIN,4000); // Beep 1
        delay(500);
        noTone(BuzzerPIN);
        delay(500);
        tone(BuzzerPIN,4000); // Beep 2
        delay(500);
        noTone(BuzzerPIN);
        delay(500);
        tone(BuzzerPIN,4000); // Beep 3
        delay(500);
        noTone(BuzzerPIN);
        delay(500);
    }
    
    // Test SD Card setup
    Serial.println("\n--- Testing SD Card Setup ---");
    sdCard.startup();
    
    // Write Test:
    sdCard.writeFile("/data.txt", "Hello, ESP32!\n");
    Serial.println("\t Write Function Works");
    
    
    // Append Test:
    sdCard.appendFile("/data.txt", "This is an APPENDED test line\n");
    Serial.println("\t Append Function Works");
    
    // Read Test:
    String content = sdCard.readFile("/data.txt");
    if (content == "Hello, ESP32!\n"){
        Serial.println("");
    }
    Serial.println("File content:");
    Serial.println(content);
    
    ////////// Data Logging Successfull: //////////
    if (Sensor_tests == false){ // two beeps
        tone(BuzzerPIN,1000);   // Long Beep 1
        delay(2000);
        noTone(BuzzerPIN);
        delay(1000);
        tone(BuzzerPIN, 1000);  // Long Beep 2
        delay(2000);
        noTone(BuzzerPIN);
        delay(1000);
        tone(BuzzerPIN, 1000);  // Long Beep 3
        delay(2000);
        noTone(BuzzerPIN);
    }
    else{
        tone(BuzzerPIN,4000); // Beep 1
        delay(500);
        noTone(BuzzerPIN);
        delay(500);
        tone(BuzzerPIN,4000); // Beep 2
        delay(500);
        noTone(BuzzerPIN);
        delay(500);
        tone(BuzzerPIN,4000); // Beep 3
        delay(500);
        noTone(BuzzerPIN);
        delay(500);
        tone(BuzzerPIN,4000); // Beep 4
        delay(500);
        noTone(BuzzerPIN);
        delay(500);
    }
    
    
    // Create a CSV for storing Sensor Data: "Sensors.csv"
    sdCard.writeFile("/data.csv","Time,Latitude,Longitude,Altitude,Temperature,Pressure,AccelX,AccelY,AccelZ,GyroX,GyroY,GyroZ,MPU_Temperature");
}

void loop() {
    if (Mission_Completed == false){
    static unsigned long lastPrint = 0;
    const unsigned long PRINT_INTERVAL = 500; // Print every second
    unsigned long currTime = millis();
    
    // Print sensor data at regular intervals
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
        temperature = bmp.readTemperature();
        pressure = bmp.readPressure();
        bmpAltitude = bmp.readAltitude();
        
        Serial.println("\n--- BMP280 Data ---");
        Serial.println("Temperature: " + String(temperature) + "°C");
        Serial.println("Pressure: " + String(pressure) + "Pa");
        Serial.println("BMP Altitude: " + String(bmpAltitude) + "m");
        
        // Accelerometer Data
        Serial.println("\n--- Accelerometer Data ---");
        SensorData accelerations = accelerometer.readSensor();
        
        // Flight state
        Serial.println("\n--- Flight State ---");
        Serial.println("Launched: " + String(isLaunched ? "Yes" : "No"));
        Serial.println("Apogee Reached: " + String(Apogee ? "Yes" : "No"));
        Serial.println("Landed: " + String(isLanded ? "Yes" : "No"));
        
        Serial.println("\n------------------------");
        
        // Log data to SD card with flight state
        String flightState = "0";
        if (isLaunched) flightState = "1";
        if (Apogee) flightState = "2";
        if (isLanded) flightState = "3";

        // const char *dataString = "abc";
        String dataString = String(millis()) + "," +
                           String(gpsSerial.available() ? gps.get_latitude(gps.parsed_data(gpsSerial.readStringUntil('\n'))) : "0") + "," +
                           String(gpsSerial.available() ? gps.get_longitude(gps.parsed_data(gpsSerial.readStringUntil('\n'))) : "0") + "," +
                           String(bmpAltitude) + "," +
                           String(temperature) + "," +
                           String(pressure) + "," +
                           String(accelerations.accelX) + "," +
                           String(accelerations.accelY) + "," +
                           String(accelerations.accelZ) + "," +
                           String(accelerations.gyroX) + "," +
                           String(accelerations.gyroY) + "," +
                           String(accelerations.gyroZ) + "," +
                           String(accelerations.temperature) + "," +
                           flightState;
        Serial.println(dataString);
        sdCard.writeFile("/data.txt", dataString);
    }

    /////////////// EVENT SEQUENCE DETECTION ///////////////
    // Flight detection logic
    int index = indexer % N;
    int landingIndex = indexer % M;

    if (indexer < 2 * M) {
            if (indexer < M) {
                prevLandingArray[landingIndex] = pressure;
            }
            else if (indexer >= M) {
                currLandingArray[landingIndex] = pressure;
            }

            if (indexer < N) {
                prevPressureArray[index] = pressure;
            }
            else if (indexer >= N && indexer < N * 2) {
                currPressureArray[index] = pressure;
        }
    }
    else {
        // Calculate landing means
        for (int i = 0; i < M; i++) {
            if (i < M) {
                currLandingMean += currLandingArray[i];
                prevLandingMean += prevLandingArray[i];
            }
        }
        currLandingMean /= M;
        prevLandingMean /= M;
        
        // Calculate landing variance
        if (landingIndex != 0 && postVarianceCheck == false) {
            float diff = pressure - currLandingMean;
            landingVariance += diff * diff;
        }
        else if (landingIndex == 0) {
            landingVariance = sqrt(landingVariance);
            landingVariance /= (M - 1);
            postVarianceCheck = true;
        }


        // Calculate current and previous means
        for (int i = 0; i < N; i++) {
            currMean += currPressureArray[i];
            prevMean += prevPressureArray[i];
        }
        
        // Apogee and flight detection
        prevPressureArray[index] = currPressureArray[index];
        currPressureArray[index] = pressure;
        
        currMean /= N;
        prevMean /= N;
        // Serial.println("Previous Mean =" + String(prevMean));

        prevLandingArray[landingIndex] = currLandingArray[landingIndex];
        currLandingArray[landingIndex] = pressure;

        // Launch detection
        if (isLaunched == false) {
            if (currMean < prevMean) {
                launch_counter += 1;
            }
            else {
                launch_counter = 0;
            }
            if (launch_counter >= Threshold) {
                isLaunched = true;
                Serial.println("\n\nLAUNCH DETECTED!\n\n");
            }
            Serial.println("Launch Counter = " + String(launch_counter));
            // Serial.println("Previous Mean =" + String(prevMean));
            // Serial.println("Current Mean = " + String(currMean));
        }

        // Apogee detection
        if (Apogee == false && isLaunched == true) {
            if (currMean > prevMean) {
                apogee_counter += 1;
            }
            else {
                apogee_counter = 0;
            }
            if (apogee_counter >= Threshold) {
                Apogee = true;
                Serial.println("APOGEE DETECTED!");
            }
        }

        // Landing detection
        if (Apogee == true && isLanded == false) {
            if (abs(currLandingMean - prevLandingMean) <= landingVariance) {
                landed_counter += 1;
            }
            else {
                landed_counter = 0;
            }
            if (landed_counter >= Threshold) {
                isLanded = true;
                Mission_Completed = true;

                Serial.println("LANDING DETECTED!");
            }
        }
    }
    
    // Reset calculation variables for next iteration
    currMean = 0;
    prevMean = 0;
    currLandingMean = 0;
    prevLandingMean = 0;
    indexer += 1;

}
}