#include "vector.h"
#include "matrix.h"
#include <iostream>

int main (int argc, char *argv[]) 
{
	// Matrix <int, 3, 3> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
	// Matrix <int, 3, 3> b{{2, -1, -2, -4, 6, 3, -4, -2, 8}};
	// b.displayMatrix();

	// luDecomposition(b);

	// Matrix <int, 3, 3> x = transpose(a);
	// x.displayMatrix();

	// std::cout << std::endl;

	Matrix <int, 3, 4> b({1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3});
	b.displayMatrix();

	std::cout << std::endl;

	Matrix <int, 4, 3> c = transpose(b);
	c.displayMatrix();

	return 0;
}
