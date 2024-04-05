#include "vector.h"
#include <iostream>

int main (int argc, char *argv[]) {
	Vector<int> x = {1, 2};
	Vector<float> y = {1.5, 2.5};

	std::cout << dot(x, y) << std::endl;
	std::cout << euclidean_distance(x, x) << std::endl;

	const int a = 10;

	x.push_back(a);
	x.square();

	for (int i = 0; i < x.size(); i++) {
		std::cout << x[i] << std::endl;
	}

	return 0;
}
