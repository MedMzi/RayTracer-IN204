#include "Object.hpp"

const Vect& RayIntersection::getPoint() {return p;}
const Vect& RayIntersection::getNormal() {return normal;}
double RayIntersection::getHit() {return t;}
bool RayIntersection::isOutside() {return isOut;}
