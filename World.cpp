#include "Object.hpp"

void world::add(object* obj) {
    objects.push_back(obj);
}

double world::hit(const Ray& r) const {
    double closest = INFINITY;
    for (object* obj : objects) {
        double hit = obj->hit(r);
        if ((hit < closest) && (hit > 0.0)) {
            closest = hit;
        }
    }
    if (closest == INFINITY) {
        return -1;
    }

    return closest;
}