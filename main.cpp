#include "RayTracer.hpp"

int main(int argc, char* argv[]){
	Vector a = Vector(1,0,0);
	Vector b = Vector(0,1,0);
	Vector c = a^b;
	
	std::cout << c << std::endl;
	return 0;
}
