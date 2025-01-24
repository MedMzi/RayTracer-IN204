#include "Color.hpp"
#include "Object.hpp"
#include "Camera.hpp"


int main(int argc, char** argv) {
    world w;

    w.add(new Sphere(Vect(0, 0, -1), 0.5));
    w.add(new Sphere(Vect(0, -100.5, -1), 100));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;

    cam.render(w);

    return 0;
}


