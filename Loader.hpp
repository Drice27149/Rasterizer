#include <iostream>
#include <vector>
#include "Triangle.hpp"

class Loader{
public:
	void loadFile(std::string filename);
public:
	std::vector<Triangle> triangles;
};