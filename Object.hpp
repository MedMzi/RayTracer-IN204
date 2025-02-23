#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Color.hpp"
#include <memory>

class material;

class object {
    protected:
        mutable Vect center;
        mutable Vect norm;
    public:
        mutable std::shared_ptr<material> mat = nullptr;

        double ray_tmin = 0.0001;
        double ray_tmax = INFINITY;

        virtual ~object()
            {}
        
        object() : object(nullptr) 
            {}

        object(std::shared_ptr<material> m) : mat(m)
            {}

        virtual double hit(const Ray& r) const = 0;
        virtual object* clone() const = 0;

        virtual const Vect& getNormal(const Vect& p = Vect()) const {
            return norm;
        };

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
            t = obj.hit(r); //hit va donc trouver t mais aussi changer la norme pour l'appel de getNormal() ainsi que mat
            p = r.position(t); 
            normal = obj.getNormal(p) ;
            isOut = r.getDirection()*normal < 0 ;
            normal = isOut ? normal : -normal;
            mat = obj.mat;
        }

        const Vect& getPoint() const;
        const Vect& getNormal() const;
        double getHit() const;
        bool isOutside() const;

        std::shared_ptr<material> mat;



};

class Sphere : public object{
    private:
        double radius;
    
    public:
        Sphere() : Sphere(Vect(), 1.0, nullptr) 
            {}
        
        Sphere(const Vect& center, std::shared_ptr<material> m) : Sphere(center, 1.0, m) 
            {}
        
        Sphere(double radius, std::shared_ptr<material> m) : Sphere(Vect(), std::fabs(radius), m) 
            {}

        Sphere(const Sphere& a) : Sphere(a.center, a.radius, a.mat) 
            {}
        
        Sphere(const Vect& Center, double radius, std::shared_ptr<material> m) : object(m) , radius(std::fabs(radius)) {
            center = Center;
            }

        double getRadius() const;

        void setCenter(const Vect& c);
        void setRadius(double r);

        //geometrie
        const double volume() const;    //volume
        virtual const Vect& getNormal(const Vect& p) const override;

        virtual double hit(const Ray& r) const override;
        virtual object* clone() const override;

};

class Rectangle : public object {
private:
    Vect minCorner;
    Vect maxCorner;

public:
    Rectangle() : Rectangle(Vect(), Vect(1.0, 1.0, 1.0), nullptr) 
        {}

    Rectangle(const Vect& center, double a, double b, double c, std::shared_ptr<material> m) : Rectangle(center - Vect(a/2, b/2, c/2), center + Vect(a/2, b/2, c/2), m)
        {}

    Rectangle(const Vect& center, double a, std::shared_ptr<material> m) : Rectangle(center - Vect(a/2, a/2, a/2), center + Vect(a/2, a/2, a/2), m)
        {}

    Rectangle(const Rectangle& a) : Rectangle(a.minCorner, a.maxCorner, a.mat)   
        {}

    Rectangle(const Vect& corner1, const Vect& corner2, std::shared_ptr<material> m) : object(m) {
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

        ray_tmin = -INFINITY;
        ray_tmax = INFINITY;
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
    virtual const Vect& getNormal(const Vect& p) const override;

    void setMinCorner(const Vect& c);
    void setMaxCorner(const Vect& c);

    virtual double hit(const Ray& r) const override;
    virtual object* clone() const override;
};

class Triangle : public object {    //les triangles qui vont constituer les polygones du modele blender (dotobj)
    private:
        Vect A;
        Vect B;
        Vect C;

    public:
        Triangle() : Triangle(Vect(), Vect(1.0, 1.0, 1.0), Vect(1.0, 1.0, 1.0), nullptr)
            {}

        Triangle(const Triangle& a) : Triangle(a.A, a.B, a.C, a.mat)
            {}

        Triangle(const Vect& a, const Vect& b, const Vect& c, std::shared_ptr<material> m) : object(m), A(a), B(b), C(c){
            center = (A + B + C) / 3;
            Vect edge1 = B - A;
            Vect edge2 = C - A;
            norm = edge1^edge2;
        }

        const Vect& getA() const;
        const Vect& getB() const;
        const Vect& getC() const;

        void setA(const Vect& a);
        void setB(const Vect& b);
        void setC(const Vect& c);

        //geometrie
        const double area() const;  //aire

        virtual double hit(const Ray& r) const override;
        virtual object* clone() const override;
};

class dotobj : public object {  // for .obj file
    private:
        std::vector<Triangle> triangles;
        Vect position;

    public:
        dotobj() : object(), triangles() , position(Vect()){
            center = Vect();
        }

        dotobj(const dotobj& a) : object(), triangles(a.triangles) , position(a.position){
            center = a.getCenter();
        }

        dotobj(const std::string& filename) : dotobj(filename, Vect()) 
            {}

        dotobj(const std::string& filename, Vect position) : object(), position(position) {
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
        virtual object* clone() const override;
};

class world : public object {
    private:
        std::vector<object*> objects;

    public:
        world() : object(), objects(){
            center = Vect();
        }

        world(const world& a) : object(), objects(){
            for (const auto& obj : a.objects) {
                objects.push_back(obj->clone()); // cloner pour deep copy
            }

            center = a.getCenter();
        }

        ~world() {
            for (object* obj : objects) {
                delete obj;
            }
            objects.clear();
        }

        void add(object* obj);

        virtual double hit(const Ray& r) const override;

        virtual object* clone() const override;
};

#endif