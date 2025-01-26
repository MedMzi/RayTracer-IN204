#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Color.hpp"
#include "Object.hpp"

class material {
  public:
    virtual ~material() = default;

    virtual bool scatter(const Ray& r_in, const RayIntersection& inters, color& attenuation, Ray& scattered) const;
};


class lambertian : public material {
    private:
        color albedo;
    public:
        lambertian() : lambertian(color()) 
            {}

        lambertian(const lambertian& a) : lambertian(a.albedo) 
            {}

        lambertian(const color& albedo) : albedo(albedo) 
            {}

        const color& getAlbedo() const;

        virtual bool scatter(const Ray& r_in, const RayIntersection& inters, color& attenuation, Ray& scattered) const override;
};

class metal : public material {
    private:
        color albedo;
        double fuzz;
    public:
        metal() : metal(color(),0.0) 
            {}

        metal(const metal& a) : metal(a.albedo, a.fuzz) 
            {}

        metal(const color& albedo, double f) : albedo(albedo), fuzz(f) 
            {}

        const color& getAlbedo() const;

        virtual bool scatter(const Ray& r_in, const RayIntersection& inters, color& attenuation, Ray& scattered) const override;
};

class dielectric : public material {
    private:
        double refraction_index;

        static double reflectance(double cosine, double refraction_index);
    
    public:
        dielectric() : dielectric(1) 
            {}

        dielectric(const dielectric& a) : dielectric(a.refraction_index) 
            {}

        dielectric(double f) : refraction_index(f) 
            {}

        double getRefractionIndex() const;

        virtual bool scatter(const Ray& r_in, const RayIntersection& inters, color& attenuation, Ray& scattered) const override;


};

#endif