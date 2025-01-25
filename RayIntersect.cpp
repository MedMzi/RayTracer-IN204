#include "Object.hpp"
/*
//Object
Material* object::getMaterial() const {return mat;}
void object::setMaterial(Material* m) {
    if (mat){
        delete mat;
    }
    mat = m;
}
*/
//RayIntersection
const Vect& RayIntersection::getPoint() const {return p;}
const Vect& RayIntersection::getNormal() const {return normal;}
double RayIntersection::getHit() const {return t;}
bool RayIntersection::isOutside() const {return isOut;}
/*
Material* RayIntersection::getMaterial() const {return mat;}

void RayIntersection::setMaterial(Material* m) {
    if (mat){
        delete mat;
    }
    mat = m;
}
*/
