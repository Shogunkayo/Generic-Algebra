build:
	rm -rf ./bin
	mkdir bin
	g++ -Wall -I./include ./src/main.cpp -o ./bin/ga
	chmod +x ./bin/ga

clean:
	rm -rf ./bin
