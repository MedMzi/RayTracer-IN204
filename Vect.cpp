#include "RayTracer.hpp"

// getter
double Vect::getX() const {return x;}
double Vect::getY() const {return y;}
double Vect::getZ() const {return z;}

//setter
void Vect::setX(double X) {x=X;}
void Vect::setY(double Y) {y=Y;}
void Vect::setZ(double Z) {z=Z;}

//addition
Vect Vect::operator+(const Vect& other) const{
	return Vect(x + other.getX(), y + other.getY(), z + other.getZ());
}

Vect& Vect::operator+=(const Vect& a){
	x += a.getX();
	y += a.getY();
	z += a.getZ();
	
	return *this;
}

//soustraction
Vect Vect::operator-() const {return Vect(-x, -y, -z);}

Vect Vect::operator-(const Vect& other) const{
	return Vect(x - other.getX(), y - other.getY(), z - other.getZ());
}

Vect& Vect::operator-=(const Vect& a){
	x -= a.getX();
	y -= a.getY();
	z -= a.getZ();
	
	return *this;
}

//produit scalaire
double Vect::operator*(const Vect& other) const {return x * other.getX() + y * other.getY() + z * other.getZ();}

//produit avec un scalaire
Vect Vect::operator*(double a) const {return Vect(x * a, y * a, z * a);}
Vect Vect::operator/(double a) const {return *this * (1.0 / a);}
Vect operator*(double a, const Vect& v) {return v * a;}

//produit Vectoriel	
Vect Vect::operator^(const Vect& other) const{
	double cx = y * other.getZ() - z * other.getY();
	double cy = z * other.getX() - x * other.getZ();
	double cz = x * other.getY() - y * other.getX();

	return Vect(cx, cy, cz);	
}

//norme
double Vect::norme() const {return sqrt(*this * *this);}

//vecteur unitaire
Vect Vect::Unit() const {	
	double l = norme();

	if (l == 0) {
		throw std::runtime_error("Vecteur nul");
	}

	return *this * (1 / l);
}

std::ostream& operator<<(std::ostream& os, const Vect& v){
	os << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")";
	return os;	
}



