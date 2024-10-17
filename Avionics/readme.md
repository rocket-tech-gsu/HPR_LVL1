# AVNIONICS:
This document contains
- Components List, &
- Avionics Pre-Integration Testing Protocol

for information about all three: Engine Test Avionics, Flight Avionics, and Ground Control Avionics.

# Components List:

### __<u>Engine Test Avionics Components:</u>__
- Load Cell Sensor(HX711 amplifier and 2024020278 Load Cell)

### __<u>Flight Avionics Components:</u>__
- Microcontroller(s):
    - ESP32 Wroom DevKit Board

- Memory Modules:
    - SD card(5V ready Micro-SD Breakout Board, from adafruit)
    - Flash Memory Chip : WQ25 Module

- Sensor Modules:
    - GPS Sensor(GT-U7 161212989 from Goouu Tech)
    - Accelerometer and Gyroscope Sensor Module(MPU6050 Module)
    - Pressure Sensor(BMP280)
    - Magnetometer Module(???)

- Camera Module:
    - HawkEye4k Camera Module

- Battery:
    - 2(in parallel) Li-Ion Cells.
    - 1 Li-Po Battery.
    
- Communication Module \*(*if time permits*):
    - Radio Frequency Module(E22 900T30D Version 2 from *EBYTE*)

### __<u>Ground Control Avionics Components:</u>__
- Microcontroller:
    - ESP32 Wroom DevKit Board

- Communication Module \*(*if time permits*):
    - Radio Frequency Module(E22 900T30D Version 2 from *EBYTE*)

- Ignition Circuit:
    - N Channel MOSFET
    - Li-Polymer Battery

# Avionics Pre-Integration Tests:
Most Chances of not getting a certification comes from the fact that