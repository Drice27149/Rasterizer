#pragma once

#include <vector>
#include "Vector.hpp"

class Triangle{
public:
	Triangle(Vector vx, Vector vy, Vector vz);
private:
	Vector vertex[3];
	Vector normal;
};