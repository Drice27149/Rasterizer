#include "Object.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"
#include "light.hpp"
#include "Texture.hpp"

int main(){
	Scene scene(700, 700);
	
	printf("Loading\n");
	Object obj("../models/spot/spot_triangulated.obj");
	// Object obj1("../models/cornellbox/tallbox.obj");
	scene.add(&obj);
	// scene.add(&obj1);
	
	Light l0(Vector(0, 300, -300), Vector(0.7, 0.7, 0.7));
	scene.add(&l0);
	scene.Ia = Vector(0.1, 0.1, 0.1);
	
	Renderer renderer;
	renderer.origin = Vector(-2, 0, -3.5);
	renderer.gDirection = Vector(0.45, 0, 1.0);
	renderer.uDirection = Vector(0, 1.0, 0);
	renderer.near = -0.1;
	renderer.far = -50.0;
	renderer.fov = 45;
	renderer.aspect = 1.0;
	Texture texture("../models/spot/spot_texture.png");
	renderer.texture = &texture;
	printf("Rendering\n");
	renderer.render(&scene);
	
	printf("Saving\n");
	renderer.writeImage("../images/h.ppm");
	printf("Done\n");
	return 0;
}