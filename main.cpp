#include "Color.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Material.hpp"

int main(int argc, char** argv) {

    // Ouvrir un fichier pour écrire l'image
    std::ofstream image_file("output.ppm");
    if (!image_file) {
        std::cerr << "Erreur : impossible de créer le fichier image.\n";
        return 1;
    }

    world w;



    auto material_ground = new lambertian(color(1, 0.8, 0.4));
    auto material_center = new lambertian(color(0.1, 0.7, 0.5));
    auto material_left = new metal(color(0.8, 0.8, 0.8), 0.5);
    auto material_right = new metal(color(0.5, 0.5, 0.5), 0.0);


 //   w.add(new Sphere(Vect(0,0,-1), 0.5, nullptr));
  //  w.add(new Sphere(Vect(0,-100.5,-1), 100, material_ground));
  //  w.add(new Sphere(Vect(0, -100.5, -1), 100));
 //   w.add(new Triangle(Vect(),Vect(),Vect()))
  // w.add(new Rectangle(Vect(-1,0,-1), 0.5));

  w.add(new Sphere(Vect( 0.0, -100.5, -1.0), 100.0, material_ground));
  w.add(new Sphere(Vect( 0.0,    0.0, -1.2),   0.5, material_center));
  w.add(new Sphere(Vect(-1.0,    0.0, -1.0),   0.5, material_left));
  w.add(new Sphere(Vect( 1.0,    0.0, -1.0),   0.5, material_right));


    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(w, image_file);

    std::cout << "Image générée dans le fichier 'output.ppm'.\n";
    image_file.close();

    delete material_right;
    delete material_left;
    delete material_center;
    delete material_ground;

    return 0;
}


