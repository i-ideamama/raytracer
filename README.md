# Simple Raytracer

This project implements a simple ray tracer that can render basic geometric primitives and materials, using a positionable camera, antialiasing, and accurate surface normals. It supports diffuse, metallic, and dielectric shading, along with depth of field and other core features needed for producing clean, decently realistic images.

## Getting Started
Follow the steps below to configure and execute the project.
### Dependencies

**None**, the project runs fully on standard C++ with no external dependencies.

### Installing

* Download the source code.

### Project Configuration

* Setup CMake
```
cmake -S . -B build
``` 

### Executing program

* Build the program.
```
cmake --build build
```
* Run the program.
```
build/raytracer  > output/image.ppm
```
