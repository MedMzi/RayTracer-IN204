#include "Material.hpp"


bool material::scatter(const Ray& r_in, const RayIntersection& inters, color& attenuation, Ray& scattered) const{
    return false;
}

//lambertian

bool lambertian::scatter(const Ray& r_in, const RayIntersection& inters, color& attenuation, Ray& scattered) const{
    auto scatter_direction = inters.getNormal() + random_unit_vector();

    if (scatter_direction.negligeable())
        scatter_direction = inters.getNormal();

    scattered = Ray(inters.getPoint(), scatter_direction);
    attenuation = albedo;
    return true;
}

const color& lambertian::getAlbedo() const {return albedo;}

//metal

bool metal::scatter(const Ray& r_in, const RayIntersection& inters, color& attenuation, Ray& scattered) const{
    Vect reflected = reflect(r_in.getDirection(), inters.getNormal());
    reflected = reflected.Unit() + (fuzz * random_unit_vector());
    scattered = Ray(inters.getPoint(), reflected);
    attenuation = albedo;
    return (scattered.getDirection()*inters.getNormal() > 0);
}

const color& metal::getAlbedo() const {return albedo;}
