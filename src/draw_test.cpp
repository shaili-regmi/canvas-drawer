#include <iostream>
#include "canvas.h"

using namespace agl;
using namespace std;

void test_line(canvas& drawer, int ax, int ay, int bx, int by, const std::string& savename)
{
   drawer.background(0, 0, 0);
   drawer.begin(LINES);
   drawer.vertex(ax, ay);
   drawer.vertex(bx, by);
   drawer.end();
   drawer.save(savename);
}

int main(int argc, char** argv)
{
	int w = 400;
	int h = 400;
	canvas drawer(w, h);

	drawer.background(100, 40, 10);
	drawer.rose_curve(200, 200, 240, 130, 230, 200, 200.0f, 10.0f);
	drawer.save("../rose_curve-2.png");

	/*
	drawer.background(0, 0, 0);
	drawer.unfilled_polygon();
	drawer.color(255, 0, 255);
	drawer.vertex(10, 10);
	drawer.color(0, 255, 255);
	drawer.vertex(150, 150);
	drawer.color(255, 255, 0);
	drawer.vertex(280, 150);
	drawer.color(255, 0, 255);
	drawer.vertex(150, 150);
	drawer.color(0, 255, 255);
	drawer.vertex(280, 150);
	drawer.color(255, 255, 0);
	drawer.vertex(280, 280);
	drawer.color(0, 255, 255);
	drawer.vertex(280, 280);
	drawer.color(255, 255, 0);
	drawer.vertex(10, 280);
	drawer.color(255, 0, 255);
	drawer.vertex(10, 280);
	drawer.color(0, 255, 255);
	drawer.vertex(10, 10);
	drawer.end();
	drawer.save("../unfilled-polygon.png");
	*/

	//drawer.background(100, 200, 200);
	//drawer.unfilled_circle(150, 150, 140, 0, 0, 0, 150);
	//drawer.save("../unfilled_circle.png");

	//drawer.background(100, 200, 200);
	//drawer.filled_circle(150, 150, 140, 200, 150, 115, 150);
	//drawer.save("../filled_circle.png");

	//drawer.background(0, 0, 0);
	//drawer.rose_curve(32, 19, 255, 0, 0, 20, 10.0f, 5.0f);
	//drawer.save("rose_curve.png");
	//drawer.background(0, 0, 0);
	//drawer.filled_random_curve(32, 19, 10, 255, 0, 0, 20);
	//drawer.save("filled_curve.png");
	
	//canvas drawer(100, 100);
	/*
	drawer.background(0, 0, 0);

	drawer.begin(LINES);

	drawer.color(255, 0, 0);
	drawer.vertex(0, 0);
	drawer.vertex(100, 0);

	drawer.color(0, 255, 0);
	drawer.vertex(0, 0);
	drawer.vertex(0, 100);

	drawer.end();
	drawer.save("red-green-line.png");
	
	drawer.color(255, 255, 255);
	test_line(drawer, 0, 50, 100, 50, "horizontal-line.png");
	test_line(drawer, 50, 0, 50, 100, "vertical-line.png");
	test_line(drawer, 0, 0, 100, 100, "diagonal-line-1.png"); // slope = 1
	test_line(drawer, 25, 10, 75, 25,  "h-lessthan-w-line-1.png"); // slope H < W
	test_line(drawer, 25, 25, 75, 75,  "w-lessthan-h-line-1.png"); // slope W < H
	test_line(drawer, 0, 100, 100, 0, "diagonal-line-2.png"); // slope H < W
	test_line(drawer, 25, 90, 75, 75,  "h-lessthan-w-line-2.png"); // slope H < W
	test_line(drawer, 25, 90, 75, 25,  "w-lessthan-h-line-2.png"); // slope W < H
	
	// test line interpolation
	drawer.background(0, 0, 0);
	drawer.begin(LINES);
	drawer.color(255, 0, 255);
	drawer.vertex(0, 0);
	drawer.color(0, 255, 255);
	drawer.vertex(100, 100);
	drawer.end();
	drawer.save("line-color-interpolation.png");
	
	// test triangle with interpolation
	drawer.background(0, 0, 0);
	drawer.begin(TRIANGLES);
	drawer.color(255, 0, 255);
	drawer.vertex(10, 0);
	//drawer.vertex(1, 0);
	drawer.color(0, 255, 255);
	drawer.vertex(90, 50);
	//drawer.vertex(9, 5);
	drawer.color(255, 255, 0);
	drawer.vertex(10, 90);
	//drawer.vertex(1, 9);
	drawer.end();
	drawer.save("triangle.png");
	
	// test triangle with interpolation
	drawer.background(0, 0, 0);
	drawer.begin(TRIANGLES);
	drawer.color(255, 0, 255);
	drawer.vertex(10, 10);
	drawer.color(0, 255, 255);
	drawer.vertex(10, 90);
	drawer.color(255, 255, 0);
	drawer.vertex(90, 90);
	
	drawer.color(255, 0, 255);
	drawer.vertex(90, 90);
	drawer.color(0, 255, 255);
	drawer.vertex(90, 10);
	drawer.color(255, 255, 0);
	drawer.vertex(10, 10);
	drawer.end();
	drawer.save("quad.png");
	
	/*
	canvas drawer(10, 10);
	drawer.background(0, 0, 0);
	drawer.begin(POINTS);
	drawer.color(255, 0, 255);
	drawer.vertex(1, 0);
	drawer.color(0, 255, 255);
	drawer.vertex(9, 5);
	drawer.color(255, 255, 0);
	drawer.vertex(1, 9);
	drawer.end();
	drawer.save("points.png");
	*/
	return 0;
}
