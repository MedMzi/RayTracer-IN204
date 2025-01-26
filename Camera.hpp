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
    double vfov = 90;  // Vertical view angle (field of view) in degrees

    //orientation de la camera
    Vect lookfrom = Vect(0,0,0);  //point de vue de la camera
    Vect lookat = Vect(0,0,-1);   //point ou la camera est orienté
    Vect vup = Vect(0,1,0);       //vecteur vertical de la camera

    //depth of field
    double defocus_angle = 0.0; //angle de defocalisation
    double focus_dist = 10.0; //distance de focalisation

    void render(const object& world, std::ostream& out) ;

  private:
    int    image_height;   // Rendered image height
    Vect   center;         // Camera center
    Vect   pixel00_loc;    // Location of pixel 0, 0
    Vect   pixel_delta_u;  // Offset to pixel to the right
    Vect   pixel_delta_v;  // Offset to pixel below
    
    Vect u,v,w; //vecteur de la camera 

    Vect defocus_disk_u;
    Vect defocus_disk_v;

    double pixel_sample_scale;  // Scale factor for pixel samples


    void initialize() ;

    color ray_color(const Ray& r, const object& world, int depth) const;

    Ray get_ray(int i, int j) const;

    Vect sample_square() const;

    Vect defocus_disk_sample() const;
};
#endif