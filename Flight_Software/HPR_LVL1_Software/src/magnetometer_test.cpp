// #include <Arduino.h>
// #include <Wire.h>
// #include "GY271.hpp"  // Ensure this header is in your include path

// // Create a global instance of the magnetometer
// GY271Sensor magnetometer;

// void setup() {
//   Serial.begin(115200);
//   // Initialize the I2C bus once on GPIO21 (SDA) and GPIO22 (SCL)
//   Wire.begin(21, 22);
//   Wire.setClock(100000);
//   delay(1000); // Allow time for Serial Monitor to open

//   Serial.println("Initializing GY-271 Magnetometer...");
//   if (!magnetometer.startup()) {
//     Serial.println("Magnetometer initialization failed. Check wiring!");
//     while (1); // Halt execution if the sensor isn't detected
//   }
//   Serial.println("Magnetometer initialized successfully.");

//     MagnetometerData data = magnetometer.readSensor();
  
//   // Print out the sensor data
//   Serial.print("X: ");
//   Serial.print(data.x);
//   Serial.print(" uT, Y: ");
//   Serial.print(data.y);
//   Serial.print(" uT, Z: ");
//   Serial.print(data.z);
//   Serial.print(" uT, Heading: ");
//   Serial.print(data.heading);
//   Serial.println("°");
  
//   delay(2000); 


//    MagnetometerData data1 = magnetometer.readSensor();
  
//   // Print out the sensor data
//   Serial.print("X: ");
//   Serial.print(data1.x);
//   Serial.print(" uT, Y: ");
//   Serial.print(data1.y);
//   Serial.print(" uT, Z: ");
//   Serial.print(data1.z);
//   Serial.print(" uT, Heading: ");
//   Serial.print(data1.heading);
//   Serial.println("°");
  
// }

// void loop() {

    

//   // Read magnetometer sensor data
// // Delay between readings
// }
