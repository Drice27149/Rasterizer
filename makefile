tag = -std=c++17 -Wno-everything

main: main.o Vector.o Matrix.o Loader.o Triangle.o
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
	
clean: 
	rm -f *.o