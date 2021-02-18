#include "Scene.hpp"

Scene::Scene(int width, int height): width(width), height(height) {
	
}

void Scene::add(Object* object){
	objects.push_back(object);
}

void Scene::add(Light* light){
	lights.push_back(light);
}