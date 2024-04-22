#include "main.h"
#include <iostream>

int main (int argc, char *argv[]) {
    Vector v1 = {10, 20};
    Vector v2 = {30, 40};

    MultiVector mv1 = {1, 2.0};
    MultiVector mv2 = {10.5, 2.4};

    MultiVector mv3 = mv1 + Data(10.0);
    MultiVector mv4 = mv1 + mv2;

    MultiVector mv5;

    std::cout << mv3[0] << " " << mv3[1] << std::endl;
    std::cout << mv4[0] << " " << mv4[1] << std::endl;

    std::cout << dot(10, 20) << std::endl;
    std::cout << dot(v1, v2) << std::endl;
    std::cout << dot(mv1, mv2) << std::endl;

    return 0;
}
