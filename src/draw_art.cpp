#include <iostream>
#include "canvas.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
	int w = 400;
	int h = 400;
	canvas drawer(w, h);

	//flower
	drawer.background(120, 90, 100);
	drawer.rose_curve(200, 200, 220, 15, 100, 200, 180.0f, 10.0f);
	drawer.rose_curve(200, 200, 215, 100, 215, 200, 150.0f, 5.0f);
	drawer.rose_curve(200, 200, 180, 120, 150, 200, 100.0f, 20.0f);
	drawer.unfilled_circle(200, 200, 190, 20, 70, 150, 200);
	drawer.filled_circle(200, 200, 25, 160, 20, 85, 200);
	drawer.save("../flower.png");

	/*
	// filled and unfilled circles with random colors
	int r = 0;
	int g = 255;
	int b = 0;
	int center_x = w / 2;
	int center_y = h / 2;
	for (int radius = (w / 2); radius >= 0; radius -= 20)
	{
		drawer.filled_circle(center_x, center_y, radius, r, g, b, 100);
		r = rand() % (255 + 1);
		g = rand() % (255 + 1);
		b = rand() % (255 + 1);
		drawer.unfilled_circle(center_x, center_y, (radius - 10), r, g, b, 100);
		r = rand() % (255 + 1);
		g = rand() % (255 + 1);
		b = rand() % (255 + 1);
	}
	drawer.save("filled_and_unfilled_circles-2.png");
	/*
	// background
	drawer.begin(TRIANGLES);
	drawer.background(0, 0, 90);
	drawer.color(50, 50, 150);
	drawer.vertex(0, 0);
	drawer.color(0, 0, 90);
	drawer.vertex(w, 0);
	drawer.color(120, 110, 200);
	drawer.vertex(w, h);

	drawer.color(50, 50, 150);
	drawer.vertex(0, 0);
	drawer.color(0, 0, 90);
	drawer.vertex(0, h);
	drawer.color(120, 110, 200);
	drawer.vertex(w, h);
	drawer.end();
	//drawer.save("gradient-bckgrnd.png");

   //Rose Curve stars
   for (int i = 0; i < w; i += 50)
   {
	   for (int j = 0; j < h; j += 50)
	   {
		   drawer.rose_curve(i, j, 200, 100, 100, 20, 10.0f, 5.0f);
	   }
   }
   //drawer.save("rose_curve_stars.png");

   
   //Point Stars
   drawer.begin(POINTS);
   drawer.color(255, 255, 255);
   for (int i = 0; i < w; i+=40)
   {
	   for (int j = 0; j < h; j+=40)
	   {
			drawer.vertex(i, j);
			drawer.vertex(i - 1, j - 1);
			drawer.vertex(i - 1, j + 1);
			drawer.vertex(i + 1, j - 1);
			drawer.vertex(i + 1, j + 1);
			drawer.vertex(i - 2, j - 2);
			drawer.vertex(i - 2, j + 2);
			drawer.vertex(i + 2, j - 2);
			drawer.vertex(i + 2, j + 2);
	   }
	   
   }
   drawer.end();
   drawer.save("rose_curve_and_point_stars.png");
   */
   return 0;
}

