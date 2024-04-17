#include "main.h"

#include <iostream>
#include <ostream>

int main (int argc, char *argv[]) 
{
    std::cout << std::endl;

    Matrix <int, 2, 2> z1({1, 2, 3, 4});

    std::cout << "z1 + 3 = " << std::endl;

    z1 = z1 + 3;
    z1.displayMatrix();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

	Matrix <int, 2, 2> a({1, 1, 1, 1});
    Matrix <int, 2, 2> b({2, 2, 2, 2});

    std::cout << "a + b = " << std::endl;

    Matrix <int, 2, 2> c = a + b;
    c.displayMatrix();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    Matrix <int, 3, 1> d({1, 1, 1});
    Matrix <int, 1, 3> e({3, 4, 5});

    std::cout << "c * d = " << std::endl;

    (multiply<int, 3, 1, 1, 3>(d, e)).displayMatrix();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    Matrix <int, 2, 3> f({1, 2, 3, 4, 5, 6});

    std::cout << "f = " << std::endl;
    f.displayMatrix();

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "f' = " << std::endl;
    (transpose(f)).displayMatrix();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    Matrix <double, 2, 2> g({1.1, 1.1, 2, 3});
    std::cout << "Det(g) = " << determinant(g) << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    Matrix <double, 3, 3> m({25, 5, 1, 64, 8, 1, 144, 12, 1});
    std::cout << "L and U matrices of m are : " << std::endl;

    std::cout << std::endl;

    luDecomposition(m);

	return 0;
}
