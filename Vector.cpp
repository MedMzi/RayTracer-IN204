#include "RayTracer.hpp"

// getter
double Vector::getX() const {return x;}
double Vector::getY() const {return y;}
double Vector::getZ() const {return z;}

//setter
void Vector::setX(double X) {x=X;}
void Vector::setY(double Y) {y=Y;}
void Vector::setZ(double Z) {z=Z;}

//addition
Vector Vector::operator+(const Vector& other) const{
	return Vector(x + other.getX(), y + other.getY(), z + other.getZ());
}

Vector& Vector::operator+=(const Vector& a){
	x += a.getX();
	y += a.getY();
	z += a.getZ();
	
	return *this;
}

//soustraction
Vector Vector::operator-() const {return Vector(-x, -y, -z);}

Vector Vector::operator-(const Vector& other) const{
	return Vector(x - other.getX(), y - other.getY(), z - other.getZ());
}

Vector& Vector::operator-=(const Vector& a){
	x -= a.getX();
	y -= a.getY();
	z -= a.getZ();
	
	return *this;
}

//produit scalaire
double Vector::operator*(const Vector& other) const {return x * other.getX() + y * other.getY() + z * other.getZ();}

//produit avec un scalaire
Vector Vector::operator*(double a) const {return Vector(x * a, y * a, z * a);}
Vector operator*(double a, const Vector& v) {return v * a;}

//produit vectoriel	
Vector Vector::operator^(const Vector& other) const{
	double cx = y * other.getZ() - z * other.getY();
	double cy = z * other.getX() - x * other.getZ();
	double cz = x * other.getY() - y * other.getX();

	return Vector(cx, cy, cz);	
}

//norme
double Vector::norme() const {return sqrt(*this * *this);}

//vecteur unitaire
Vector Vector::Unit() const {	
	double l = norme();

	if (l == 0) {
		throw std::runtime_error("Vecteur nul");
	}

	return *this * (1 / l);
}

std::ostream& operator<<(std::ostream& os, const Vector& v){
	os << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")";
	return os;	
}



