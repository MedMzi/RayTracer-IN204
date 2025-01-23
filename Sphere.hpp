#ifndef SPHERE_H
#define SPHERE_H

#include "Objet.hpp"
#include "RayTracer.hpp"

class Sphere : public Objet {
private:
    Vect center;
    double radius;
public:
    Sphere(const Vect& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

    bool hit(const Ray& r, double ray_tmin, double ray_tmax, RayIntersection& rec) const override {
        Vect oc = center - r.getOrigin(); // Vecteur entre le centre de la sphère et l'origine du rayon
        auto a = r.getDirection() * r.getDirection(); // Coefficient 'a' (longueur au carré de la direction)
        auto b = -2.0 * (r.getDirection() * oc); // Coefficient 'b'
        auto c = (oc * oc) - radius * radius; // Coefficient 'c'

        auto discriminant = b * b - 4 * a * c; // Calcul du discriminant
        if (discriminant < 0) {
            return false; // Pas d'intersection
        }

        // Racine carrée du discriminant
        auto sqrtd = std::sqrt(discriminant);

        // Trouver la racine la plus proche dans [ray_tmin, ray_tmax].
        auto root = (-b - sqrtd) / (2.0 * a);
        if (root <= ray_tmin || ray_tmax <= root) {
            root = (-b + sqrtd) / (2.0 * a);
            if (root <= ray_tmin || ray_tmax <= root)
                return false;
        }

        // Mise à jour des informations d'intersection
        rec.t = root;
        rec.p = r.getPointAt(rec.t); // Point d'intersection
        rec.normal = (rec.p - center) / radius; // Normale à la surface au point d'intersection

        return true;
    }


};

#endif