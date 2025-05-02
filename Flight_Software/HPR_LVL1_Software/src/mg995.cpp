#include <Servo.h>

Servo myServo;

int currAngle = 90; //center position

void startupTest() {
myServo.write(90); // Move to center
delay(1000);
Serial.println("Servo ready at center position.");
}

// Check angle (+45°, center, -45°)
void checkAngleTest() {

myServo.write(135); // +45°
currAngle = 135;
delay(1000);

myServo.write(90); // center
currAngle = 90;
delay(1000);

myServo.write(45); // -45°
currAngle = 45;
delay(1000);
Serial.println("Angle test complete.");
}

void moveAngle(int desired_angle) {
    desired_angle = constrain(desired_angle, 0, 180); // limits angle values between 0 and 180
    myServo.write(desired_angle);
    currAngle = desired_angle;
    Serial.print("Moved to angle: " + String(desired_angle));

    }

void correctAngle(int prevAngle) {
    if (currAngle != prevAngle) {
        Serial.println("Correcting from " + String(currAngle) + " to " + String(prevAngle));
        myServo.write(prevAngle);
        currAngle = prevAngle;
    }
    else {
        Serial.println("No correction needed.");
    }
}

void setup(){
    Serial.begin(9600);
    myServo.attach(9); // Use pin 9
    startupTest();

}

void loop() {
    checkAngleTest();
    delay(2000);

}