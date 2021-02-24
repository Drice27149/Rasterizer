#pragma once

#include "Scene.hpp"
#include "Triangle.hpp"
#include "Texture.hpp"

class Renderer {
public:
	void render(Scene* scene);
	void renderTriangle(Vector* vs, Triangle* t);
	void writeImage(const char* filename);
public:
	// eye position, gaze & up direction
	Vector origin, gDirection, uDirection;
	// field of view, aspect ratio
	// tan(fov * 0.5) = t / n
	// aspect ratio = r / t
	float fov, aspect;
	float near, far;
	Texture* texture;
private:
	std::vector<Vector> frameBuffer;
	std::vector<float> depthBuffer;
	Scene* scene;
	int width;
	int height;
};