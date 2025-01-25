#include "Camera.hpp"
#include "Material.hpp"

void camera::initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_sample_scale = 1.0 / samples_per_pixel;

        center = Vect();

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = Vect(viewport_width, 0, 0);
        auto viewport_v = Vect(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - Vect(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

void camera::render(const object& world, std::ostream& out) {
    initialize();

    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) { 
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int sample = 0; sample < samples_per_pixel; sample++){
                Ray r = get_ray(i,j);
                pixel_color += ray_color(r, world, max_depth);
            }

            write_color(out, pixel_sample_scale * pixel_color);
        }
    }
}

color camera::ray_color(const Ray& r, const object& world, int depth) const {
    if (depth <= 0){
     //   std::cout << "max reached" << std::endl;
        return color();
    }    

    RayIntersection inters = RayIntersection(world, r);
    double t = inters.getHit();
    if ((t > 0.0) && (inters.mat != nullptr)) {
 //       return Vect(1, 0, 0); 
 //       return Vect(1, 0, 1) * (1.0 / (1.0 + 0.1 * t)); 
//       return 0.5 * (inters.getNormal() + color(1));
    //    Vect direction = random_on_hemisphere(inters.getNormal());
 //       Vect direction = inters.getNormal() + random_unit_vector();
 //       return 0.1 * ray_color(Ray(inters.getPoint(), direction), world, depth-1);
        Ray scattered;
        color attenuation;
        if (inters.mat->scatter(r, inters, attenuation, scattered)){
            auto rec = ray_color(scattered, world, depth-1);
            auto res = color(attenuation.getX()*rec.getX(), attenuation.getY()*rec.getY(), attenuation.getZ()*rec.getZ());
            return res;
        }
        return color();
    }

    Vect unit_direction = r.getDirection().Unit();
    t = 0.5 * (unit_direction.getY() + 1.0);
    return (1.0-t) * Vect(1.0, 1.0, 1.0) + t * Vect(0.5, 0.7, 1.0);
}

Ray camera::get_ray(int i, int j) const {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                          + ((i + offset.getX()) * pixel_delta_u)
                          + ((j + offset.getY()) * pixel_delta_v);

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return Ray(ray_origin, ray_direction);
    }

Vect camera::sample_square() const {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return Vect(random_double() - 0.5, random_double() - 0.5, 0);
}