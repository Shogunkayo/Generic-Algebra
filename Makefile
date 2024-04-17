build:
	rm -rf ./bin
	mkdir bin
	g++ -Wall -std=c++20 -I./include ./src/main.cpp -o ./bin/ga -fopenmp
	chmod +x ./bin/ga
	
matrix_demo:
	rm -rf ./bin
	mkdir bin
	g++ -Wall -std=c++20 -I./include ./src/matrix.cpp -o ./bin/matrix_demo -fopenmp
	chmod +x ./bin/matrix_demo
	./bin/matrix_demo

vector_demo:
	rm -rf ./bin
	mkdir bin
	g++ -Wall -std=c++20 -I./include ./src/vector.cpp -o ./bin/vector_demo -fopenmp
	chmod +x ./bin/vector_demo
	./bin/vector_demo

run:
	./bin/ga

clean:
	rm -rf ./bin
