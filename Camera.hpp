#ifndef CAMERA_H
#define CAMERA_H

#include "Object.hpp"
#include "Color.hpp"

class camera {
  public:
    double aspect_ratio = 1.0;  // Ratio of image width over height
    int image_width  = 100;  // Rendered image width in pixel count
    int samples_per_pixel = 10; 
    int max_depth = 10; // limiter le nombre de rebonds pour ne pas avoir de boucle infinie ou de stack overflow

    void render(const object& world, std::ostream& out) ;

  private:
    int    image_height;   // Rendered image height
    Vect   center;         // Camera center
    Vect   pixel00_loc;    // Location of pixel 0, 0
    Vect   pixel_delta_u;  // Offset to pixel to the right
    Vect   pixel_delta_v;  // Offset to pixel below

    double pixel_sample_scale;  // Scale factor for pixel samples


    void initialize() ;

    color ray_color(const Ray& r, const object& world, int depth) const;

    Ray get_ray(int i, int j) const;

    Vect sample_square() const;
};
#endif