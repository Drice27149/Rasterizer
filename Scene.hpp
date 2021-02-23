#pragma once

#include <vector>
#include "Object.hpp"
#include "Vector.hpp"
#include "Light.hpp"

class Scene {
public:
	Scene(int width, int height);
	void add(Object* object);
	void add(Light* light);
public:
	int width;
	int height;
	std::vector<Object*> objects;
	std::vector<Light*> lights;
	Vector Ia;					// ambient lighting
};