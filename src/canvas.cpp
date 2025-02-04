#include "canvas.h"
#include <cassert>
#include <algorithm>
constexpr auto PI = 3.14159265358979323846;

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
	if (current_shape == LINES) draw_line();
	if (current_shape == TRIANGLES) draw_triangle();
	if (current_shape == POINTS) draw_point();
}

void canvas::draw_line()
{
	for (int i = 0; i < (vertices.size() - 1); i+=2)
	{
		ppm_pixel color = vertices[i].color;
		ppm_pixel next_color = vertices[i + 1].color;
		
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
				h_less_than_w(bx, by, ax, ay, w, h, color, next_color);
			}
			else
			{
				h_less_than_w(ax, ay, bx, by, w, h, color, next_color);
			}
		}
		else
		{
			if (by < ay)
			{
				w_less_than_h(bx, by, ax, ay, w, h, color, next_color);
			}
			else
			{
				w_less_than_h(ax, ay, bx, by, w, h, color, next_color);
			}
		}
	}
	vertices.clear();
}

void canvas::h_less_than_w(int ax, int ay, int bx, int by, int w, int h, ppm_pixel color, ppm_pixel next_color)
{
	bool increment = true; // ax <= bx or ay <= by
	if (by < ay) increment = false;
	if (bx < ax) increment = false;
	if (h < 0) h = -1 * h;
	if (w < 0) w = -1 * w;
	int f = (2 * h) - w;

	int total_pixels = bx - ax;
	ppm_pixel fill_color;
	float t = 0; // alpha for linear color interpolation

	for (int x = ax; x <= bx; x++)
	{
		t = (float)(x-ax) / (float)total_pixels;
		int new_r = floor(color.r * (1 - t) + next_color.r * t);
		int new_g = floor(color.g * (1 - t) + next_color.g * t);
		int new_b = floor(color.b * (1 - t) + next_color.b * t);
		fill_color = { (unsigned char)new_r, (unsigned char)new_g, (unsigned char)new_b };
		
		_canvas.set(ay, x, fill_color);

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

void canvas::w_less_than_h(int ax, int ay, int bx, int by, int w, int h, ppm_pixel color, ppm_pixel next_color)
{
	bool increment = true; // ax <= bx or ay <= by
	if (by < ay) increment = false;
	if (bx < ax) increment = false;
	if (h < 0) h = -1 * h;
	if (w < 0) w = -1 * w;
	int f = (2 * w) - h;

	int total_pixels = by - ay;
	ppm_pixel fill_color;
	float t = 0; // t for linear color interpolation

	for (int y = ay; y <= by; y++)
	{
		t = (float)(y-ay) / (float)total_pixels;
		int new_r = floor(color.r * (1 - t) + next_color.r * t);
		int new_g = floor(color.g * (1 - t) + next_color.g * t);
		int new_b = floor(color.b * (1 - t) + next_color.b * t);
		fill_color = { (unsigned char)new_r, (unsigned char)new_g, (unsigned char)new_b };
		
		_canvas.set(y, ax, fill_color);

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

void canvas::draw_triangle()
{
	for (int i = 0; i < (vertices.size() - 2); i+=3)
	{
		vertex_struct a = vertices[i];
		vertex_struct b = vertices[i+1];
		vertex_struct c = vertices[i+2];
		ppm_pixel color_a = a.color;
		ppm_pixel color_b = b.color;
		ppm_pixel color_c = c.color;
		ppm_pixel fill_color;
		int red;
		int green;
		int blue;

		bounding_box boundaries = find_boundary(a, b, c);

		float f_alpha = f_line_eqn(b, c, a);
		float f_beta = f_line_eqn(a, c, b);
		float f_gamma = f_line_eqn(a, b, c);

		for (int i = boundaries.min_y; i <= boundaries.max_y; i++)
		{
			for (int j = boundaries.min_x; j <= boundaries.max_x; j++)
			{
				vertex_struct p = { j, i, _canvas.get(i, j) };

				float f_bc_p = f_line_eqn(b, c, p);
				float f_ac_p = f_line_eqn(a, c, p);
				float f_ab_p = f_line_eqn(a, b, p);

				float alpha = f_bc_p / f_alpha;
				float beta = f_ac_p / f_beta;
				float gamma = f_ab_p / f_gamma;

				red = floor((alpha * color_a.r) + (beta * color_b.r) + (gamma * color_c.r));
				green = floor((alpha * color_a.g) + (beta * color_b.g) + (gamma * color_c.g));
				blue = floor((alpha * color_a.b) + (beta * color_b.b) + (gamma * color_c.b));
				fill_color = { (unsigned char)red, (unsigned char)green, (unsigned char)blue };

				if ((alpha >= 0) && (beta >= 0) && (gamma >= 0))
				{
					// Note that this algorithm doesn't draw the top and left edges
					// Testing for shared edges using point (-1.2, -1.1)
					float f_bc_minus_one = ((c.y - b.y) * (-1.2f - b.x)) - ((c.x - b.x) * (-1.1f - b.y));
					float f_ac_minus_one = ((c.y - a.y) * (-1.2f - a.x)) - ((c.x - a.x) * (-1.1f - a.y));
					float f_ab_minus_one = ((b.y - a.y) * (-1.2f - a.x)) - ((b.x - a.x) * (-1.1f - a.y));

					bool draw_alpha = (alpha > 0) || ((f_alpha * f_bc_minus_one) > 0);
					bool draw_beta = (beta > 0) || ((f_beta * f_ac_minus_one) > 0);
					bool draw_gamma = (gamma > 0) || ((f_gamma * f_ab_minus_one) > 0);

					if (draw_alpha && draw_beta && draw_gamma)
					{
						_canvas.set(i, j, fill_color);
					}

				}
			}
		}

	}
	vertices.clear();
}

bounding_box canvas::find_boundary(vertex_struct a, vertex_struct b, vertex_struct c)
{
	bounding_box boundaries;
	int ax = a.x;
	int ay = a.y;
	int bx = b.x;
	int by = b.y;
	int cx = c.x;
	int cy = c.y;

	int minx = min({ ax, bx, cx });
	int miny = min({ ay, by, cy });
	int maxx = max({ ax, bx, cx });
	int maxy = max({ ay, by, cy });

	boundaries = { minx, miny, maxx, maxy };
	return boundaries;
}

float canvas::f_line_eqn(vertex_struct m, vertex_struct n, vertex_struct p)
{
	int mx = m.x;
	int my = m.y;
	int nx = n.x;
	int ny = n.y;
	int px = p.x;
	int py = p.y;

	float f_m_n_of_p = ((ny - my) * (px - mx)) - ((nx - mx) * (py - my));
	return f_m_n_of_p;
}

void canvas::draw_point()
{
	for (int i = 0; i < (vertices.size()); i++)
	{
		int ax = vertices[i].x;
		int ay = vertices[i].y;

		_canvas.set(ay, ax, vertices[i].color);
	}
	vertices.clear();
}

void canvas::unfilled_circle(int x, int y, int radius, unsigned char r, unsigned char g, unsigned char b, int smoothness)
{
	begin(LINES);
	color(r, g, b);
	circle(x, y, radius, "unfilled", smoothness);
	end();
}

void canvas::filled_circle(int x, int y, int radius, unsigned char r, unsigned char g, unsigned char b, int smoothness)
{
	begin(TRIANGLES);
	color(r, g, b);
	circle(x, y, radius, "filled", smoothness);
	end();
}

void canvas::circle(int x, int y, int radius, string type, int num_slices)
{
	float delta_theta = (2 * PI) / (float)num_slices;
	float theta_one;
	float theta_two;
	int point_one_x;
	int point_one_y;
	int point_two_x;
	int point_two_y;

	for (int i = 0; i < num_slices; i++)
	{
		theta_one = i * delta_theta;
		theta_two = (i + 1) * delta_theta;
		point_one_x = x + floor(radius * cos(theta_one));
		point_one_y = y + floor(radius * sin(theta_one));
		point_two_x = x + floor(radius * cos(theta_two));
		point_two_y = y + floor(radius * sin(theta_two));

		if (type.compare("filled") == 0) vertex(x, y);
		vertex(point_one_x, point_one_y);
		vertex(point_two_x, point_two_y);
	}
}

void canvas::unfilled_polygon()
{
	begin(LINES);
}

void canvas::rose_curve(int x, int y, unsigned char r, unsigned char g, unsigned char b, int smoothness, float amplitude, float angular_freq)
{
	begin(LINES);
	color(r, g, b);

	float delta_theta = (2 * PI) / (float)smoothness;
	float theta_one;
	float theta_two;
	int point_one_x;
	int point_one_y;
	int point_two_x;
	int point_two_y;

	float radius_one;
	float radius_two;


	for (int i = 0; i < smoothness; i++)
	{
		theta_one = i * delta_theta;
		theta_two = (i + 1) * delta_theta;
		radius_one = amplitude * cos(angular_freq * theta_one);
		radius_two = amplitude * cos(angular_freq * theta_two);
		point_one_x = x + floor(radius_one * cos(theta_one));
		point_one_y = y + floor(radius_one * sin(theta_one));
		point_two_x = x + floor(radius_two * cos(theta_two));
		point_two_y = y + floor(radius_two * sin(theta_two));

		vertex(point_one_x, point_one_y);
		vertex(point_two_x, point_two_y);
	}
	end();
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
	if (x < 0) x = 0;
	if (y < 0) y = 0;
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

