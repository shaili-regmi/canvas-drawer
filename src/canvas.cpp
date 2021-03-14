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

/*
void canvas::end()
{
	for (int i = 0; i < (vertices.size() - 1); i++)
	{
		int ax = vertices[i].x;
		int ay = vertices[i].y;
		int bx = vertices[i+1].x;
		int by = vertices[i+1].y;
		int w = bx - ax;
		int h = by - ay;
		bool increment = true; // ax <= bx or ay <= by

		if (h <= w)
		{
			if (bx <= ax || by <= ay)
			{
				increment = false;
				if (bx < ax) w = -1 * w;
				if (by < ay) h = -1 * h;
				
				int temp_bx = bx;
				bx = ax;
				ax = temp_bx;
				int temp_by = by;
				by = ay;
				ay = temp_by;
			
			}
			int f = (2 * h) - w;

			for (int x = ax; x <= bx; x++)
			{
				_canvas.set(ay, x, current_color);
				if (f > 0)
				{
					if (increment)
					{
						ay++;
					}
					else
					{
						ay--;
					}
					f += (2 * (h - w));
				}
				else
				{
					f += (2 * h);
				}
			}
		}
		else
		{
			if (bx <= ax || by <= ay)
			{
				increment = false;
				if (bx < ax) w = -1 * w;
				if (by < ay) h = -1 * h;
				
				int temp_bx = bx;
				bx = ax;
				ax = temp_bx;
				int temp_by = by;
				by = ay;
				ay = temp_by;
				
			}
			int f = (2 * w) - h;

			for (int y = ay; y <= by; y++)
			{
				_canvas.set(y, ax, current_color);
				if (f > 0)
				{
					if (increment)
					{
						ax++;
					}
					else
					{
						ax--;
					}
					f += (2 * (w - h));
				}
				else
				{
					f += (2 * w);
				}
			}
		}
	}
	vertices.clear();
}
*/
void canvas::end()
{
	for (int i = 0; i < (vertices.size() - 1); i++)
	{
		int ax = vertices[i].x;
		int ay = vertices[i].y;
		int bx = vertices[i + 1].x;
		int by = vertices[i + 1].y;
		
		int w = bx - ax;
		int h = by - ay;
		bool increment = true; // ax <= bx or ay <= by

		if (h <= w)
		{
			if (bx < ax)
			{
				int temp_bx = bx;
				bx = ax;
				ax = temp_bx;
				int temp_by = by;
				by = ay;
				ay = temp_by;
				w = bx - ax;
				//h = by - ay;
			}

			if (by < ay)
			{
				increment = false;
				//h = -1 * h;
				h = ay - by;
				//ax = ax - 1;
				//bx = bx - 1;
			}
			int f = (2 * h) - w;

			for (int x = ax; x <= bx; x++)
			{
				_canvas.set(ay, x, current_color);
				if (f > 0)
				{
					if (increment)
					{
						ay++;
					}
					else
					{
						ay--;
					}
					f += (2 * (h - w));
				}
				else
				{
					f += (2 * h);
				}
			}
		}
		else
		{
			if (by < ay)
			{
				int temp_bx = bx;
				bx = ax;
				ax = temp_bx;
				int temp_by = by;
				by = ay;
				ay = temp_by;
				//w = bx - ax;
				h = by - ay;
			}

			if (bx < ax)
			{
				increment = false;
				//w = -1 * w;
				w = ax - bx;
				//ay = ay - 1;
				//by = by - 1;
			}
			int f = (2 * w) - h;

			for (int y = ay; y <= by; y++)
			{
				_canvas.set(y, ax, current_color);
				if (f > 0)
				{
					if (increment)
					{
						ax++;
					}
					else
					{
						ax--;
					}
					f += (2 * (w - h));
				}
				else
				{
					f += (2 * w);
				}
			}
		}
	}
	vertices.clear();
}

void canvas::vertex(int x, int y)
{
	vertices.push_back({ x,y });
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

