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
}

void canvas::vertex(int x, int y)
{
	total_vertices++;
	for (int i = 0; i < total_vertices; i++)
	_canvas.set(y, x, current_color);
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

