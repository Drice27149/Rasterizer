#include "Object.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"
#include "light.hpp"

int main(){
	Scene scene(700, 700);
	
	Object obj("../models/simp/triangle.obj");
	printf("Loading\n");
	scene.add(&obj);
	
	Renderer renderer;
	renderer.origin = Vector(0, 0, 5.0);
	renderer.gDirection = Vector(0, 0, -1.0);
	renderer.uDirection = Vector(0, 1.0, 0);
	renderer.near = -0.1;
	renderer.far = -50.0;
	renderer.fov = 45;
	renderer.aspect = 1.0;
	printf("Rendering\n");
	renderer.render(&scene);
	
	printf("Saving\n");
	renderer.writeImage("../images/a.ppm");
	printf("Done\n");
	return 0;
}