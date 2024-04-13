#include "vector.h"
#include "matrix.h"
#include <iostream>
#include <ostream>

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

    // Matrix <int, 2, 2> x({1, 2, 1, 2});
	// Matrix <int, 2, 2> y({2, 1, 2, 1});

	// Matrix <int, 2, 3> b{{2, 2, 2, 2, 2, 2}};
	// Matrix <int, 3, 2> a({1, 1, 1, 1, 1, 1});

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

	// Matrix <int, 2, 2> c;
	// c = multiply<int, 2, 2, 2, 2>(x, y);
	// c.displayMatrix();

	// std::cout << std::endl;

	// Matrix <int, 3, 3> d = multiply<int, 3, 2, 2, 3>(a, b);
	// d.displayMatrix();

	// std::cout << std::endl;

	// x = multiply<int, 2, 2, 2, 2>(x, y) + 2;
	// x.displayMatrix();
   
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
