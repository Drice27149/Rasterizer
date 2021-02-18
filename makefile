tag = -std=c++17 -Wno-everything

main: main.o Vector.o Matrix.o Loader.o Triangle.o Scene.o Object.o Light.o Renderer.o
	g++ $^ -o $@ $(tag)
	
main.o: main.cpp
	g++ -c $< -o $@ $(tag)
	
Matrix.o: Matrix.cpp Matrix.hpp
	g++ -c $< -o $@ $(tag)
	
Vector.o: Vector.cpp Vector.hpp
	g++ -c $< -o $@ $(tag)
	
Loader.o: Loader.cpp Loader.hpp
	g++ -c $< -o $@ $(tag)
	
Triangle.o: Triangle.cpp Triangle.hpp
	g++ -c $< -o $@ $(tag)
	
Scene.o: Scene.cpp Scene.hpp
	g++ -c $< -o $@ $(tag)
	
Object.o: Object.cpp Object.hpp
	g++ -c $< -o $@ $(tag)
	
Light.o: Light.cpp Light.hpp
	g++ -c $< -o $@ $(tag)
	
Renderer.o: Renderer.cpp Renderer.hpp
	g++ -c $< -o $@ $(tag)
	
clean: 
	rm -f *.o