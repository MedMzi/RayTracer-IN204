#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "RayTracer.hpp"
#include "Color.hpp"

class object {
    protected:
        mutable Vect center;
    public:
        virtual ~object() {}
        object() {}

        virtual double hit(const Ray& r) const = 0;
        inline const Vect& getCenter() const { return center; };
};

class RayIntersection {
    private:
        Vect p;
        Vect normal;
        double t;
        bool isOut;
    public:
        RayIntersection() : RayIntersection(Vect(), Vect(), 0.0, false)
            {}

        RayIntersection(const RayIntersection& a) : RayIntersection(a.p, a.normal, a.t, a.isOut) 
            {}

        RayIntersection(Vect point, Vect norm, double x, bool b) : p(point) , normal(norm), t(x), isOut(b)
            {}

        RayIntersection(const object& obj, const Ray& r){
            t = obj.hit(r);
            p = r.position(t); 
            normal = (p - obj.getCenter()).Unit() ;
            isOut = r.getDirection()*normal < 0 ;
           // normal = isOut ? normal : -normal;
        }

        const Vect& getPoint();
        const Vect& getNormal();
        double getHit();
        bool isOutside();



};

class Sphere : public object{
    private:
        double radius;
    
    public:
        Sphere() : Sphere(Vect(), 1.0) 
            {}
        
        Sphere(const Vect& center) : Sphere(center, 1.0) 
            {}
        
        Sphere(double radius) : Sphere(Vect(), std::fabs(radius)) 
            {}

        Sphere(const Sphere& a) : Sphere(a.center, a.radius) 
            {}
        
        Sphere(const Vect& Center, double radius) : radius(std::fabs(radius)) 
            {center = Center;}

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

        center = (minCorner + maxCorner) / 2;
}

    const Vect& getMinCorner() const;
    const Vect& getMaxCorner() const;

    //geometrie
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

        Triangle(const Triangle& a) : Triangle(a.A, a.B, a.C)
            {}

        Triangle(const Vect& a, const Vect& b, const Vect& c) : A(a), B(b), C(c)
            {center = (A + B + C) / 3;}

        const Vect& getA() const;
        const Vect& getB() const;
        const Vect& getC() const;

        void setA(const Vect& a);
        void setB(const Vect& b);
        void setC(const Vect& c);

        //geometrie
        const Vect normal() const;  //normale
        const double area() const;  //aire

        virtual double hit(const Ray& r) const override;
};

class dotobj : public object {  // for .obj file
    private:
        std::vector<Triangle> triangles;
        Vect position;

    public:
        dotobj() : triangles() , position(Vect())
            {center = Vect();}

        dotobj(const dotobj& a) : triangles(a.triangles) , position(a.position)
            {center = a.getCenter();}

        dotobj(const std::string& filename) : dotobj(filename, Vect()) 
            {}

        dotobj(const std::string& filename, Vect position) : position(position) {
            loadFromObjFile(filename, position);
            //calcul du centre (barycentre de tout les centres de gravité)
            center = Vect(0, 0, 0); 
            double totalArea = 0.0;
            for (const Triangle& triangle : triangles) {
                double area = triangle.area();
                center += triangle.getCenter() * area;    // pondere par la surface du triangle
                totalArea += area;
            }

            center = center / totalArea ; 
        }

        void loadFromObjFile(const std::string& filename, Vect position = Vect()); //charge un fichier .obj

        const std::vector<Triangle>& getTriangles() const;
        const Vect& getPosition() const;

        virtual double hit(const Ray& r) const override;
};

class world : public object {
    private:
        std::vector<object*> objects;

    public:
        world() : objects()
            {center = Vect();}

        world(const world& a) : objects(a.objects)
            {center = a.getCenter();}

        ~world() {
            for (object* obj : objects) {
                delete obj;
            }
        }

        void add(object* obj);

        virtual double hit(const Ray& r) const override;
};

#endif