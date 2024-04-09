#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include <stdexcept>
#include <type_traits>
#include <concepts>
#include <initializer_list>
#include <iostream>

template <typename T, int rows = 0, int cols = 0>
class Matrix
{
public:
    VectorContainer <VectorContainer<T>*>* matrix;
    int no_rows;
    int no_cols;

    Matrix();
    Matrix(std::initializer_list<T> init);
    ~Matrix();

    void displayMatrix();
};

template <typename T, int rows, int cols>
Matrix<T, rows, cols>::Matrix()
{
    matrix = new VectorContainer <VectorContainer<T>*>();
    this->no_rows = rows;
    this->no_cols = cols;

    int curr_rows = rows;

    while(curr_rows != 0)
    {
        VectorContainer <T>* temp = new VectorContainer <T>();

        for(int i = 0; i < cols; i++)
        {
            temp->push_back(0);
        }

        matrix->push_back(temp);

        curr_rows--;
    }
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols>::Matrix(std::initializer_list<T> init)
{
    matrix = new VectorContainer <VectorContainer<T>*>();
    this->no_rows = rows;
    this->no_cols = cols;

    int curr_rows = rows;

    auto first = init.begin();
    auto last = init.end();

    while(curr_rows != 0 && first != last)
    {
        VectorContainer <T>* temp = new VectorContainer <T>();

        for(int i = 0; i < cols; i++, (void)++first)
        {
            temp->push_back(*first);
        }

        matrix->push_back(temp);

        curr_rows--;
    }
}

template <typename T, int rows, int cols>
Matrix<T, rows, cols>::~Matrix()
{
    for(int i = 0; i < matrix->size(); i++)
        delete (*matrix)[i];

    delete matrix;
}

template <typename T, int rows, int cols>
void Matrix<T, rows, cols>::displayMatrix()
{
    for(int i = 0; i < this->no_rows; i++)
    {
        std::cout << std::endl;
        VectorContainer <T> currRow = *((*matrix)[i]);

        for(int j = 0; j < this->no_cols; j++)
            std::cout << currRow[j] << " ";

        std::cout << std::endl;
    }
}

#endif