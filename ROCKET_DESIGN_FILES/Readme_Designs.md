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
- Keep in mind that at high speeds:
  - fins faces enormous amounts of stresses hence the joint between fins and the fin can must be very strong.
  - if all of the fins are not symmetrical then it'll rotate very fast, which will lead to poor wireless communication and will ruin the video footage.
  - While attaching the fins to the fin can, they could be canted at very small angles like 0.1 degrees, which will again lead to same consequences.
- To rectify these error possibilities, the fin assembling must be done with a very precise assembling unit. It should be able to ensure perfect orientation of each fin and should have stand that could be put on table or something. Also, there should be firm and sturdy clamps for each fin so that throughout the curing process nothing moves.
- <img width="300" alt="image" src="https://1443543871-files.gitbook.io/~/files/v0/b/gitbook-legacy-files/o/assets%2F-LB423_rlWTQK_KuQzK5%2F-ML9q8Tc30hREyNcX-tV%2F-ML9tEgR7dJIOe54EEHi%2FFinGeometry.png?alt=media&token=a40cd3ad-5a02-4cb5-9cfc-fc14e914ae65">
- Based upon OpenRocket Simulation we got following most optimized parameters:
- <img width="1497" alt="image" src="https://github.com/rocket-tech-gsu/HPR_LVL1/assets/110617721/9bb8c6ab-aa71-44c3-9780-7abf199f4d98">
- Fusion360 Design:
- ![Fin_Can v3](https://github.com/rocket-tech-gsu/HPR_LVL1/assets/110617721/ad8f81ec-7d31-4d6d-999d-8c77b2c21cac)  
