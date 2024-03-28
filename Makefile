build:
	rm -rf ./bin
	mkdir bin
	g++ -Wall ./src/main.cpp -o ./bin/gla
	chmod +x ./bin/gla

clean:
	rm -rf ./bin
