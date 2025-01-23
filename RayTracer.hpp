#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

class Vect{
	private:
		double x,y,z;
	
	public:
		Vect() : Vect(0,0,0)
			{}
		
		Vect(double a) : Vect(a,a,a) 
			{}
			
		Vect(const Vect& a) : Vect(a.getX(), a.getY(), a.getZ())
			{}
		
		Vect(double x, double y, double z) : x(x), y(y), z(z)
			{}
	    		
	    double getX() const;	//getter X
		double getY() const;	//getter Y
		double getZ() const;	//getter Z
		
		void setX(double X);	//setter X
		void setY(double Y);	//setter Y
		void setZ(double Z);	//setter Z
		
		Vect operator+(const Vect& other) const;	//addition 
		Vect& operator+=(const Vect& a);
		Vect operator-() const;			//soustraction
		Vect operator-(const Vect& other) const;	
		Vect& operator-=(const Vect& a); 
	
		double operator*(const Vect& other) const;	//produit scalaire
		Vect operator*(double a) const;	//produit avec un scalaire	
		Vect operator/(double a) const;	//division par un scalaire	
		Vect operator^(const Vect& other) const;	//produit Vectiel	
		
		double operator[](int index) const; //pour pouvoir creer certaine boucle sur les dimensions
		
		double norme() const;	//norme
		Vect Unit() const;	//vecteur unitaire		
}; 

Vect operator*(double a, const Vect& v);			//produit avec un scalaire à gauche
std::ostream& operator<<(std::ostream& os, const Vect& v);	//insertion dans un flux (print)

class Ray{
	private:
		Vect Origin;		//point d'origine du rayon
		Vect Direction;	//direction du rayon
		
	public:
		Ray() : Ray(Vect(),Vect(1,1,1).Unit())
			{}
			
		Ray(const Ray& a) : Ray(a.getOrigin(), a.getDirection())
			{}
		
		Ray(Vect ori, Vect dir) : Origin(ori) , Direction(dir.Unit())
			{}
		
		const Vect& getOrigin() const;	//getter origin
		const Vect& getDirection() const;	//getter direction
		
		void setOrigin(const Vect& o);		//setter origin
		void setDirection(const Vect& v);		//setter direction	
		
		Vect position(double t) const;		//retrouve la position du rayon selon le paramètre t
};
std::ostream& operator<<(std::ostream& os, const Ray& r);	//insertion dans un flux (print)

#endif
