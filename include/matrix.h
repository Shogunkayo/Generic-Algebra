#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include <stdexcept>
#include <type_traits>
#include <concepts>

template <typename T>
class Matrix
{
public:
    Vector <Vector<T>>* matrix;

    Matrix()
    {
        matrix = new Vector <Vector<T>>();
    }
};

#endif