#include "Object.hpp"

const Vect& RayIntersection::getPoint() const {return p;}
const Vect& RayIntersection::getNormal() const {return normal;}
double RayIntersection::getHit() const {return t;}
bool RayIntersection::isOutside() const {return isOut;}
