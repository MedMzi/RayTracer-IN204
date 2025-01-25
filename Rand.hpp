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
    if (on_unit_sphere*normal > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

#endif