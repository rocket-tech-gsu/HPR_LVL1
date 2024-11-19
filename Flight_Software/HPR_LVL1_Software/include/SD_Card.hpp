/* 
//////////////////// CONTENTS: ////////////////////
-> Header File for using SD card.
-> USAGE code, for software team to refer to.
-> OLDERVERSION.

//////////////////// TODO: ////////////////////
The SDCardManager header file in this needs to be structured like:
bool Setup(), 
    -> Test its initilization with ESP32, 
    -> Test all functions one by one 
    -> At each check it also prints out readable serial monitor output(in CS it's also called verbosity)
bool writeFile(const char *path, const char *message);
String readFile(const char *path);
bool deleteFile(const char *path);
bool testCard();
bool appendFile(const char *path, const char *message);

*/


#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>

class SDCardManager {
private:
    bool cardInitialized;
    SPIClass spi;

public:
    const int chipSelect;
    // CLASS CONSTRUCTOR:
    SDCardManager(int cs_pin): 
        chipSelect(cs_pin), 
        cardInitialized(false),
        spi(HSPI)
    {}
    // FUNCTIONS:
    bool startup();
    bool writeFile(const char *path, const char *message);
    String readFile(const char *path);
    bool deleteFile(const char *path);
    bool testCard();
    bool appendFile(const char *path, const char *message);

};

// FUNCTION IMPLEMENTATIONS:
bool SDCardManager::startup() {
    Serial.println("Initializing SD card...");
    
    spi.begin(18, 19, 23, chipSelect); // SCK, MISO, MOSI, SS

    if (!SD.begin(chipSelect, spi, 4000000)) {
        Serial.println("\nSD Card initialization failed!\n");
        Serial.println("Troubleshooting Checks:");
        Serial.println("1. SD card is inserted properly");
        Serial.println("2. Wiring connections(test verified):");
        Serial.println("   - CS (SS)  -> GPIO5");
        Serial.println("   - MOSI     -> GPIO23");
        Serial.println("   - MISO     -> GPIO19");
        Serial.println("   - SCK      -> GPIO18");
        Serial.println("   - VCC      -> 3.3V (NOT 5V)");
        Serial.println("   - GND      -> GND");
        return false;
    }
    
    cardInitialized = true;
    Serial.println("SD Card initialization successful!");
    
    uint8_t cardType = SD.cardType();
    if(cardType == CARD_NONE) {
        Serial.println("No SD card attached");
        return false;
    }
    
    Serial.print("SD Card Type: ");
    switch(cardType) {
        case CARD_MMC:  Serial.println("MMC"); break;
        case CARD_SD:   Serial.println("SDSC"); break;
        case CARD_SDHC: Serial.println("SDHC"); break;
        default:        Serial.println("UNKNOWN"); break;
    }
    
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
    return true;
}
bool SDCardManager::writeFile(const char* path, const char* message) {
    if (!cardInitialized) return false;
    
    File file = SD.open(path, FILE_WRITE);
    if(!file) {
        Serial.println("Failed to open file for writing");
        return false;
    }
    
    if(file.print(message)) {
        Serial.printf("Wrote to file: %s\n", path);
        file.close();
        return true;
    } else {
        Serial.println("Write failed");
        file.close();
        return false;
    }
}
String SDCardManager::readFile(const char *path)
{
    if (!cardInitialized) return "";
    
    File file = SD.open(path);
    if(!file) {
        Serial.println("Failed to open file for reading");
        return "";
    }
    
    String content = "";
    while(file.available()) {
        content += (char)file.read();
    }
    
    file.close();
    return content;
}
bool SDCardManager::deleteFile(const char *path)
{
    if (!cardInitialized) return false;
    
    if(SD.remove(path)) {
        Serial.printf("File deleted: %s\n", path);
        return true;
    } else {
        Serial.println("Delete failed");
        return false;
    }
}
bool SDCardManager::testCard()
{
    if (!cardInitialized) return false;
    
    Serial.println("Testing SD card functionality...");
    
    // Test write
    if (!writeFile("/test.txt", "Test content\n")) {
        Serial.println("Write test failed!");
        return false;
    }
    
    // Test read
    String content = readFile("/test.txt");
    if (content != "Test content\n") {
        Serial.println("Read test failed!");
        return false;
    }
    
    // Test delete
    if (!deleteFile("/test.txt")) {
        Serial.println("Delete test failed!");
        return false;
    }
    
    Serial.println("All SD card tests passed!");
    return true;
}
bool SDCardManager::appendFile(const char *path, const char *message)
{
    if (!cardInitialized) return false;
    
    File file = SD.open(path, FILE_APPEND);
    if(!file) {
        Serial.println("Failed to open file for appending");
        return false;
    }
    
    if(file.print(message)) {
        Serial.printf("Appended to file: %s\n", path);
        file.close();
        return true;
    } else {
        Serial.println("Append failed");
        file.close();
        return false;
    }
}


//////////////////// USAGE: ////////////////////
// // Global instance with CS pin set to 5:
// SDCardManager sdCard(5);

// void setup() {
//     Serial.begin(115200);
//     delay(1000);
    
//     Serial.println("\nSD Card Test Program");
//     Serial.println("------------------");
    
//     pinMode(5, OUTPUT);
//     digitalWrite(5, HIGH);
    
//     if (!sdCard.begin()) {
//         Serial.println("Card initialization failed!");
//         while (1) delay(1000);
//     }
    
//     if (!sdCard.testCard()) {
//         Serial.println("Card functionality test failed!");
//         while (1) delay(1000);
//     }
    
//     // Example usage
//     sdCard.writeFile("/data.txt", "Hello, ESP32!\n");
//     sdCard.appendFile("/data.txt", "This is a test line\n");
    
//     String content = sdCard.readFile("/data.txt");
//     Serial.println("File content:");
//     Serial.println(content);
    
//     Serial.println("Setup complete - SD card is ready!");
// }

// void loop() {
//     delay(1000);
// }


// #include <SD.h>
// #include <SPI.h>



//////////////////// OLDERVERSION: ////////////////////

// class SD_card{
//     private:
//     public:
//         File myfile;
//         String data;
//         int cs=4;
//         void startup();
//         void Write(String Input);
//         String Read(String File_name);
// };

// void SD_card::startup(){
//   try{
//     // Initilizing the SD card:
//     if (!SD.begin(cs))
//     {
//       delay(500);
//       Serial.println("Card failed, or not present");
//     }
//     else
//     {
//         Serial.println("card initialized.");
//     }

//     // W R I T I N G   D A T A:
//     myfile = SD.open("data.csv",FILE_WRITE | O_TRUNC);
//     String val1 = "Testing";
//     String val2 = "Storing String";
//     String val3 = val1 + "," + val2;
//     if (myfile) {
//       myfile.println(val3);
//       myfile.close();
//       // print to the serial port too:
//       Serial.println("The following data has been added to your file:");
//       // Serial.println(val3);
//     }
//     else {
//       Serial.println("error opening data.csv");
//     }

//     // R E A D I N G   D A T A:
//     myfile= SD.open("data.csv", FILE_READ);
//     if(myfile){
//       while (myfile.available()) {
//       Serial.println(myfile.readString());
//       }
//     }
//     else {
//       Serial.println("Reading File Doesn't Work! \nor\nThe file you're trying to read doesn't exist");
//     }
//     }
//     catch{
//       Serial.printf("\n\nAbort Recommendation! – SD card is not working\n\n ");
//     }
// }

// void SD_card::Write(String input){
//   // W R I T I N G   D A T A:
//   myfile = SD.open("data.csv",FILE_WRITE | O_TRUNC);
//   if (myfile) {
//     myfile.println(input);
//     myfile.close();
//     Serial.println("SD Card Logging Successfully ...");
//   }
//   else {
//     Serial.println("Error opening data.csv");
//   }
// }

// String SD_card::Read(String File_name)
// {
//   // R E A D I N G   D A T A:
//   myfile= SD.open("data.csv", FILE_READ);
//   if(myfile){
//     while (myfile.available()) {
//     Serial.println(myfile.readString());
//     }
//   }
//   else {
//     Serial.println("File Might Not Exist!");
//   }
// }
