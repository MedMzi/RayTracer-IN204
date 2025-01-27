#include "Material.hpp"

object::~object() {
    if (mat != nullptr) {
        delete mat;
        mat = nullptr;
    }
}

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

//dielectric
bool dielectric::scatter(const Ray& r_in, const RayIntersection& inters, color& attenuation, Ray& scattered) const{
    attenuation = color(1.0);
    double refraction_ratio = inters.isOutside() ? (1.0 / refraction_index) : refraction_index;

    Vect unit_direction = r_in.getDirection().Unit();
    double cos_theta = std::fmin((-unit_direction * inters.getNormal()), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vect direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
        direction = reflect(unit_direction, inters.getNormal());
    else
        direction = refract(unit_direction, inters.getNormal(), refraction_ratio);

    scattered = Ray(inters.getPoint(), direction);
    return true;
}

double dielectric::reflectance(double cosine, double refraction_index){
    double r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 *= r0 ;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}
