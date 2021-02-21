#pragma once

#include "Scene.hpp"
#include "Triangle.hpp"

class Renderer {
public:
	void render(Scene* scene);
	void renderTriangle(Vector* vScreen, Triangle* t);
	void writeImage(const char* filename);
public:
	// eye position, gaze & up direction
	Vector origin, gDirection, uDirection;
	// field of view, aspect ratio
	// tan(fov * 0.5) = t / n
	// aspect ratio = r / t
	float fov, aspect;
	float near, far;
private:
	std::vector<Vector> frameBuffer;
	std::vector<float> depthBuffer;
	int width;
	int height;
};