# HPR_LVL1 | High Powered Rocket Level-1
### (as per NAR --> Rocket motors from Classes):
![image](https://github.com/yup-VARUN/L1Rocket/assets/110617721/90c8edc8-8cfb-430f-9047-7eff27ad1070)
FAA governs the US air space For guidelines refer to: https://www.faa.gov/air_traffic/publications/atpubs/pham_html/chap31_section_1.html#:~:text=Class%202%20%2D%20a%20high%20power,pound%2Dseconds)%20or%20less.


## Gameplan:
Step 1: Shortlist all of the sensors, actuators, microcontrollers, and other hardware components that would be the perfect fit for the given problem statement.<br>
Step 2: Come up with a schematic.<br>
Step 3: Write the program for each individual component.<br>
Step 4: Test all those individual parts of codes with the microcontroller on the breadboard or in the Proteus Software.<br>
Step 5: Integrate all those components together.<br>
Step 6: Perform tests.<br>
Step 7: Design a nice board, and route all the copper traces onto a PCB of the right size and shape.<br>
Step 8: Get the PCB manufactured, or manufacture it yourself.<br>
Step 9: Solder everything together.<br>

## Avionics Goals to be accomplished:
- Sensor Calibration,
- Test and initiate the telemetry and share the data through telemetry,
- Final Health checkup & report over telemetry("say ready for launch if everything is responding as it should"),
- Ignition Sequence: <br>
  -> Check if the rocket is upright.<br>
  -> Start logging the raw data from all sensors in the Flash memory chip.<br>
  -> Buzzer n Light flash for Launch Alert. <br>
  -> Update the IMU reference. <br>
  -> Start the Camera Recording. <br>
  -> Listen for the final confirmation signal over the Telemetry. <br>
  -> Set the ignition charges to "HIGH" for 4 seconds.
- Determine the Altitude of the rocket in real time using: <br>
  -> IMU(accelerometer + gyroscope) Data | Medium Low Pass Filter<br> 
  -> Pressure Sensor Data | Aggressive Low Pass Filter<br>
  -> GPS Z axis Data | Medium Low Pass Filter<br>
  -> Convert all of the cleaned signals into Height<br>
  -> Convert all of those heights into a single height using the Kalman Filter Algorithm for fusing multiple different sensors.
- Detect the apogee with the variation in height,
- Eject the parachute,
- Data logging(save the sensor locally on the flight computer),
- Location sensing,
- Landing detection,
- Stop the Camera Recording after 5 seconds,
- Send the location through the LoRa module,
- Write all of the data from flash chips to SD Card,
- Activate the buzzer after some delay.

## Optional Functions:
- Reaction Wheel for stabilization along the Roll Axis(Along the rocket's body, pointing along the nose cone)
- Fin Control/Thrust Vector Control

## Components Specifications:

__Rocket Motor:__
- Class I Rocket Motor

__Sensors:__
- Pressure Sensor: BMP280 | For altitude
- Accelerometer & Gyroscope: MPU6050 | For Navigation (inertial measurement unit)
- GPS Module: NEO-6M | For location sensing
- Magnetometer: GY-273 | For orientation sensing
- Camera Module: Raspberry Pi Camera Module 3 - 12MP 120 Degree | For capturing the video footage

__Signal Receiver & Transmitters:__
- nRF24
- LoRa Module

__Algorithms:__
- Kalman Filter for sensor fusion
- Low Pass filter

__Pyro Channels:__
- MOSFETs
- 900mAh LiPo Battery by Apogee (Model:09204)

__Microcontroller:__
- Atmega328P

__Memory:__
- Flash memory chip: FLASH - NOR Memory IC 256Mbit SPI - Quad I/O 133 MHz 16-SOIC | Storing the data reliably(soldered connections), quickly(133 MHz)
- SD card, for easier data recovery & redundancy.
