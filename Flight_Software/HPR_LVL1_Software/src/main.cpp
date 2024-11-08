// Header Files:
#include <Arduino.h>
#include <../lib/GPS_Module.h>
#include <../lib/BMP_Module.h>
#include <../lib/MPU6050_Module.h>
#include <../lib/SD_Card_Module.h>


//Objects Declarations(from the classes present in the header files):


// Function Declarations:
int myFunction(int, int);

// Variable Declarations:


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(LED_BUILTIN, OUTPUT);
  int result = myFunction(2, 3);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}