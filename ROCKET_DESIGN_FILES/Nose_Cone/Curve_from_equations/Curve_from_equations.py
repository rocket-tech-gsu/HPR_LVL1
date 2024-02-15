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
