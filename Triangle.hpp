#pragma once

#include <vector>
#include "Vector.hpp"

class Triangle{
public:
	Triangle(Vector vx, Vector vy, Vector vz);
public:
	Vector vertex[3];
	Vector normal;
	Vector color;
};