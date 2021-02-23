#include "Triangle.hpp"

Triangle::Triangle(Vector vx, Vector vy, Vector vz){
	vertex[0] = vx;
	vertex[1] = vy;
	vertex[2] = vz;
	// normal = Vector::crossProduct(vx - vy, vz - vy);
	normal = Vector::crossProduct(vz - vy, vx - vy);
	normal.normalize();
}