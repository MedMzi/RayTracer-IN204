#include "Object.hpp"

void world::add(object* obj) {
    objects.push_back(obj);
}

double world::hit(const Ray& r) const {
    double closest = ray_tmax;
 //   center = Vect();
    for (object* obj : objects) {
        double hit = obj->hit(r);
        if ((hit < closest) && (hit > ray_tmin)) {
            closest = hit;
            center = obj->getCenter();
            norm = obj->getNormal(r.position(closest));
            mat = obj->mat;
        }
    }
    if (closest == ray_tmax) {
        return -1.0;
    }

    return closest;
}