# Planetary System

The purpose of this project consists of generating an app that allows to set up a a planetary system with given masses, radius, and initial positions. The first version of this project will consist only of the calculation of the results, with no visual representation. On a second version, a 2D visualization will be included. The third version shall include 3D, and later improvement will allow moving spatially through the simulation.

## Units used

* **Mass**: kilograms
* **Distances**: meters
* **Time**: seconds

## System config file

STILL TO BE INTEGRATED

Config files contain the metadata for a system. This files has the following format:

```
{
    "bodies":[
        {
            "name": "XXXXXXXX",
            "initial_position": [X, X, X],
            "initial_velocity": [X, X, X],
            "mass": X,
            "radius": X,
            "color":{
                "r": X,
                "g": X,
                "b": X,
                "a": X
            }
        },
        ...
}
```