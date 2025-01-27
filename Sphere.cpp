#include "Object.hpp"

//getter
double Sphere::getRadius() const {return radius;}

//setter
void Sphere::setCenter(const Vect& c) {center = c;}
void Sphere::setRadius(double r) {radius = std::fmax(0, r);}

//geometrie
const double Sphere::volume() const {
    return 4.0/3.0 * M_PI * radius * radius * radius;
}

const Vect& Sphere::getNormal(const Vect& p) const{
    norm = (p - center).Unit();
    return norm;
}

//hit
double Sphere::hit(const Ray& r) const {
    Vect oc = center - r.getOrigin();
    auto a = r.getDirection() * r.getDirection();
    auto b = -2.0 * (r.getDirection() * oc);
    auto c = (oc* oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return -1.0; // pas de racine
    }

    discriminant = std::sqrt(discriminant);
    auto root = (-b - discriminant) / (2.0 * a);

    //voir si la racine plus petite est valide
    if (root > ray_tmin && root < ray_tmax) {
        return root; 
    }

    //essayer l'autre
    root = (-b + discriminant) / (2.0 * a);
    if (root > ray_tmin && root < ray_tmax) {
        return root; // Valid second root
    }

    //retourner -1 pour éviter toute confusion
    return -1.0;
}

object* Sphere::clone() const {
        return new Sphere(*this);
}
