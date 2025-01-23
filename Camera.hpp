#ifndef CAMERA_H
#define CAMERA_H
#include "RayTracer.hpp"
#include "Object.hpp"

class camera {
  public:
    double aspect_ratio = 1.0;  // Ratio of image width over height
    int    image_width  = 100;  // Rendered image width in pixel count

    void render(const object& world) ;

  private:
    int    image_height;   // Rendered image height
    Vect   center;         // Camera center
    Vect   pixel00_loc;    // Location of pixel 0, 0
    Vect   pixel_delta_u;  // Offset to pixel to the right
    Vect   pixel_delta_v;  // Offset to pixel below


    void initialize() ;

    color ray_color(const Ray& r, const object& world) const;
};
#endif