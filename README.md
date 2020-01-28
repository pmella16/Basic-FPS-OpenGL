# Description
This is a program implemented for practical part of the course Computer Graphics at Technische Hochschule Ulm

It consists of a 3D model created using Blender 2.8, imported to a C++ program and rendered using OpenGL 4+. It's a simulation of a
3D first person shooter with some basic shading and a minimap included.

This is a fork from prof. @Alfred-Franz that contained the red triangle program (the hello world of computer graphics, so I heard) that I used as a template for creating an OpenGL project.

# Goal
The practical part of the course consisted in creating 3 showcases:

* 2D showcase containing some 2D transformations (minimap)
* Shaders showcase (Light from the moon and flashlight)
* 3D showcase containing 3D transformations to move the camera around the map.

The resulting program is a combination of the three

## Building
### Requirements
* Microsoft Visual Studio (2019 used in this case) with C++ compiler
* CMake 3+

Using CMake, select this repo's folder as source and a folder for binaries, configure, generate and open the project.

Once in MSV, find the project "FPSGame" and build. 

Execute the .exe in /FPSGame/
