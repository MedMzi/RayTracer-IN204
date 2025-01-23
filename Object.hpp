#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "RayTracer.hpp"
#include "Color.hpp"


class object {
    public:
        virtual ~object() {}

        virtual double hit(const Ray& r) const = 0;
};

class Sphere : public object{
    private:
        Vect center;
        double radius;
    
    public:
        Sphere() : Sphere(Vect(), 1.0) 
            {}
        
        Sphere(const Vect& center) : Sphere(center, 1.0) 
            {}
        
        Sphere(double radius) : Sphere(Vect(), radius) 
            {}

        Sphere(const Sphere& a) : Sphere(a.center, a.radius) 
            {}
        
        Sphere(const Vect& center, double radius) : center(center), radius(std::fmax(0, radius)) 
            {}

        const Vect& getCenter() const;
        double getRadius() const;

        void setCenter(const Vect& c);
        void setRadius(double r);

        //geometrie
        const double volume() const;    //volume

        virtual double hit(const Ray& r) const override;

};

class Rectangle : public object {
private:
    Vect minCorner;
    Vect maxCorner;

public:
    Rectangle() : Rectangle(Vect(), Vect(1.0, 1.0, 1.0)) 
        {}

    Rectangle(const Vect& center, double a, double b, double c) : Rectangle(center - Vect(a/2, b/2, c/2), center + Vect(a/2, b/2, c/2))
        {}

    Rectangle(const Vect& center, double a) : Rectangle(center - Vect(a/2, a/2, a/2), center + Vect(a/2, a/2, a/2))
        {}

    Rectangle(const Rectangle& a) : Rectangle(a.minCorner, a.maxCorner)   
        {}

    Rectangle(const Vect& corner1, const Vect& corner2){
        minCorner = Vect(
            fmin(corner1.getX(), corner2.getX()),
            fmin(corner1.getY(), corner2.getY()),
            fmin(corner1.getZ(), corner2.getZ())
        );
        maxCorner = Vect(
            fmax(corner1.getX(), corner2.getX()),
            fmax(corner1.getY(), corner2.getY()),
            fmax(corner1.getZ(), corner2.getZ())
        );
}

    const Vect& getMinCorner() const;
    const Vect& getMaxCorner() const;

    //geometrie
    const Vect getCenter() const; //centre
    const double geta() const;    //longueur d'un cote
    const double getb() const;    //largeur d'un cote
    const double getc() const;    //hauteur d'un cote
    const double volume() const;    //volume
    const double surface() const;   //surface
    const double surfaceab() const; //surface du cote ab
    const double surfacebc() const; //surface du cote bc
    const double surfaceca() const; //surface du cote ca

    void setMinCorner(const Vect& c);
    void setMaxCorner(const Vect& c);

    virtual double hit(const Ray& r) const override;
};

class Triangle : public object {
    private:
        Vect A;
        Vect B;
        Vect C;

    public:
        Triangle() : Triangle(Vect(), Vect(1.0, 1.0, 1.0), Vect(1.0, 1.0, 1.0))
            {}

        Triangle(const Vect& a, const Vect& b, const Vect& c) : A(a), B(b), C(c)
            {}

        Triangle(const Triangle& a) : Triangle(a.A, a.B, a.C)
            {}

        const Vect& getA() const;
        const Vect& getB() const;
        const Vect& getC() const;

        void setA(const Vect& a);
        void setB(const Vect& b);
        void setC(const Vect& c);

        //geometrie
        const Vect normal() const;  //normale
        const double area() const;  //aire
        const Vect centroid() const; //Centre de gravité

        virtual double hit(const Ray& r) const override;
};

class dotobj : public object {  // for .obj file
    private:
        std::vector<Triangle> triangles;
        Vect position;

    public:
        dotobj() : triangles() , position(Vect())
            {}

        dotobj(const dotobj& a) : triangles(a.triangles) , position(a.position)
            {}

        dotobj(const std::string& filename) : position(Vect()) {
            loadFromObjFile(filename);
        }

        dotobj(const std::string& filename, Vect position) : position(position) {
            loadFromObjFile(filename, position);
        }

        void loadFromObjFile(const std::string& filename, Vect position = Vect()); //charge un fichier .obj

        const std::vector<Triangle>& getTriangles() const;
        const Vect& getPosition() const;

        virtual double hit(const Ray& r) const override;
};

#endif