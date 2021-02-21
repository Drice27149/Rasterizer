tag = -std=c++17 -Wno-everything

main: build/main.o build/Matrix.o build/Vector.o build/Loader.o build/Triangle.o build/Scene.o build/Object.o build/Light.o build/Renderer.o
	g++ $^ -o $@ $(tag)
	
build/main.o: main.cpp
	g++ -c $< -o $@ $(tag)
	
build/Matrix.o: Matrix.cpp Matrix.hpp
	g++ -c $< -o $@ $(tag)
	
build/Vector.o: Vector.cpp Vector.hpp
	g++ -c $< -o $@ $(tag)
	
build/Loader.o: Loader.cpp Loader.hpp
	g++ -c $< -o $@ $(tag)
	
build/Triangle.o: Triangle.cpp Triangle.hpp
	g++ -c $< -o $@ $(tag)
	
build/Scene.o: Scene.cpp Scene.hpp
	g++ -c $< -o $@ $(tag)
	
build/Object.o: Object.cpp Object.hpp
	g++ -c $< -o $@ $(tag)
	
build/Light.o: Light.cpp Light.hpp
	g++ -c $< -o $@ $(tag)
	
build/Renderer.o: Renderer.cpp Renderer.hpp
	g++ -c $< -o $@ $(tag)
	
clean: 
	rm -f build/*.o