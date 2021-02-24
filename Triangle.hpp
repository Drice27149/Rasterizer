#pragma once

#include <vector>
#include "Vector.hpp"

class Triangle{
public:
	Triangle(Vector vx, Vector vy, Vector vz);
public:
	Vector vertex[3];
	Vector normals[3]; 	// vertex normal
	Vector st[3];		// vertex texture coordinates
	int vid[3]; 		// vertex id
	Vector normal; 		// face normal
	Vector Kd;
	Vector Ks;
	Vector Ka;
};