# canvas-drawer

Implements a simple drawing api

TODO: Add a representative image for your project here

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
canvas-drawer $ mkdir build
canvas-drawer $ cd build
canvas-drawer/build $ cmake -G "Visual Studio 16 2019" ..
canvas-drawer/build $ start Draw-2D.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
canvas-drawer/build $ ../bin/Debug/draw_test
canvas-drawer/build $ ../bin/Debug/draw_art
```

*macOS*

Open terminal to the directory containing this repository.

```
canvas-drawer $ mkdir build
canvas-drawer $ cd build
canvas-drawer/build $ cmake ..
canvas-drawer/build $ make
```

To run each program from build, you would type

```
canvas-drawer/build $ ../bin/draw_test
canvas-drawer/build $ ../bin/draw_art
```

## Supported primitives

TODO: Document the custom primitives supported by your canvas class

Draw points at the given vertices using begin(POINTS);
void draw_point();


Draw an unfilled circle with the given center (x,y), radius, color, and smoothness (how many lines the circle is divided into)

void unfilled_circle(int x, int y, int radius, unsigned char r, unsigned char g, unsigned char b, int smoothness);


Draw a filled circle with the given center (x,y), radius, color, and smoothness (how many triangles the circle is divided into)

void filled_circle(int x, int y, int radius, unsigned char r, unsigned char g, unsigned char b, int smoothness);


Draw unfilled concave or convex polygons with the vertices that follow. Need to call end() after the vertices.

void unfilled_polygon();


Draw unfilled rose curves with the given center (x,y), color, smoothness, amplitude, and angular frequency

void rose_curve(int x, int y, unsigned char r, unsigned char g, unsigned char b, int smoothness, float amplitude, float angular_freq);

## Results

TODO: Show artworks using your class
