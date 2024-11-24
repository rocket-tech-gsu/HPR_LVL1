#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

struct SensorData {
    float accelX, accelY, accelZ;    // in m/s^2
    float gyroX, gyroY, gyroZ;       // in rad/s
    float temperature;                // in °C
};

class MPU6050Sensor {
private:
    Adafruit_MPU6050 mpu;
    sensors_event_t a, g, temp;
    
public:

    bool startup() {
        Wire.begin(21, 22);  // SDA, SCL

        // Try to initialize!
        if (!mpu.begin()) {
            Serial.println("Failed to find MPU6050 chip");
            return false;
        }

        // Set up the accelerometer and gyroscope ranges
        mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
        mpu.setGyroRange(MPU6050_RANGE_500_DEG);
        mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

        Serial.println("MPU6050 Found!");
        return true;
    }

    SensorData readSensor() {
        mpu.getEvent(&a, &g, &temp);
        
        SensorData data;
        // Accelerometer data
        data.accelX = a.acceleration.x;
        data.accelY = a.acceleration.y;
        data.accelZ = a.acceleration.z;
        
        // Gyroscope data
        data.gyroX = g.gyro.x;
        data.gyroY = g.gyro.y;
        data.gyroZ = g.gyro.z;
        
        // Temperature data
        data.temperature = temp.temperature;
        
        return data;
    }

    void printReadings() {
        SensorData data = readSensor();
        
        Serial.println("------------------------");
        Serial.println("Accelerometer readings:");
        Serial.print("X: "); Serial.print(data.accelX); Serial.print(" m/s^2, ");
        Serial.print("Y: "); Serial.print(data.accelY); Serial.print(" m/s^2, ");
        Serial.print("Z: "); Serial.print(data.accelZ); Serial.println(" m/s^2");

        Serial.println("Gyroscope readings:");
        Serial.print("X: "); Serial.print(data.gyroX); Serial.print(" rad/s, ");
        Serial.print("Y: "); Serial.print(data.gyroY); Serial.print(" rad/s, ");
        Serial.print("Z: "); Serial.print(data.gyroZ); Serial.println(" rad/s");

        Serial.print("Temperature: ");
        Serial.print(data.temperature);
        Serial.println(" °C");
        Serial.println("------------------------");
    }
};


//////////////////// USAGE: ////////////////////
// MPU6050Sensor mpuSensor;

// void setup() {
//     Serial.begin(115200);
//     while (!Serial) delay(10);  // Wait for Serial Monitor

//     if (!mpuSensor.begin()) {
//         while (1) {
//             Serial.println("MPU6050 connection failed");
//             delay(10000);
//         }
//     }
// }

// void loop() {
//     mpuSensor.printReadings();
//     delay(1000);  // Delay between readings
// }