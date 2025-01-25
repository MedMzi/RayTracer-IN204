#include "Object.hpp"

//getter
const Vect& Rectangle::getMinCorner() const {return minCorner;}
const Vect& Rectangle::getMaxCorner() const {return maxCorner;}

//setter
void Rectangle::setMinCorner(const Vect& c) {minCorner = c;}
void Rectangle::setMaxCorner(const Vect& c) {maxCorner = c;}

//geometrie
const double Rectangle::geta() const {
    return maxCorner.getX() - minCorner.getX();
}

const double Rectangle::getb() const {
    return maxCorner.getY() - minCorner.getY();
}

const double Rectangle::getc() const {
    return maxCorner.getZ() - minCorner.getZ();
}

const double Rectangle::volume() const {
    return geta() * getb() * getc();
}

const double Rectangle::surfaceab() const {
    return geta() * getb();
}

const double Rectangle::surfacebc() const {
    return getb() * getc();
}

const double Rectangle::surfaceca() const {
    return getc() * geta();
}

const double Rectangle::surface() const {
    return 2 * (surfaceab() + surfacebc() + surfaceca());
}

//hit
double Rectangle::hit(const Ray& r) const {     // on utilise l'algorithme "Slab Method"
    double tmin = -INFINITY;
    double tmax = INFINITY;

    for (int i = 0; i < 3; i++) {
        double t0 = (minCorner[i] - r.getOrigin()[i]) / r.getDirection()[i];
        double t1 = (maxCorner[i] - r.getOrigin()[i]) / r.getDirection()[i];

        if (t0 > t1) {
            std::swap(t0, t1);
        }

        tmin = std::fmax(t0, tmin);
        tmax = std::fmin(t1, tmax);

        if (tmin > tmax) {
            return -1.0;
        }
    }

    return tmin;
}

const Vect& Rectangle::getNormal(const Vect& p) const {
    float epsilon = 0.0000000001f;

    if (fabs(p.getZ() - maxCorner.getZ()) < epsilon) {
        norm = Vect(0.0, 0.0, 1.0);  
        return norm;
    }

    if (fabs(p.getX() - maxCorner.getX()) < epsilon) {
        norm = Vect(1.0, 0.0, 0.0);  
        return norm;
    }

   if (fabs(p.getY() - maxCorner.getY()) < epsilon) {
        norm = Vect(0.0, 1.0, 0.0);  
        return norm;
    }

    if (fabs(p.getX() - minCorner.getX()) < epsilon) {
        norm = Vect(-1.0, 0.0, 0.0);  
        return norm;
    }

    if (fabs(p.getY() - minCorner.getY()) < epsilon) {
        norm = Vect(0.0, -1.0, 0.0);  
        return norm;
    }

    if (fabs(p.getZ() - minCorner.getZ()) < epsilon) {
        norm = Vect(0.0, 0.0, -1.0); 
        return norm;
    }

    // pour eviter les erreurs
    return norm;
}