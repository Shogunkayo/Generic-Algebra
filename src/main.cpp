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

	Matrix <int, 2, 2> x({1, 2, 1, 2});
	Matrix <int, 2, 2> y({2, 1, 2, 1});

	Matrix <int, 2, 3> b{{2, 2, 2, 2, 2, 2}};
	Matrix <int, 3, 2> a({1, 1, 1, 1, 1, 1});

	// Overloaded + for single integer
	// Matrix <int, 2, 2> c;
	// c = x + 1;
	// c.displayMatrix();
	// std::cout << std::endl;

	// x.displayMatrix();
	// x = x + 2;
	// std::cout << std::endl;
	// x.displayMatrix();

	// std::cout << std::endl;
	// Matrix <int, 2, 2> d = y * 3;
	// d.displayMatrix();


	// Overloaded + for 2 matrices
	// Matrix <int, 2, 2> c;
	// c = x + y;
	// c.displayMatrix();

	// std::cout << std::endl;

	// Matrix <int, 2, 2> d = x + y;
	// d.displayMatrix();

	// std::cout << std::endl;

	// y = x - y;
	// y.displayMatrix();

	Matrix <int, 2, 2> c;
	c = multiply<int, 2, 2, 2, 2>(x, y);
	c.displayMatrix();

	std::cout << std::endl;

	Matrix <int, 3, 3> d = multiply<int, 3, 2, 2, 3>(a, b);
	d.displayMatrix();

	std::cout << std::endl;

	x = multiply<int, 2, 2, 2, 2>(x, y) + 2;
	x.displayMatrix();

	return 0;
}
