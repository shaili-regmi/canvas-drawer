#include "canvas.h"
#include <cassert>

using namespace std;
using namespace agl;

canvas::canvas(int w, int h)
{
	_canvas = ppm_image(w, h);
}

canvas::~canvas()
{
}

void canvas::save(const std::string& filename)
{
   _canvas.save(filename);
}

void canvas::begin(PrimitiveType type)
{
	current_shape = type;
}

void canvas::end()
{
	for (int i = 0; i < (vertices.size() - 1); i++)
	{
		ppm_pixel color = vertices[i].color;
		ppm_pixel next_color = vertices[i + 1].color;
		bool color_interpolation = false;
		if (color.r != next_color.r || color.g != next_color.g || color.b != next_color.b)
		{
			color_interpolation = true;
		}
		int ax = vertices[i].x;
		int ay = vertices[i].y;
		int bx = vertices[i + 1].x;
		int by = vertices[i + 1].y;

		int w = bx - ax;
		int h = by - ay;

		if (abs(h) <= abs(w))
		{
			if (bx < ax)
			{
				h_less_than_w(bx, by, ax, ay, w, h, color, next_color, color_interpolation);
			}
			else
			{
				h_less_than_w(ax, ay, bx, by, w, h, color, next_color, color_interpolation);
			}
		}
		else
		{
			if (by < ay)
			{
				w_less_than_h(bx, by, ax, ay, w, h, color, next_color, color_interpolation);
			}
			else
			{
				w_less_than_h(ax, ay, bx, by, w, h, color, next_color, color_interpolation);
			}
		}
	}
	vertices.clear();
}

void canvas::h_less_than_w(int ax, int ay, int bx, int by, int w, int h, ppm_pixel color, ppm_pixel next_color, bool color_interpolation)
{
	bool increment = true; // ax <= bx or ay <= by
	if (by < ay) increment = false;
	if (bx < ax) increment = false;
	if (h < 0) h = -1 * h;
	if (w < 0) w = -1 * w;
	int f = (2 * h) - w;

	int total_pixels = bx - ax;
	ppm_pixel orig_color = color;
	float t = 0; // t for linear color interpolation

	for (int x = ax; x <= bx; x++)
	{
		if (color_interpolation)
		{
			t = (float)x / (float)total_pixels;
			int new_r = floor(orig_color.r * (1 - t) + next_color.r * t);
			int new_g = floor(orig_color.g * (1 - t) + next_color.g * t);
			int new_b = floor(orig_color.b * (1 - t) + next_color.b * t);
			color = { (unsigned char)new_r, (unsigned char)new_g, (unsigned char)new_b };
		}
		_canvas.set(ay, x, color);
		if (f > 0)
		{
			if (increment) ay++;
			else ay--;

			f += (2 * (h - w));
		}
		else
		{
			f += (2 * abs(h));
		}
	}
}

void canvas::w_less_than_h(int ax, int ay, int bx, int by, int w, int h, ppm_pixel color, ppm_pixel next_color, bool color_interpolation)
{
	bool increment = true; // ax <= bx or ay <= by
	if (by < ay) increment = false;
	if (bx < ax) increment = false;
	if (h < 0) h = -1 * h;
	if (w < 0) w = -1 * w;
	int f = (2 * w) - h;

	int total_pixels = by - ay;
	ppm_pixel orig_color = color;
	float t = 0; // t for linear color interpolation

	for (int y = ay; y <= by; y++)
	{
		if (color_interpolation)
		{
			t = (float)y / (float)total_pixels;
			int new_r = floor(orig_color.r * (1 - t) + next_color.r * t);
			int new_g = floor(orig_color.g * (1 - t) + next_color.g * t);
			int new_b = floor(orig_color.b * (1 - t) + next_color.b * t);
			color = { (unsigned char)new_r, (unsigned char)new_g, (unsigned char)new_b };
		}
		_canvas.set(y, ax, color);
		if (f > 0)
		{
			if (increment) ax++;
			else ax--;
	
			f += (2 * (w - h));
		}
		else
		{
			f += (2 * w);
		}
	}
}

void canvas::vertex(int x, int y)
{
	if (x >= _canvas.width())
	{
		x = _canvas.width() - 1;
	}
	if (y >= _canvas.height())
	{
		y = _canvas.height() - 1;
	}
	vertices.push_back({ x,y, current_color });
}

void canvas::color(unsigned char r, unsigned char g, unsigned char b)
{
	current_color = { r,g,b };
}

void canvas::background(unsigned char r, unsigned char g, unsigned char b)
{
	for (int i = 0; i < _canvas.height(); i++)
	{
		for (int j = 0; j < _canvas.width(); j++)
		{
			_canvas.set(i, j, { r,g,b });
		}
	}
}

