# Author - Varun Ahlawat
# Setup Instructions: 
# Go to Add-Ins in fusion360, click on create button, then click edit button, copy and paste the following code in it:
''' 
Description - 
Nose Cone geometry can make or break the performance of any fast-moving craft through air. It is the part that faces almost all the aerodynamic drag.
It can create shock waves that interact with the rest of the craft in very interesting ways.
This allows the user to make an optimized nose cone for the rockets if you know the Haack Constant for it.

The Haack's constant depends on your flow regime, i.e. how fast is your rocket going to fly, and the diameter of the rest of your rocket.
During the optimization, i.e. finding the best value of Haack's constant for your craft, there must be some boundary conditions! is bounded by factors like mass, which must be bounded 

The following Python script is written as per the fusion360 documentation, it takes in the following arguments: 
- the height of the nose cone 
- the Haack constant for the Hack series
Then it creates a spline as a sketch that fits the curve geometry. Then an offset curve is added to the sketch
which is then closed to make an area enclosing a curve. The enclosed area is then finally revolved around the axis.'''

import adsk.core, adsk.fusion, traceback, math

def create_cartesian_spline(sketch, xmin, xmax, num_of_points):
    points = []
    
    x = xmin
    for i in range(num_of_points + 1):
        y = f(x)
        points.append(adsk.core.Point3D.create(x, y, 0))
        x += (xmax - xmin)/(num_of_points)
        
    # Create an ObjectCollection and add points to it.
    point_collection = adsk.core.ObjectCollection.create()
    for pt in points:
        point_collection.add(pt)

    # Add the fitted spline to the sketch.
    return sketch.sketchCurves.sketchFittedSplines.add(point_collection)

def f(x):
    R = 4
    L = 20
    C = 0
    theta = math.acos(1 - ((2 * x) / L))
    coefficient = (R / math.sqrt(math.pi))
    y = (coefficient * math.sqrt(theta - (math.sin(2 * theta)) / (2) + C * (math.sin(theta))**3))
    return y

def run(context):
    try:
        app = adsk.core.Application.get()
        ui = app.userInterface

        # Get the active design.
        design = app.activeProduct

        # Create a new sketch in the XY plane.
        sketches = design.rootComponent.sketches
        sketch = sketches.add(design.rootComponent.xYConstructionPlane)

        # Range of x values.
        xmin = 0
        xmax = 20

        # Number of points to generate.
        num_of_points = 100

        # Create the Cartesian spline.
        create_cartesian_spline(sketch, xmin, xmax, num_of_points)

    except:
        if ui:
            ui.messageBox('Failed:\n{}'.format(traceback.format_exc()))

def stop(context): 
    pass # so that when you press stop in fusion360, the script can stop execution

# Run the script.
run(None)
