#include "Object.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"
#include "light.hpp"

int main(){
	Scene scene(500, 500);
	
	Object shortbox("..models/cornellbox/shortbox.obj");
	scene.add(&shortbox);
	
	Light light(Vector(0.0f, 0.0f, 0.0f), Vector(0.5f, 0.5f, 0.5f));
	scene.add(&light);
	
	Renderer renderer;
	renderer.render(&scene);
	return 0;
}