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
	_canvas.clear();
}

void canvas::save(const std::string& filename)
{
   _canvas.save(filename);
}

void canvas::begin(PrimitiveType type)
{
}

void canvas::end()
{
}

void canvas::vertex(int x, int y)
{
}

void canvas::color(unsigned char r, unsigned char g, unsigned char b)
{
}

void canvas::background(unsigned char r, unsigned char g, unsigned char b)
{
}

