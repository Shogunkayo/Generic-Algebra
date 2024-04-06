#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include <stdexcept>
#include <type_traits>
#include <concepts>
#include <initializer_list>

template <typename T>
class Matrix
{
public:
    Vector <Vector<T>> matrix;
    int no_rows;
    int no_cols;

    Matrix()
    {
        matrix = Vector <Vector<T>>();
        no_rows = 0;
        no_cols = 0;
    }

    Matrix(int rows, int cols)
    {
        matrix = Vector <Vector<T>>();
        this->no_rows = rows;
        this->no_cols = cols;

        while(rows != 0)
        {
            Vector <T> temp;

            for(int i = 0; i < cols; i++)
            {
                temp.push_back(0);
            }

            matrix.push_back(temp);

            rows--;
        }
    }

    Matrix(int rows, int cols, std::initializer_list<T> init)
    {
        
    }
};

#endif