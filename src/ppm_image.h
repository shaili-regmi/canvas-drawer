#ifndef image_H_
#define image_H_

#include <iostream>
#include <string>

namespace agl
{
  struct ppm_pixel
  {
     unsigned char r;
     unsigned char g;
     unsigned char b;
  };

  class ppm_image
  {
  public:
     ppm_image(); // default constructor
     ppm_image(int width, int height); // constructor
     ppm_image(const ppm_image& orig); // copy constructor
     ppm_image& operator=(const ppm_image& orig); // assignment operator

     virtual ~ppm_image(); // destructor

     // load the given filename
     // returns true if the load is successful; false otherwise
     bool load(const std::string& filename);

     // save the given filename
     // returns true if the save is successful; false otherwise
     bool save(const std::string& filename) const;

     // Returns a copy of this image resized to the given width and height
     ppm_image resize(int width, int height) const;

     // Return a copy of this image flipped around the horizontal midline
     ppm_image flip_horizontal() const;

     // Return a sub-image having the given top,left coordinate and (width, height)
     ppm_image subimage(int x, int y, int w, int h) const;

     // Replace the portion starting at (row, col) with the given image
     // Clamps the image if it doesn't fit on this image
     void replace(const ppm_image& image, int x, int y);

     // Return a copy of this image with the given gamma correction applied to it
     ppm_image gammaCorrect(float gamma) const;

     // Apply the following calculation to the pixels in 
     // our image and the given image:
     //    this.pixels = this.pixels * (1-alpha) + other.pixel * alpha
     // Can assume that the two images are the same size
     ppm_image alpha_blend(const ppm_image& other, float amount) const;

     // Return a copy of this image converted to grayscale
     ppm_image grayscale() const;

     // Return a copy of this image with the colors rotated.
     // The red channel becomes the green channel, the green becomes blue, and the blue becomes red.
     ppm_image swirl_colors() const;

     // Returns a horixontally tiled copy of the image with the same size and the given number of tiles.
     // Clamps the ends if needed
     ppm_image horizontal_tiles(int number) const;

     // Return a copy of this image with the colors inverted
     ppm_image invert_color() const;

     // Return a copy of this image with all non-white portions placed over given background picture
     // Assumes that the two images are the same size
     ppm_image replace_nonwhite(ppm_image background) const;

     // Return a copy of this image with all of the pixels with the given color_old replaced by the given color_new
     ppm_image change_color(ppm_pixel color_old, ppm_pixel color_new) const;
     
     // Returns a copy of this image stitched to another given image in the row-direction (height)
     ppm_image combine_rows(ppm_image image) const;

     // Get the pixel at index (row, col)
     ppm_pixel get(int row, int col) const;

     // Set the pixel at index (row, col)
     void set(int row, int col, const ppm_pixel& c);

     // return the width of this image
     int width() const;

     // return the height of the image
     int height() const;

     // delete the 2D array used to store the image to free memory
     void clear();

  private:
      int columns; // number of columns/width
      int rows; // number of rows/height
      ppm_pixel** image_array = NULL; // pointer for the 2D array that stores the image
  };
}

#endif
