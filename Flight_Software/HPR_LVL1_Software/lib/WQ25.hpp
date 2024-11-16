// #include <Arduino.h>
// #include <SPI.h>
// #include <SPIMemory.h>

// class WQ25{
//     private:
//     public:
//         // Define the pin for Chip Select (CS)
//         const uint8_t chipSelectPin = 5;
//         bool startup();
//         SPIFlash flash(chipSelectPin);
// };

// bool WQ25::startup(){

//     try{

//         // Initialize the SPI flash memory
//         if (flash.begin()) {
//             Serial.println("Flash memory initialized successfully.");
//         } else {
//             Serial.println("Flash memory initialization failed!");
//             while (1);
//         }

//         // Test writing and reading data
//         String = "Hello, Flash Memory!";
//         size_t dataSize = strlen(testData) + 1;

//         // Erase a sector before writing
//         if (flash.eraseSector(0)) {
//             Serial.println("Sector erased successfully.");
//         } else {
//             Serial.println("Sector erase failed!");
//         }

//         // Write data to flash memory
//         if (flash.writeByteArray(0, (uint8_t *)testData, dataSize)) {
//             Serial.println("Data written successfully.");
//         } else {
//             Serial.println("Data write failed!");
//         }

//         // Read data from flash memory
//         String readData;
//         if (flash.readByteArray(0, (uint8_t *)readData, dataSize)) {
//             Serial.print("Data read from flash: ");
//             Serial.println(readData);
//         } else {
//             Serial.println("Data read failed!");
//         }
    
//     }
//     catch{

//     }

// }



#ifndef WQ25_H
#define WQ25_H

#include <Arduino.h>
// #include <SPI.h>
#include <SPIMemory.h>

class WQ25 {
private:
    const uint8_t chipSelectPin;
    SPIFlash flash;
    
public:
    // Constructor
    WQ25(uint8_t cs = 5) : chipSelectPin(cs), flash(cs) {}
    
    // Initialize the flash memory
    bool startup();
    
    // Utility functions
    bool writeString(uint32_t addr, const String& data);
    String readString(uint32_t addr, size_t length);
    bool eraseSector(uint32_t addr);
};

// Implementation
bool WQ25::startup() {
    if (!flash.begin()) {
        Serial.println(F("Flash memory initialization failed!"));
        return false;
    }
    
    Serial.println(F("Flash memory initialized successfully."));
    return true;
}

bool WQ25::writeString(uint32_t addr, const String& data) {
    if (!flash.eraseSector(addr)) {
        Serial.println(F("Sector erase failed!"));
        return false;
    }
    
    // Convert String to char array
    char charArray[data.length() + 1];
    data.toCharArray(charArray, data.length() + 1);
    
    if (!flash.writeByteArray(addr, (uint8_t*)charArray, data.length() + 1)) {
        Serial.println(F("Data write failed!"));
        return false;
    }
    
    Serial.println(F("Data written successfully."));
    return true;
}

String WQ25::readString(uint32_t addr, size_t length) {
    char buffer[length + 1];
    
    if (!flash.readByteArray(addr, (uint8_t*)buffer, length + 1)) {
        Serial.println(F("Data read failed!"));
        return String("");
    }
    
    buffer[length] = '\0';  // Ensure null termination
    return String(buffer);
}

bool WQ25::eraseSector(uint32_t addr) {
    if (!flash.eraseSector(addr)) {
        Serial.println(F("Sector erase failed!"));
        return false;
    }
    
    Serial.println(F("Sector erased successfully."));
    return true;
}

#endif // WQ25_H