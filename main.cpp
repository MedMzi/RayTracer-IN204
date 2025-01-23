#include "RayTracer.hpp"
#include "Color.hpp"
#include <fstream>
double hit_sphere(const Vect& center, double radius, const Ray& r) {
    Vect oc = center - r.getOrigin();
    auto a = r.getDirection() * r.getDirection();
    auto b = -2.0 * (r.getDirection() * oc);
    auto c = (oc* oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - std::sqrt(discriminant) ) / (2.0*a);
    }
}
color Ray_color(const Ray& r) {

	auto t = hit_sphere(Vect(0,0,-1), 0.5, r);
    if (t > 0.0) {
        Vect N = (r.position(t) - Vect(0,0,-1)).Unit();
        return 0.5*color(N.getX()+1, N.getY()+1, N.getZ()+1);
    }
    Vect unit_direction = (r.getDirection()).Unit();
    auto a = 0.5*(unit_direction.getY() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}
int main(int argc, char* argv[]){
	 auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

	// Ouvrir un fichier pour écrire l'image
    std::ofstream image_file("output.ppm");
    if (!image_file) {
        std::cerr << "Erreur : impossible de créer le fichier image.\n";
        return 1;
    }

    // Écrire l'en-tête du fichier PPM
    image_file << "P3\n" << image_width << " " << image_height << "\n255\n";

    // Paramètres de la caméra
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = Vect(0, 0, 0);

    auto viewport_u = Vect(viewport_width, 0, 0);
    auto viewport_v = Vect(0, -viewport_height, 0);

    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = camera_center - Vect(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Rendu de l'image
    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto Ray_direction = pixel_center - camera_center;
            Ray r(camera_center, Ray_direction);

            color pixel_color = Ray_color(r);
            write_color(image_file, pixel_color); // Écrit dans le fichier
        }
    }

    std::cout << "Image générée dans le fichier 'output.ppm'.\n";
    image_file.close();
    return 0;

}



