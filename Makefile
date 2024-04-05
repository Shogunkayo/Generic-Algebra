build:
	rm -rf ./bin
	mkdir bin
	g++ -Wall -std=c++20 -I./include ./src/main.cpp -o ./bin/ga
	chmod +x ./bin/ga

run:
	./bin/ga

clean:
	rm -rf ./bin
