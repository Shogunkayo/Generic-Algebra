#include "vector.h"
#include "matrix.h"
#include <iostream>
#include <ostream>

int main (int argc, char *argv[]) 
{
	// Matrix <int, 3, 3> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
	// Matrix <int, 3, 3> b{{2, -1, -2, -4, 6, 3, -4, -2, 8}};
	// b.displayMatrix();

	// luDecomposition(b);

	// Matrix <int, 3, 3> x = transpose(a);
	// x.displayMatrix();

	// std::cout << std::endl;

    /*
	Matrix <int, 3, 4> b({1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3});
	b.displayMatrix();

	std::cout << std::endl;

	Matrix <int, 4, 3> c = transpose(b);
	c.displayMatrix();
    */

    /*
    MultiVector m1;
    m1.push_back(10);
    m1.push_back<float>(3.14);
    m1.push_back('a');


    MultiVector m2;
    m2.push_back(10);
    m2.push_back<float>(3.14);
    m2.push_back('a');

    MultiVector m3 = m1 - m2;

    m1.square();

    std::cout << m1[0] << std::endl;
    std::cout << m1[1] << std::endl;
    std::cout << m1[2] << std::endl;

    MultiVector m4;
    m4.push_back(10);
    m4.push_back(2.5);

    std::cout << dot(m4, m4) << std::endl;
    */

    MultiVector m10 = {10, 20, 30.5, 'A'};

    MultiVector m20 = m10;
    m20[3] += Data(5);

    std::cout << m10[3] << std::endl;
    std::cout << m20[3] << std::endl;

	return 0;
}
