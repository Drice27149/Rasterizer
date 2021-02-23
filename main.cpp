#include "Object.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"
#include "light.hpp"

int main(){
	Scene scene(700, 700);
	
	printf("Loading\n");
	Object obj("../models/bunny/bunny.obj");
	// Object obj1("../models/cornellbox/tallbox.obj");
	scene.add(&obj);
	// scene.add(&obj1);
	
	Light l0(Vector(0, 300, 300), Vector(2, 2, 2));
	scene.add(&l0);
	scene.Ia = Vector(20, 20, 20);
	
	Renderer renderer;
	renderer.origin = Vector(0, 0, 50.0);
	renderer.gDirection = Vector(0, 0, -1.0);
	renderer.uDirection = Vector(0, 1.0, 0);
	renderer.near = -0.1;
	renderer.far = -50.0;
	renderer.fov = 45;
	renderer.aspect = 1.0;
	printf("Rendering\n");
	renderer.render(&scene);
	
	printf("Saving\n");
	renderer.writeImage("../images/f.ppm");
	printf("Done\n");
	return 0;
}