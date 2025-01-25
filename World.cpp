#include "Object.hpp"

void world::add(object* obj) {
    objects.push_back(obj);
}

double world::hit(const Ray& r) const {
    double closest = INFINITY;
 //   center = Vect();
    for (object* obj : objects) {
        double hit = obj->hit(r);
        if ((hit < closest) && (hit > 0.0)) {
            closest = hit;
            center = obj->getCenter();
            norm = obj->getNormal(r.position(closest));
        }
    }
    if (closest == INFINITY) {
        return -1;
    }

    return closest;
}