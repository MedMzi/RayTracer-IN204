#ifndef RAND_HPP
#define RAND_HPP
#include <random>
#include "RayTracer.hpp"

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

inline Vect random_Vect(double min = 0, double max = 1) {
    return Vect(random_double(min,max), random_double(min,max), random_double(min,max));
}

inline Vect random_unit_vector() {
    while (true) {
        auto p = random_Vect(-1,1);
        auto norme = p.norme();
        if (1e-160 < norme && norme <= 1)
            return p.Unit();
    }
}

inline Vect random_on_hemisphere(const Vect& normal) {
    Vect on_unit_sphere = random_unit_vector();
    if (on_unit_sphere*normal > 0.0) // meme hemisphere que normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

inline Vect random_in_unit_disk() {
    while (true) {
        auto p = Vect(random_double(-1,1), random_double(-1,1), 0);
        if (p.norme() < 1){
            return p;
        }
    }
}

inline double clamp(double x, double min = 0.0, double max=0.999) {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

inline Vect reflect(const Vect& v, const Vect& n) {
    return v - 2*(v*n)*n;
}

inline Vect refract(const Vect& uv, const Vect& n, double etai_over_etat) {
    auto cos_theta = std::fmin(-uv*n, 1.0);
    Vect r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Vect r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp*r_out_perp)) * n;
    return r_out_perp + r_out_parallel;
}

inline double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

#endif