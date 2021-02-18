#pragma once

#include "Scene.hpp"

class Renderer {
public:
	void render(Scene* scene);
public:
	// eye position, gaze & up direction
	Vector origin, gDirection, uDirection;
	// field of view, aspect radio
	float fov, aspectRadio;
};