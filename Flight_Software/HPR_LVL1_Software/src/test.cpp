// #include <Arduino.h>
// #include <SD.h>
// #include <SPI.h>

// // For ESP32, adjust these as needed
// #define SD_CS_PIN  5

// // Simple Base64 encode function (for small chunks). 
// // You can replace with a more robust library if desired.
// String base64Encode(const uint8_t* data, size_t length) {
//     // A quick, minimal base64 table:
//     static const char PROGMEM *base64_chars = 
//         "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//         "abcdefghijklmnopqrstuvwxyz"
//         "0123456789+/";
    
//     String encoded;
//     encoded.reserve(((length+2)/3)*4);  // approximate size
    
//     unsigned int val = 0;
//     int valb = -6;
//     for (size_t i = 0; i < length; i++) {
//         val = (val << 8) + data[i];
//         valb += 8;
//         while (valb >= 0) {
//             encoded += base64_chars[(val >> valb) & 0x3F];
//             valb -= 6;
//         }
//     }
//     if (valb > -6) {
//         encoded += base64_chars[((val << 8) >> (valb + 8)) & 0x3F];
//     }
//     while (encoded.length() % 4) {
//         encoded += '=';
//     }
//     return encoded;
// }

// // Recursively list all files & subfolders on the SD card
// void listAndSendFiles(File dir, String pathPrefix) {
//     while (true) {
//         File entry = dir.openNextFile();
//         if (!entry) {
//             // no more files
//             break;
//         }
//         String entryName = String(entry.name());
//         String fullPath = pathPrefix + "/" + entryName;

//         if (entry.isDirectory()) {
//             // Recurse into subdirectory
//             listAndSendFiles(entry, fullPath);
//         } else {
//             // It's a file. Send it.
//             Serial.printf("FILE_BEGIN: %s\n", fullPath.c_str());

//             // Read in chunks
//             const size_t CHUNK_SIZE = 512;
//             uint8_t buffer[CHUNK_SIZE];
            
//             while (true) {
//                 size_t bytesRead = entry.read(buffer, CHUNK_SIZE);
//                 if (bytesRead == 0) break; // done reading

//                 // Base64‐encode chunk
//                 String encoded = base64Encode(buffer, bytesRead);
//                 Serial.println(encoded);
//             }

//             Serial.printf("FILE_END: %s\n", fullPath.c_str());
//         }
//         entry.close();
//     }
// }

// void setup() {
//     Serial.begin(115200);
//     while (!Serial) { /* wait for serial */ }

//     // Initialize SD card
//     if (!SD.begin(SD_CS_PIN)) {
//         Serial.println("SD Card initialization failed!");
//         return;
//     }
//     Serial.println("SD Card initialized successfully.");

//     // Start reading from root
//     File root = SD.open("/");
//     if (!root) {
//         Serial.println("Failed to open root directory!");
//         return;
//     }
//     if (!root.isDirectory()) {
//         Serial.println("Root is not a directory!");
//         return;
//     }

//     // List & send all files
//     listAndSendFiles(root, "");
//     root.close();
// }

// void loop() {
//     // Nothing else to do. 
//     // All the sending happened in setup(). 
//     // If you want to keep re‐sending or handle requests, do that here.
// }
