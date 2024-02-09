# Let's talk about the designs
Things to be taken care of in the design:

NOSE CONE DESIGN:
- Haack Series fusion360 API, Python Script

PROPULSION SYSTEM DESIGN: 
- Grains go inside a liner(usually made of Phenolic ablative material)
- But that can't hold the pressure of a burning motor
- So there's a metal case to reinforce the liner, to allow it to hold the immense pressure
- The nozzle is a part of liner but is screwed into the aluminium case using threads.
- Slide the liner and motor grains assembled together inside the case using lube:

- From both ends a strong seal is required for gases to not let escape. We call the closures, closures lol.
- This is the forward closure: closes from the front.
- O ring is gonna pop out if just on its own
- Threads will not be able to seal the gases on its own.
- So we have a retention ring(to thread the closure in place) along with O ring in the closure.

- So is the bottom closure, a closure with O ring and a retention ring with threads. But on that retention ring the entire airframe rests.

AVIONICS BAY DESIGN:
- Place GPS and radio communication antennas physically apart so that they can't interfere(spoiler alert they interfere a hell lot!).
- No mechanical stresses should pass through the PCB Board.
- Should be very sturdy, no vibrations should affect any connections, or any sensor



FIN CAN DESIGN:
- <img width="1497" alt="image" src="https://1443543871-files.gitbook.io/~/files/v0/b/gitbook-legacy-files/o/assets%2F-LB423_rlWTQK_KuQzK5%2F-ML9q8Tc30hREyNcX-tV%2F-ML9tEgR7dJIOe54EEHi%2FFinGeometry.png?alt=media&token=a40cd3ad-5a02-4cb5-9cfc-fc14e914ae65">
- Based upon OpenRocket Simulation we got following most optimized parameters:
- <img width="1497" alt="image" src="https://github.com/rocket-tech-gsu/HPR_LVL1/assets/110617721/9bb8c6ab-aa71-44c3-9780-7abf199f4d98">
