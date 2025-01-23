#include "Object.hpp"

//getter
const Vect& Sphere::getCenter() const {return center;}
double Sphere::getRadius() const {return radius;}

//setter
void Sphere::setCenter(const Vect& c) {center = c;}
void Sphere::setRadius(double r) {radius = std::fmax(0, r);}

//geometrie
const double Sphere::volume() const {
    return 4.0/3.0 * M_PI * radius * radius * radius;
}

//hit
double Sphere::hit(const Ray& r) const {
    Vect oc = center - r.getOrigin();
    auto a = r.getDirection() * r.getDirection();
    auto b = -2.0 * (r.getDirection() * oc);
    auto c = (oc* oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - std::sqrt(discriminant) ) / (2.0*a);	//on cherche le premier contact donc le plus petit
    }
}
