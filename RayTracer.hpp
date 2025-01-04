#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <iostream>
#include <cmath>

class Vector{
	private:
		double x,y,z;
	
	public:
		Vector() : Vector(0,0,0)
			{}
		
		Vector(double a) : Vector(a,a,a) 
			{}
			
		Vector(const Vector& a) : Vector(a.getX(), a.getY(), a.getZ())
			{}
		
		Vector(double x, double y, double z) : x(x), y(y), z(z)
			{}
	    		
	    	double getX() const;	//getter X
		double getY() const;	//getter Y
		double getZ() const;	//getter Z
		
		void setX(double X);	//setter X
		void setY(double Y);	//setter Y
		void setZ(double Z);	//setter Z
		
		Vector operator+(const Vector& other) const;	//addition 
		Vector& operator+=(const Vector& a);
		Vector operator-() const;			//soustraction
		Vector operator-(const Vector& other) const;	
		Vector& operator-=(const Vector& a); 
	
		double operator*(const Vector& other) const;	//produit scalaire
		Vector operator*(double a) const;	//produit avec un scalaire	
		Vector operator^(const Vector& other) const;	//produit vectoriel	
		
		
		double norme() const;	//norme
		Vector Unit() const;	//vecteur unitaire		
};

Vector operator*(double a, const Vector& v);			//produit avec un scalaire à gauche
std::ostream& operator<<(std::ostream& os, const Vector& v);	//insertion dans un flux (print)

class Ray{
	private:
		Vector Origin;		//point d'origine du rayon
		Vector Direction;	//direction du rayon
		
	public:
		Ray() : Ray(Vector(),Vector(1,1,1).Unit())
			{}
			
		Ray(const Ray& a) : Ray(a.getOrigin(), a.getDirection())
			{}
		
		Ray(Vector ori, Vector dir) : Origin(ori) , Direction(dir.Unit())
			{}
		
		const Vector& getOrigin() const;	//getter origin
		const Vector& getDirection() const;	//getter direction
		
		void setOrigin(const Vector& o);		//setter origin
		void setDirection(const Vector& v);		//setter direction	
		
		Vector position(double t);		//retrouve la position du rayon selon le paramètre t
};
std::ostream& operator<<(std::ostream& os, const Ray& r);	//insertion dans un flux (print)

#endif
