#include "RayTracer.hpp"

//getter
const Vector& Ray::getOrigin() const {return Origin;}
const Vector& Ray::getDirection() const {return Direction;}	

//setter
void Ray::setOrigin(const Vector& o) {Origin = o;}
void Ray::setDirection(const Vector& v) {Direction = v.Unit();}

//position
Vector Ray::position(double t) { return Origin + t*Direction ;}

//flux
std::ostream& operator<<(std::ostream& os, const Ray& r){
	os << "point of origin " << r.getOrigin() << " is headed towards " << r.getDirection() ;
	return os;	
}
