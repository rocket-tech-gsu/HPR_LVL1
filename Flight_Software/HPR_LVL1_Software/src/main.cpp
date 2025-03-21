// #include <Arduino.h>
// #include <../include/gps.hpp>
// #include <../include/BMP.hpp>
// #include <../include/SD_Card.hpp>
// #include <../include/MPU6050.hpp>

// // Pin definitions
// #define GPS_RX_PIN 16
// #define GPS_TX_PIN 17
// #define CSV_BUFFER_SIZE 160

// // Global objects
// HardwareSerial gpsSerial(1);
// GPS gps(gpsSerial);
// BMP280Sensor bmp;
// MPU6050Sensor accelerometer;
// SDCardManager sdCard(4);


// // Sensor Data Variables:
// static bool Sensor_tests = true;
// static const int BuzzerPIN = 12;
// static float pressure;
// static float bmpAltitude;
// static float temperature;
// static unsigned long startTime = 0;
// static SensorData accelerations;

// static char csvBuffer[CSV_BUFFER_SIZE];

// String* parsed;
// String latitude;
// String longitude;
// float gpsAltitude;

// // Function Declarations
// void pressButton();

// void setup() {
//     Serial.begin(115200);
//     delay(1000);  // Give serial monitor time to start
    
//     // Test GPS setup
//     Serial.println("\n--- Testing GPS Setup ---");
//     if (gps.startup(GPS_RX_PIN, GPS_TX_PIN)) {
//         Serial.println("GPS initialized successfully");
//     } else {
//         Serial.println("GPS initialization failed");
//         Sensor_tests = false;
//     }
    
//     // Test BMP280 setup
//     Serial.println("\n--- Testing BMP280 Setup ---");
//     if (bmp.startup()) {
//         Serial.println("BMP280 initialized successfully");
//     } else {
//         Serial.println("BMP280 initialization failed");
//         Sensor_tests = false;
//     }
    
//     // Test GY-61 setup
//     Serial.println("\n--- Testing GY-61 Setup ---");
//     if (accelerometer.startup()) {
//         Serial.println("GY-61 initialized successfully");
//     } else {
//         Serial.println("GY-61 initialization failed");
//         Sensor_tests = false;
//     }
    
//     ////////// All Sensors Successfull: //////////
//     if (Sensor_tests == false){ // two beeps
//         tone(BuzzerPIN,1000);
//         delay(3000);
//         noTone(BuzzerPIN);
//         delay(5000);
//         // tone(BuzzerPIN, 1000);
//         // delay(2000);
//         // noTone(BuzzerPIN);
//         Serial.println("Sensor Initialization Was Not Perfect!");
//     }
//     else{
//         tone(BuzzerPIN,4000); // Beep 1
//         delay(100);
//         noTone(BuzzerPIN);
//         delay(100);
//         tone(BuzzerPIN,5000); // Beep 2
//         delay(100);
//         noTone(BuzzerPIN);
//         delay(100);
//         tone(BuzzerPIN,6000); // Beep 3
//         delay(100);
//         noTone(BuzzerPIN);
//         Serial.println("Sensor Initialization Was FUCKING Perfect!");
//         delay(5000);
//     }
    
    
//     // Test SD Card setup
//     Serial.println("\n--- Testing SD Card Setup ---");
//     sdCard.startup();
    
//     // Write Test:
//     sdCard.writeFile("/data.txt", "Hello, ESP32!\n");
//     Serial.println("\t Write Function Works");
    
    
//     // Append Test:
//     sdCard.appendFile("/data.txt", "This is an APPENDED test line\n");
//     Serial.println("\t Append Function Works");
    
//     // Read Test:
//     String content = sdCard.readFile("/data.txt");
//     if (content == "Hello, ESP32!\n"){
//         Serial.println("");
//     }
//     Serial.println("File content:");
//     Serial.println(content);
    
    
//     ////////// Data Logging Successfull: //////////
//     if (Sensor_tests == false){ // two beeps
//         tone(BuzzerPIN,1000);   // Long Beep 1
//         delay(3000);
//         noTone(BuzzerPIN);
//         delay(1000);
//         tone(BuzzerPIN, 1000);  // Long Beep 2
//         delay(3000);
//         noTone(BuzzerPIN);
//         delay(5000);
//         // tone(BuzzerPIN, 1000);  // Long Beep 3
//         // delay(2000);
//         // noTone(BuzzerPIN);
//     }
//     else{
//         tone(BuzzerPIN,4000); // Beep 1
//         delay(100);
//         noTone(BuzzerPIN);
//         delay(100);
//         tone(BuzzerPIN,5000); // Beep 2
//         delay(100);
//         noTone(BuzzerPIN);
//         delay(100);
//         tone(BuzzerPIN,6000); // Beep 3
//         delay(100);
//         noTone(BuzzerPIN);
//         tone(BuzzerPIN,7000); // Beep 4
//         delay(100);
//         noTone(BuzzerPIN);
//         tone(BuzzerPIN,8000); // Beep 5
//         delay(100);
//         noTone(BuzzerPIN);
//         Serial.println("Data Logging Was FUCKING Perfect!");
//         delay(7000);
//     }

//     // Create a CSV for storing Sensor Data: "Sensors.csv"
//     sdCard.writeFile("/data1.csv","Time,Latitude,Longitude,Altitude,Temperature,Pressure,AccelX,AccelY,AccelZ,GyroX,GyroY,GyroZ,MPU_Temperature\n");
// }

// ////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////

// void loop(){
//     static unsigned long lastPrint = 0;
//     const unsigned long PRINT_INTERVAL = 500; // Print every 500 ms
//     unsigned long currTime = millis();
    
//     if (currTime - lastPrint >= PRINT_INTERVAL) {
//         lastPrint = currTime;
        
//         // Variables for GPS data
//         String latStr = "0";
//         String lonStr = "0";
//         float gpsAltitude = 0.0;
        
//         // Read and process GPS data once
//         if (gpsSerial.available()) {
//             String nmea = gpsSerial.readStringUntil('\n');
//             if (nmea.startsWith("$GPGGA")) {
//                 // Parse the NMEA sentence
//                 String* fields = gps.parsed_data(nmea);
//                 latStr = gps.get_latitude(fields);
//                 lonStr = gps.get_longitude(fields);
//                 gpsAltitude = gps.get_altitude(fields);
//                 delete[] fields;  // Free the allocated memory
//             }
//         }
        
//         // BMP280 and accelerometer data
//         temperature = bmp.readTemperature();
//         pressure = bmp.readPressure();
//         bmpAltitude = bmp.readAltitude();
//         accelerations = accelerometer.readSensor();

//         // Create CSV string using snprintf
//         snprintf(csvBuffer, CSV_BUFFER_SIZE,
//                  "%lu,%s,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
//                  millis(),
//                  latStr.c_str(),
//                  lonStr.c_str(),
//                  bmpAltitude,
//                  temperature,
//                  pressure,
//                  accelerations.accelX,
//                  accelerations.accelY,
//                  accelerations.accelZ,
//                  accelerations.gyroX,
//                  accelerations.gyroY,
//                  accelerations.gyroZ,
//                  accelerations.temperature);
        
//         // Append the CSV string to the file
//         sdCard.appendFile("/data1.csv", csvBuffer);
//     }
// }