#ifndef canvas_H_
#define canvas_H_

#include <string>
#include <vector>
#include "ppm_image.h"

using namespace std;

namespace agl
{
    struct vertex_struct
    {
        int x;
        int y;
        ppm_pixel color;
    };

    struct bounding_box 
    {
        // The coordinates of the bounding box for the triangle
        int min_x;
        int min_y;
        int max_x;
        int max_y;
    };

   enum PrimitiveType {UNDEFINED, LINES, TRIANGLES, POINTS};
   class canvas
   {
   public:
      canvas(int w, int h);
      virtual ~canvas();

      // Save to file
      void save(const std::string& filename);

      // Draw primitives with a given type (either LINES or TRIANGLES)
      // For example, the following draws a red line followed by a green line
      // begin(LINES);
      //    color(255,0,0);
      //    vertex(0,0);
      //    vertex(100,0);
      //    color(0,255,0);
      //    vertex(0, 0);
      //    vertex(0,100);
      // end();
      void begin(PrimitiveType type);
      void end();

      // Draw a line between two vertices using Bresenham's algorithm
      // Linear color interpolation if two vertices of the same line have different colors
      void draw_line();

      // Drawing the two different cases for Bresenham's algorithm
      void h_less_than_w(int ax, int ay, int bx, int by, int w, int h, ppm_pixel color, ppm_pixel next_color);
      void w_less_than_h(int ax, int ay, int bx, int by, int w, int h, ppm_pixel color, ppm_pixel next_color);

      // Draw a triangle between three vertices using barycentric coordinates
      // Color interpolation using Gouraud shading if vertices have different colors
      void draw_triangle();

      // Find the bounding box for the triangle to be drawn
      bounding_box find_boundary(vertex_struct a, vertex_struct b, vertex_struct c);

      // Find f(p) for a point p on a line between vertices m and n using the implicit line equation
      float f_line_eqn(vertex_struct m, vertex_struct n, vertex_struct p);

      // Draw points at the given vertices
      void draw_point();

      // Draw an unfilled circle with the given center (x,y), radius, color, and smoothness (how many lines the circle is divided into)
      void unfilled_circle(int x, int y, int radius, unsigned char r, unsigned char g, unsigned char b, int smoothness);

      // Draw a filled circle with the given center (x,y), radius, color, and smoothness (how many triangles the circle is divided into)
      void filled_circle(int x, int y, int radius, unsigned char r, unsigned char g, unsigned char b, int smoothness);

      // Helper function for unfilled and filled circle functions where type is the type of circle (filled or unfilled)
      void circle(int x, int y, int radius, string type, int smoothness);

      // Draw unfilled concave or convex polygons with the vertices that follow. Need to call end() after the vertices.
      void unfilled_polygon();

      // Draw unfilled rose curves with the given center (x,y), color, smoothness, amplitude, and angular frequency
      void rose_curve(int x, int y, unsigned char r, unsigned char g, unsigned char b, int smoothness, float amplitude, float angular_freq);

      // Specifiy a vertex at raster position (x,y)
      // x corresponds to the column; y to the row
      void vertex(int x, int y);

      // Specify a color. Color components are in range [0,255]
      void color(unsigned char r, unsigned char g, unsigned char b);

      // Fill the canvas with the given background color
      void background(unsigned char r, unsigned char g, unsigned char b);

   private:
      ppm_image _canvas;
      ppm_pixel current_color;
      PrimitiveType current_shape;
      vector<vertex_struct> vertices;
   };
}

#endif


