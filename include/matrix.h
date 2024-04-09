#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include <stdexcept>
#include <type_traits>
#include <concepts>
#include <initializer_list>
#include <iostream>

template <typename T>
class Matrix
{
public:
    VectorContainer <VectorContainer<T>*>* matrix;
    int no_rows;
    int no_cols;

    Matrix()
    {
        matrix = new VectorContainer <VectorContainer<T>*>();
        no_rows = 0;
        no_cols = 0;
    }

    Matrix(int rows, int cols)
    {
        matrix = new VectorContainer <VectorContainer<T>*>();
        this->no_rows = rows;
        this->no_cols = cols;

        while(rows != 0)
        {
            VectorContainer <T>* temp = new VectorContainer <T>();

            for(int i = 0; i < cols; i++)
            {
                temp->push_back(0);
            }

            matrix->push_back(temp);

            rows--;
        }
    }

    ~Matrix()
    {
        for(int i = 0; i < matrix->size(); i++)
            delete (*matrix)[i];

        delete matrix;
    }

    void displayMatrix()
    {
        for(int i = 0; i < this->no_rows; i++)
        {
            std::cout << std::endl;
            VectorContainer <int> currRow = *((*matrix)[i]);

            for(int j = 0; j < this->no_cols; j++)
                std::cout << currRow[j] << " ";

            std::cout << std::endl;
        }
    }

    // Matrix(int rows, int cols, std::initializer_list<T> init)
    // {
        
    // }
};

#endif