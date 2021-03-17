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

   enum PrimitiveType {UNDEFINED, LINES, TRIANGLES};
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

      // Drawing the two different cases for Bresenham's algorithm
      void h_less_than_w(int ax, int ay, int bx, int by, int w, int h, ppm_pixel color, ppm_pixel next_color, bool color_interpolation);
      void w_less_than_h(int ax, int ay, int bx, int by, int w, int h, ppm_pixel color, ppm_pixel next_color, bool color_interpolation);

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


