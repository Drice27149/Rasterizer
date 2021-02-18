#pragma once

#include "Vector.hpp"

class Light {
public:
	Light(Vector position, Vector Intensity);
public:
	Vector position;
	Vector intensity;
};