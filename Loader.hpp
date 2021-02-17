#include <iostream>
#include <vector>
#include "Triangle.hpp"

class Loader{
public:
	void loadFile(std::string filename);
private:
	std::vector<Triangle> triangles;
};