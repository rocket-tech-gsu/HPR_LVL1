#include <../lib/WQ25.h>

WQ25 flash;  // Uses default CS pin 5
// or
WQ25 flash(10);  // Uses CS pin 10

void setup() {
    Serial.begin(115200);
    
    if (!flash.startup()) {
        Serial.println(F("Flash initialization failed!"));
        while(1);
    }
    
    // Write a string
    String testData = "Hello, Flash Memory!";
    if (flash.writeString(0, testData)) {
        // Read it back
        String readBack = flash.readString(0, testData.length());
        Serial.println(readBack);
    }
}