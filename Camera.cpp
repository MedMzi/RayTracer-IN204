#include "Camera.hpp"
void camera::initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

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

void camera::render(const object& world) {
    initialize();

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {

            Ray r = Ray(center, pixel00_loc + i*pixel_delta_u + j*pixel_delta_v - center);
            auto pixel_color = ray_color(r, world);

            write_color(std::cout, pixel_color);
        }
    }
}

color camera::ray_color(const Ray& r, const object& world) const {
    double t = world.hit(r);
    if (t > 0.0) {
        return Vect(1, 0, 0);
    }

    Vect unit_direction = r.getDirection().Unit();
    t = 0.5 * (unit_direction.getY() + 1.0);
    return (1.0-t) * Vect(1.0, 1.0, 1.0) + t * Vect(0.5, 0.7, 1.0);
}