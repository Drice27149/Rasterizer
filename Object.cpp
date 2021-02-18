#include "Object.hpp"
#include "Loader.hpp"

Object::Object(std::string filename){
	Loader loader;
	loader.loadFile(filename);
	this->triangles = loader.triangles;
}

Object::Object(std::vector<Triangle> triangles): triangles(triangles) {
	
}