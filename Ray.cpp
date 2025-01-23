#include "RayTracer.hpp"

//getter
const Vect& Ray::getOrigin() const {return Origin;}
const Vect& Ray::getDirection() const {return Direction;}	

//setter
void Ray::setOrigin(const Vect& o) {Origin = o;}
void Ray::setDirection(const Vect& v) {Direction = v.Unit();}

//position
Vect Ray::position(double t) const { return Origin + t*Direction ;}

//flux
std::ostream& operator<<(std::ostream& os, const Ray& r){
	os << "point of origin " << r.getOrigin() << " is headed towards " << r.getDirection() ;
	return os;	
}
