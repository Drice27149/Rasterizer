#pragma once

#include <vector>
#include <iostream>
#include "Triangle.hpp"

class Object {
public:
	Object(std::string filename);
	Object(std::vector<Triangle> triangles);
private:
	std::vector<Triangle> triangles;
};
