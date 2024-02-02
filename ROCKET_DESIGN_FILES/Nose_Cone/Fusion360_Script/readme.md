This readme file contains three sections–"Why this?", "code breakdown", and "dealing with continuous function on computers". It is simply the best resource to learn about the fusion360's API.
________________________________________________________________________________________________
# Why this?:
- Fusion360 had no support for making curves from mathematical equations
- So simple equations for example even a basic curve y=f(x) cannot be plotted as a curve.
- That's where Fusion360's API comes in:
> - The packages are made by autodesk and therefore the name of the package is abbriviated as "adsk".
> - Some of the important libraries in it are "core", "fusion", and "cam".
> - This code uses all three of the aforementioned and some python libraries("math" and "traceback").
________________________________________________________________________________________________
# Code Breakdown:
- The way the Fusion360 API works, locally in your system, is that it will automatically call a single function name "run".
- Autodesk's core package("adsk.core") has an "Application" method in it, which in turn has "get" class.
### 1. interactions with UI:
- We make an instance(object) of that get class by "adsk.core.Application.get()".
- There's an "userInterface" method in that class that allows us to interact with the fusion360's UI.
- We can store the instance of that in a variable, let's call it "ui".
- Get the 

**With it we can do things like:**
> - Display messages via "messageBox".
> - Get user's input via "inputBox".

### 2. Interacting with the fusion360 objects:
- in the instance of "adsk.core.Application.get()", there are the following attributes: ".activeProduct.rootComponent".
- **VERY IMP!**
-  You'll be able to **access sketches**, **create new sketches**, **construct planes**, ... etc. 
- Access Sketches: "root_comp.sketches"
- Construct a Sketch Plane: "xYConstructionPlane"
- Create Sketches: "root_comp.sketches.add(the_construction_plane_that_you_just_made)"
- There's another class in core module of the adsk package, it's called "ObjectCollection".
- That, in turn, has a class called "create".
> Guess what does it do, create objects.(you be like OFCOURSEEE, lol! writing documentation is kinda fun)

- Say you made an object of that class by executing "object1 = adsk.core.ObjectCollection.create()", now if you want to add a new object in the fusion360's object collection, then execute "object1.add()".

________________________________________________________________________________________________
# Discretization of a continuous math function(because binary bits can't do continuous computations):
- 
