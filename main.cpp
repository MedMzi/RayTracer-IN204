#include "Color.hpp"
#include "Object.hpp"
#include "Camera.hpp"


int main(int argc, char** argv) {

    // Ouvrir un fichier pour écrire l'image
    std::ofstream image_file("output.ppm");
    if (!image_file) {
        std::cerr << "Erreur : impossible de créer le fichier image.\n";
        return 1;
    }

    world w;

    w.add(new Sphere(Vect(1, 0, -1), 0.5));
 //   w.add(new Sphere(Vect(0, -100.5, -1), 100));
 //   w.add(new Triangle(Vect(),Vect(),Vect()))
    w.add(new Rectangle(Vect(-1,0,-1), 0.5));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;

    cam.render(w, image_file);

    std::cout << "Image générée dans le fichier 'output.ppm'.\n";
    image_file.close();

    return 0;
}


