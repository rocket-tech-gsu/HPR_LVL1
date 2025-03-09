// #include <Arduino.h>
// const int CAMERA_BUTTON_PIN = 27;  // Pin connected to the camera button control (through relay)
// const unsigned long MAX_RECORDING_TIME = 6000;  // 1 minute in milliseconds
// const unsigned long BUTTON_PRESS_DURATION = 500; // Duration to hold button in milliseconds

// // State variables
// bool isRecording = false;
// unsigned long recordingStartTime = 0;
// void pressButton();
// void setup()
// {
//   // Configure button pin
//   pinMode(CAMERA_BUTTON_PIN, OUTPUT);
//   digitalWrite(CAMERA_BUTTON_PIN, LOW);  // Ensure button starts released
//   // Initialize serial communication for debugging
//   Serial.begin(115200);  // ESP32 typically uses 115200 baud rate
  

  
//   // Initial delay to ensure system is stable
//   delay(1000);
//   // Going into the menu with the first button press
//   pressButton();
  
  
//   delay(1000);
//   pressButton();
//   delay(10000);
//   pressButton();
//   // Check if current recording needs to be stopped
//   if (isRecording && (millis() - recordingStartTime >= MAX_RECORDING_TIME)) { 
//     pressButton();
//     Serial.println("Setting isRecording = false");
//     delay(2000);  // Wait for 2 second before starting new recording
//     pressButton();  // Start a new recording
//     isRecording = true;
//     recordingStartTime = millis();
//     Serial.println("Setting isRecording = true");
//   }
  
//   delay(1000);
  
//   Serial.println("ESP32 camera control system initialized");
// }

// void loop() {
//   // // FIRST RECORDING EVER:
//   // // Start Recording
//   // if (isRecording == false){
//   //   pressButton();
//   //   isRecording = true;
//   //   recordingStartTime = millis();
//   //   Serial.println("Setting isRecording = true");
//   // }


//   // // LATER RECORDINGS:
//   // // Check if current recording needs to be stopped
//   // if (isRecording && (millis() - recordingStartTime >= MAX_RECORDING_TIME)) {
//   //   pressButton();
//   //   Serial.println("Setting isRecording = false");
//   //   delay(2000);  // Wait for 2 second before starting new recording
//   //   pressButton();  // Start a new recording
//   //   isRecording = true;
//   //   recordingStartTime = millis();
//   //   Serial.println("Setting isRecording = true");
//   // }
//   ;
// }

// void pressButton() {
//   digitalWrite(CAMERA_BUTTON_PIN, HIGH);  // Press button
//   delay(BUTTON_PRESS_DURATION);    // Hold button
//   digitalWrite(CAMERA_BUTTON_PIN, LOW);   // Release button
//   delay(100);  // Short delay after releasing to ensure stable state
// }