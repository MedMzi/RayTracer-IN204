#ifndef OBJET_HPP
#define OBJET_HPP

#include "ray.hpp"

class RayIntersection {
  public:
    Vect p;
    Vect normal;
    double t;
};

class Objet {
  public:
    virtual ~Objet() = default;

    virtual bool intersect(const ray& r, double ray_tmin, double ray_tmax, RayIntersection& rec) const = 0;
};

#endif
