#include <Arduino.h>
#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif


struct sensorval{

    float aX;

    float aY;

    float aZ;

    float aSqrt;

    float gX;

    float gY;

    float gZ;

    float mDirection;

    float mX;

    float mY;

    float mZ;

    float bmeTemp;

    float bmePressure;

    float bmeAltitide;


}


Adafruit_BMP280 bme; // I2C
MPU9250_asukiaaa mySensor;

class mpu9250{
    public: 
        struct sensorval values;
        bool setup();
        sensonval getvalues();

}


bool mpu9250::setup() {
    if(Wire.begin() && bme.begin() && mySensor.beginAccel() && mySensor.beginGyro() &&  mySensor.beginMag())
    {
        return true;
        // Serial.begin(115200);
        // while (!Serial);
        //mySensor.setWire(&Wire);
        //mySensor.setWire(&Wire);
        // mySensor.beginAccel();
        // mySensor.beginGyro();
        // mySensor.beginMag();
    } else{
        return false;
    }

        // You can set your own offset for mag values
        // mySensor.magXOffset = -50;
        // mySensor.magYOffset = -55;
        // mySensor.magZOffset = -10;
}

sensorval mpu9250::getvalues() {
    try{ 
        values.aX = mySensor.accelX();
        values.aY = mySensor.accelY();
        values.aZ = mySensor.accelZ();
        values.gX = mySensor.gyroX();
        values.gY = mySensor.gyroY();
        values.gZ = mySensor.gyroZ();
        values.mX = mySensor.magX();
        values.mY = mySensor.magY();
        values.mZ = mySensor.magZ();
        values.aSqrt = mySensor.accelSqrt();
        values.mDirection = mySensor.magHorizDirection();
        values.bmeTemp = bme.readTemperature();
        values.bmePressure = bme.readPressure()/3377;
        values.bmeAltitude = bme.readAltitude(1013.25);
        //check what does the values(3377, 1013.25) do

        return values;
    } 
    
    catch(...){
        return NULL;
    }
}




