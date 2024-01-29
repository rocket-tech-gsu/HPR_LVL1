Nose cones could be made from curves like a parabola, or a section of a circle(simple ogive, secant ogive, and tangent ogive). But if someone's too lazy then they could also just choose a straight line(Triangular Nose Cone)! But we aren't lazy and we want our rocket to perform the best! Here's something you should know:

# HAACK SERIES:
I've made an animation for the Haack Series Curve on Desmos, feel free to play with it:
https://www.desmos.com/calculator/ssogxdsf9f?embed
<img width="1476" alt="Screenshot 2024-01-29 at 5 28 16 PM" src="https://github.com/rocket-tech-gsu/HPR_LVL1/assets/110617721/65aac82e-d4ef-4e26-b128-77e5667f9758">

Haack Series Curve:
<img width="1200" alt="Screenshot 2024-01-29 at 5 24 59 PM" src="https://github.com/rocket-tech-gsu/HPR_LVL1/assets/110617721/1604868d-5f3e-4cb1-a804-9bc6f0cb2c92">
Parameters: Base radius(R), Haack's Constant(C), and the Length(L)

Some recognized values of C:
| Haack Series Type      | C Value   |
|-------------------------|-----------|
| LD-Haack (Von Kármán)   | 0         |
| LV-Haack                | 1/3       |
| Tangent                 | 2/3       |


**Von Kármán:**
If you put the constant to a zero(i.e.C = 0) then we call that geometry Von Kármán, to honor Von Kármán's contribution.
It'll look as follows(to scale):
<img width="1476" alt="Screenshot 2024-01-29 at 5 28 16 PM" src="https://github.com/rocket-tech-gsu/HPR_LVL1/assets/110617721/65aac82e-d4ef-4e26-b128-77e5667f9758">
This is an example of Von Kármán's Geometry. Here C = 0, L = 25, and R = 5cm.

**Here's a comparison of different nose cone geometries at different Mach Numbers:**
<img width="1426" src=https://upload.wikimedia.org/wikipedia/commons/8/81/Nose_cone_drag_comparison.svg >

# OUR DESIGN:
- Starting the initial rocket design process in OpenRocket we begin with the Von Kármán Geometry for the nose cone design of our rocket.
- However, by initial looks at it one can see that the highest velocity for our rocket will be 0.98, LV Haack would also perform just as well for our rocket.
- Then in the Open Rocket's optimization window we performed optimization on the shape parameter of the Haack Series the size of the nose cone.
- <img width="1451" alt="Screenshot 2024-01-29 at 5 13 51 PM" src="https://github.com/rocket-tech-gsu/HPR_LVL1/assets/110617721/a6be2a2f-0e9f-48eb-afe7-f4b265446246">

- Values before optimization: 25cm, c=0
- Values after optimization: 24.3cm, c=0.016

## INTERESTING OBSERVATION:
The optimized value of C is not Von Kármán(C=0)! 
Instead, C = 16 which is almost there in the middle of LV–Haack and Von Kármán, which is much closer to Von Kármán.
But how did the software OpenRocket come to that value? Under the hood, it must've considered the entire simulated velocity profile over time:

<img width="1512" alt="Screenshot 2024-01-29 at 5 39 02 PM" src="https://github.com/rocket-tech-gsu/HPR_LVL1/assets/110617721/033b74e3-7fd8-4239-af6b-7535cb454c02">

