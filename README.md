# Simple-Bezier-Curve-OpenGL
A simple Bezier Curve example made in OpenGL using glad, freetype, glfw and premake5.

This project is made to be a quick lookup reference for how Bezier Curves work, and as a tutorial for beginners on how to implement them yourself in a low level graphics API like OpenGL (I chose OpenGL because it is the simplest)

All the Bezier Curve calculations are done in main.cpp via the formula (see https://en.wikipedia.org/wiki/B%C3%A9zier_curve).

The other code is to show how to implement it and it's by no means good code because I had to keep it simple

# Example
![](https://github.com/AbdullrahmanAlzeidi/Simple-Bezier-Curve-OpenGL/blob/master/images/example.png?raw=true)


# Building The Project
The project is built using Premake5 (see https://github.com/premake/premake-core).
I only tested it on windows (tested on MSVC2017), however I don't think the libraries will work on Linux or MacOS.

So if you are using linux or MacOS you are going to have to link the libraries manually.

Steps on building in windows:

1. Open commandline window on project directory.
2. Type "premake5 vsYOUR_VISUAL_STUDIO_VERSION", so for me it was "premake5 vs2017".
3. Open the newly generated Buid directory and open Simple-Bezier-Curve-OpenGL.sln.
4. Build and run the executable in VisialStudio
