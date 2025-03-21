#include <Arduino.h>
#include <cmath>
#include <algorithm> // For std::copy
#include <../include/gps.hpp>
#include <../include/BMP.hpp>
#include <../include/SD_Card.hpp>
#include <../include/MPU6050.hpp>

// Pin definitions
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define CSV_BUFFER_SIZE 160
#define PRESSURE_BUFFER_SIZE 30
#define PRESSURE_WINDOW_SIZE 5

// Global objects
HardwareSerial gpsSerial(1);
GPS gps(gpsSerial);
BMP280Sensor bmp;
MPU6050Sensor accelerometer;
SDCardManager sdCard(4);
static int loop_counter = 0;
static bool pressures_populated = false;
static bool std_populated = false;


// Sensor Data Variables:
static bool Sensor_tests = true;
static const int BuzzerPIN = 12;
static float pressure;
static float bmpAltitude;
static float temperature;
static unsigned long startTime = 0;
static SensorData accelerations;

static char csvBuffer[CSV_BUFFER_SIZE];
static float Pressures[PRESSURE_BUFFER_SIZE];
static float Pressures_window1[PRESSURE_WINDOW_SIZE];
static float Pressures_window2[PRESSURE_WINDOW_SIZE];
static float pressure_old_mean;
static float pressure_new_mean;

static float acc_mag;
static float acc_threshold = 9.81*1.5;

static bool Launched = false;
static bool Apogee = false;
static bool Landed = false;


static int counter_threshold = 5;
static int landing_counter_threshold = 10;

static int launchCounter;
static int apogeeCounter;
static int landedCounter;

static float pressureStd_new;
static float pressureStd_old;

String* parsed;
String latitude;
String longitude;
float gpsAltitude;

// Function Declarations
void pressButton();
float calculateMean(float arr[], int size);
float calculateStd(float arr[], int size);
float calculateMag(float arr[], int size);
void leftShiftArray_Copy(float pressures[], int size, float newValue);

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
        delay(3000);
        noTone(BuzzerPIN);
        delay(5000);
        // tone(BuzzerPIN, 1000);
        // delay(2000);
        // noTone(BuzzerPIN);
        Serial.println("Sensor Initialization Was Not Perfect!");
    }
    else{
        tone(BuzzerPIN,4000); // Beep 1
        delay(100);
        noTone(BuzzerPIN);
        delay(100);
        tone(BuzzerPIN,5000); // Beep 2
        delay(100);
        noTone(BuzzerPIN);
        delay(100);
        tone(BuzzerPIN,6000); // Beep 3
        delay(100);
        noTone(BuzzerPIN);
        Serial.println("Sensor Initialization Was FUCKING Perfect!");
        delay(5000);
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
        delay(3000);
        noTone(BuzzerPIN);
        delay(1000);
        tone(BuzzerPIN, 1000);  // Long Beep 2
        delay(3000);
        noTone(BuzzerPIN);
        delay(5000);
        // tone(BuzzerPIN, 1000);  // Long Beep 3
        // delay(2000);
        // noTone(BuzzerPIN);
    }
    else{
        tone(BuzzerPIN,4000); // Beep 1
        delay(100);
        noTone(BuzzerPIN);
        delay(100);
        tone(BuzzerPIN,5000); // Beep 2
        delay(100);
        noTone(BuzzerPIN);
        delay(100);
        tone(BuzzerPIN,6000); // Beep 3
        delay(100);
        noTone(BuzzerPIN);
        tone(BuzzerPIN,7000); // Beep 4
        delay(100);
        noTone(BuzzerPIN);
        tone(BuzzerPIN,8000); // Beep 5
        delay(100);
        noTone(BuzzerPIN);
        Serial.println("Data Logging Was FUCKING Perfect!");
        delay(7000);
    }

    // Create a CSV for storing Sensor Data: "Sensors.csv"
    sdCard.writeFile("/data1.csv","Time,Latitude,Longitude,Altitude,Temperature,Pressure,AccelX,AccelY,AccelZ,GyroX,GyroY,GyroZ,MPU_Temperature\n");
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void loop(){
    static unsigned long lastPrint = 0;
    const unsigned long PRINT_INTERVAL = 500; // Print every 500 ms
    unsigned long currTime = millis();
    
    if (currTime - lastPrint >= PRINT_INTERVAL) {
        lastPrint = currTime;
        
        // Variables for GPS data
        String latStr = "0";
        String lonStr = "0";
        float gpsAltitude = 0.0;
        
        // Read and process GPS data once
        if (gpsSerial.available()) {
            String nmea = gpsSerial.readStringUntil('\n');
            if (nmea.startsWith("$GPGGA")) {
                // Parse the NMEA sentence
                String* fields = gps.parsed_data(nmea);
                latStr = gps.get_latitude(fields);
                lonStr = gps.get_longitude(fields);
                gpsAltitude = gps.get_altitude(fields);
                delete[] fields;  // Free the allocated memory
            }
        }
                
        
        accelerations = accelerometer.readSensor();
        // BMP280 and accelerometer data
        temperature = bmp.readTemperature();
        pressure = bmp.readPressure();
        bmpAltitude = bmp.readAltitude();

        
        // Using std::copy (efficient and readable)
        
        if (pressures_populated){
            if(!std_populated){
                pressureStd_new = calculateStd(Pressures, PRESSURE_BUFFER_SIZE);
                pressureStd_old = pressureStd_new;
            }
            else{
                if(currTime<60000){
                    pressureStd_new = calculateStd(Pressures, PRESSURE_BUFFER_SIZE);
                    pressureStd_old = max(pressureStd_old,pressureStd_new);
                }
                else{// Standard Deviation Calculations Done
                    std_populated = true;
                    tone(BuzzerPIN,2000);
                    delay(200);
                    tone(BuzzerPIN, 8000);
                    delay(200);
                    noTone(BuzzerPIN);
                    tone(BuzzerPIN,2000);
                    delay(200);
                    tone(BuzzerPIN, 8000);
                    delay(200);
                    noTone(BuzzerPIN);
                }
            }

            leftShiftArray_Copy(Pressures, PRESSURE_BUFFER_SIZE, pressure);
            std::copy(Pressures, Pressures + PRESSURE_WINDOW_SIZE, Pressures_window1);
            std::copy(Pressures + (PRESSURE_BUFFER_SIZE - PRESSURE_WINDOW_SIZE), Pressures + PRESSURE_BUFFER_SIZE, Pressures_window2);

            pressure_old_mean = calculateMean(Pressures_window1, PRESSURE_WINDOW_SIZE);
            pressure_new_mean = calculateMean(Pressures_window2, PRESSURE_WINDOW_SIZE);

            float acc_values[] = {accelerations.accelX, accelerations.accelY, accelerations.accelZ};
            acc_mag = calculateMag(acc_values, 3);

            if(!Launched){
                if(launchCounter>counter_threshold){
                    Launched = true;
                    Serial.println("Launched!");
                }
                else if((pressure_old_mean-pressure_new_mean)>pressureStd_old && acc_mag > acc_threshold){
                    launchCounter += 1;
                }
                else{
                    launchCounter = 0;
                }
            }

            else if(!Apogee){
                if(apogeeCounter>counter_threshold){
                    Apogee = true;
                    Serial.println("Apogee!");
                }
                else if((pressure_new_mean-pressure_old_mean)>pressureStd_old){
                    apogeeCounter += 1;
                }
                else{
                    apogeeCounter = 0;
                }
            }

            if(Apogee && !Landed){
                if(landedCounter>landing_counter_threshold){
                    Landed = true;
                    Serial.println("Landed!");
                }
                else if(abs(pressure_new_mean-pressure_old_mean)<pressureStd_old){
                    landedCounter += 1;
                    Serial.println("Absolute difference in pressure windows ");
                    Serial.println(String(abs(pressure_new_mean-pressure_old_mean)));
                }
                else{
                    landedCounter = 0;
                }
            }
        }
        else{
            Pressures[loop_counter] = pressure;
        }
        loop_counter += 1;
        if (loop_counter%30 == 0){
            loop_counter = 0;
            pressures_populated = true;
        }


        // Create CSV string using snprintf
        snprintf(csvBuffer, CSV_BUFFER_SIZE,
                 "%lu,%s,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                 millis(),
                 latStr.c_str(),
                 lonStr.c_str(),
                 bmpAltitude,
                 temperature,
                 pressure,
                 accelerations.accelX,
                 accelerations.accelY,
                 accelerations.accelZ,
                 accelerations.gyroX,
                 accelerations.gyroY,
                 accelerations.gyroZ,
                 accelerations.temperature);
        
        // Append the CSV string to the file
        sdCard.appendFile("/data1.csv", csvBuffer);
    }
}

void leftShiftArray_Copy(float pressures[], int size, float newValue) {
    std::copy(pressures + 1, pressures + size, pressures);  // This is correct, no its not "pressures + size -1"
    pressures[size - 1] = newValue;
}

float calculateMean(float arr[], int size){
    float sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum/size;
}

float calculateStd(float arr[], int size){
    int mean = calculateMean(arr, size);
    float ssq_errors;
    float temp;
    for (int i = 0; i < size; i++)
    {
        temp = (arr[i] - mean);
        ssq_errors += temp * temp;
    }
    return pow(ssq_errors/size, 0.5);
}

float calculateMag(float arr[], int size){
    float ssum = 0;
    for (int i = 0; i < size; i++)
    {
        ssum += (arr[i] * arr[i]);
    }
    return pow(ssum/size, 0.5);
}