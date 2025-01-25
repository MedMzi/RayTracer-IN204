#include "Object.hpp"

//getters
const Vect& Triangle::getA() const {return A;}
const Vect& Triangle::getB() const {return B;}
const Vect& Triangle::getC() const {return C;}

//setters
void Triangle::setA(const Vect& a) {A = a;}
void Triangle::setB(const Vect& b) {B = b;}
void Triangle::setC(const Vect& c) {C = c;}

//geométrie
const double Triangle::area() const{
    return 0.5 * getNormal().norme();
}



//hit
double Triangle::hit(const Ray& r) const {      //on utilise l'algorithme de Möller-Trumbore
    Vect e1 = B - A;
    Vect e2 = C - A;
    Vect h = r.getDirection() ^ e2;
    double a = e1 * h;
    if (a > -0.00001 && a < 0.00001) {
        return -1.0;
    }
    double f = 1.0 / a;
    Vect s = r.getOrigin() - A;
    double u = f * (s * h);
    if (u < 0.0 || u > 1.0) {
        return -1.0;
    }
    Vect q = s ^ e1;
    double v = f * (r.getDirection() * q);
    if (v < 0.0 || u + v > 1.0) {
        return -1.0;
    }
    double t = f * (e2 * q);
    
    if (t > ray_tmin && t < ray_tmax) {
        return t;
    }
    return -1.0;
}