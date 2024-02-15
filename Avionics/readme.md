# Avionics:

- At the heart of each rocket is a flight computer. It is responsible for ejecting the parachute, sensing the trajectory, appogee altitude and all sorts of things.
Our goal with this flight computer will be to make a flight computer that we can use again and again in future for upcoming rockets.

- Avionics101:
  - Redundancy must be present in the avionics. If we used two, exactly same flight computers and if there will be a problem in one of them both would fail in exact same way, which is useless redundancy.
  - We want the pyro charge signals to be able to be triggered by either of the two flight computers.
  - Voltage regulator must be a really good in terms of noise in the voltage output. Source voltage often introduce noise in the systems, and systems that are very sensitive for the input voltage like a sensistive gyroscope.
    - Also, there must be something to block the 5V coming from the power input inside the mciroUSB connector in case it's also connceted to external 5V. Otherwise it'll become 10V in total. A **DIODE** can do that.
    - <img width="543" alt="image" src="https://github.com/rocket-tech-gsu/HPR_LVL1/assets/110617721/57ef1d58-e476-4d0f-9bf7-48a2c86836a5">
  - As per schematics of the microcontroller there must be capacitors that can help in case of the voltage dips.


# Avionics Components:
- Microcontroller
- Resonator
- Sensors:
  - Accelerometer
  - Gyroscope
  - 
- Capacitors
- Resistors
- Transmitter
- Reciever
- Shot key diode
- 
