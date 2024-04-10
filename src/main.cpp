#include "vector.h"
#include "matrix.h"
#include <iostream>

int main (int argc, char *argv[]) {
	// Vector<int> x = {1, 2};
	// Vector<float> y = {1.5, 2.5};

	// std::cout << dot(x, y) << std::endl;
	// std::cout << euclidean_distance(x, x) << std::endl;

	// const int a = 10;

	// x.push_back(a);
	// x.square();

	// for (int i = 0; i < x.size(); i++) {
	// 	std::cout << x[i] << std::endl;
	// }

	// Matrix <int> x;
	// Matrix <double, 2, 3> y({1.1, 1.2, 1.3, 2.1, 2.2, 2.3});

	// x.displayMatrix();
	// y.displayMatrix();

	// std::cout << std::endl << std::endl;

	// std::cout << y[0][2] << std::endl;
	// std::cout << y[1][1] << std::endl;

	// y[0][0] = 5;
	// y.displayMatrix();

	Matrix <int, 2, 2> x({1, 2, 1, 2});
	Matrix <int, 2, 2> y({2, 1, 2, 1});

	Matrix <int, 2, 2> z{{2, 2, 2, 2}};
	// Matrix <int, 2, 2> z = x + 1;
	// z.displayMatrix();

	// y.displayMatrix();

	// y = x;
	// std::cout << std::endl;

	x.displayMatrix();

	x = z / 2;
	std::cout << std::endl;

	x.displayMatrix();

	return 0;
}
