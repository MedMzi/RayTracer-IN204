#include "Color.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Material.hpp"

int main() {

        // Ouvrir un fichier pour écrire l'image
    std::ofstream image_file("output.ppm");
    if (!image_file) {
        std::cerr << "Erreur : impossible de créer le fichier image.\n";
        return 1;
    }

    world w;
    std::vector<material*> materials; // Container to store all allocated materials

    auto ground_material = new lambertian(color(0.5, 0.5, 0.5));
    w.add(new Sphere(Vect(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Vect center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Vect(4, 0.2, 0)).norme() > 0.9) {
                material* sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random_Vect();
                    sphere_material = new lambertian(albedo);
                    w.add(new Sphere(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random_Vect(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = new metal(albedo, fuzz);
                    w.add(new Sphere(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = new dielectric(1.5);
                    w.add(new Sphere(center, 0.2, sphere_material));
                }

                materials.push_back(sphere_material);
            }
        }
    }

    auto material1 = new dielectric(1.5);
    w.add(new Sphere(Vect(0, 1, 0), 1.0, material1));

    auto material2 = new lambertian(color(0.4, 0.2, 0.1));
    w.add(new Sphere(Vect(-4, 1, 0), 1.0, material2));

    auto material3 = new metal(color(0.7, 0.6, 0.5), 0.0);
    w.add(new Sphere(Vect(4, 1, 0), 1.0, material3));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1200;
    cam.samples_per_pixel = 500;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.lookfrom = Vect(13,2,3);
    cam.lookat   = Vect(0,0,0);
    cam.vup      = Vect(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;

    cam.render(w, image_file);

    image_file.close();
}


