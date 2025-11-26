# Simple Raytracer

<img width="800" height="450" alt="primitives" src="https://github.com/user-attachments/assets/47f2714c-de0d-493f-a24b-7af45abee619" />
<img width="800" height="450" alt="chair" src="https://github.com/user-attachments/assets/78323991-3e92-44fc-9d01-06f6e86f187d" />
<img width="800" height="450" alt="chair_zoomed" src="https://github.com/user-attachments/assets/f14e962f-c146-43fa-94e2-d2ab34eefa6d" />

## Description
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

## References
- [Ray Tracing in One Weekend Book](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- [Improved Model for Shaded Display paper](https://www.cs.drexel.edu/~deb39/Classes/Papers/p343-whitted.pd)
