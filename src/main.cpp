#include "vector.h"
#include <iostream>

int main (int argc, char *argv[]) {
	ColumnVector<int> x = {1, 2, 3, 4, 5};
	x.push_back(10);

	ColumnVector<int> y = x;
	
	x = x * 2;

	y = y + x;

	for (int i = 0; i < y.size(); i++) {
		std::cout << y[i] << std::endl;
	}

	return 0;
}
