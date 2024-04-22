#ifndef MATRIX_H
#define MATRIX_H

#include "vectorcontainer.h"
#include "custom_concepts.h"
#include <stdexcept>
#include <type_traits>
#include <concepts>
#include <initializer_list>
#include <iostream>
#include <typeinfo>
#include <cmath>
#include <omp.h>

/*
Note : For now, we are only handling 1D and 2D matrices.
*/
template <Numeric T, int rows = 0, int cols = 0>
class Matrix
{
public:
    VectorContainer <VectorContainer<T>*>* matrix;   // Our matrix is a (custom) vector of vectors. The vectors within the matrix represent rows.
    int no_rows;
    int no_cols;

    Matrix();                                        // Constructor to create a zero-matrix
    Matrix(std::initializer_list<T> init);           // Constructor to create a matrix from a lit of supplied elements
    ~Matrix();                                       // The destructor clears the memory alloted to data member matrix

    VectorContainer<T>& operator [](const int row);                      // Overload of [] operator to access matrix elements
    
    Matrix<T, rows, cols>& operator =(Matrix<T, rows, cols>& other);     // Overload of assignment operator
    Matrix<T, rows, cols>& operator =(Matrix<T, rows, cols> other);      // Another overload of the same assignment operator (just a quick bug fix)

    Matrix<T, rows, cols> operator+(T obj);          // Overload of + operator to add a scalar to a matrix
    Matrix<T, rows, cols> operator-(T obj);          // Overload of - operator to subtract a scalar from a matrix
    Matrix<T, rows, cols> operator*(T obj);          // Overload of * operator to multiply a matrix by a scalar
    Matrix<T, rows, cols> operator/(T obj);          // Overload of / operator to divide a matrix by a scalar

    Matrix<T, rows, cols> operator+(Matrix<T, rows, cols>& m);          // Overload of + operator to add two matrices
    Matrix<T, rows, cols> operator-(Matrix<T, rows, cols>& m);          // Overload of + operator to subtract one matrix from another

    template <typename U, int rows1, int cols1, int rows2, int cols2>
    friend Matrix<U, rows1, cols2> multiply(Matrix<U, rows1, cols1>& m1, Matrix<U, rows2, cols2>& m2);    // Friend function to handle multiplication of two matrices

    void displayMatrix();           // Helper function to print the matrix to stdout. Used for debugging purposes.
};

template <Numeric T, int rows, int cols>
Matrix<T, rows, cols>::Matrix()
{
    if(rows < 0 || cols < 0)
        throw std::invalid_argument("Matrix dimensions can't be negative");

    matrix = new VectorContainer <VectorContainer<T>*>();

    this->no_rows = rows;
    this->no_cols = cols;

    int curr_rows = rows;

    while(curr_rows != 0)
    {
        VectorContainer <T>* temp = new VectorContainer <T>();

        #pragma omp for
        for(int i = 0; i < cols; i++)
        {
            temp->push_back(0);
        }

        matrix->push_back(temp);

        curr_rows--;
    }
}

template <Numeric T, int rows, int cols>
Matrix<T, rows, cols>::Matrix(std::initializer_list<T> init)
{
    if(rows < 0 || cols < 0)
        throw std::invalid_argument("Matrix dimensions can't be negative");

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

template <Numeric T, int rows, int cols>
Matrix<T, rows, cols>::~Matrix()
{
    #pragma omp for
    for(int i = 0; i < matrix->size(); i++)
        delete (*matrix)[i];

    delete matrix;
}

/*
Note : Suppose we're accessing element a[2][3] of a matrix.
The second [] overload is part of the VectorContainer implementation.
We are overloading only the first [] to return the required row, which is indexed by the second [].
*/
template <Numeric T, int rows, int cols>
VectorContainer<T>& Matrix<T, rows, cols>::operator [](const int row)
{
    return *((*matrix)[row]);
} 

template <Numeric T, int rows, int cols>
Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator =(Matrix<T, rows, cols>& other)
{
    #pragma omp for
    for(int i = 0; i < this->no_rows; i++)
    {
        *((*matrix)[i]) = other[i];
    }

    return (*this);
} 

template <Numeric T, int rows, int cols>
Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator =(Matrix<T, rows, cols> other)
{
    #pragma omp for
    for(int i = 0; i < this->no_rows; i++)
    {
        *((*matrix)[i]) = other[i];
    }

    return (*this);
} 

template <Numeric T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator +(T obj)
{
    Matrix <T, rows, cols> res;

    #pragma omp parallel shared(res)
    for(int i = 0; i < this->no_rows; i++)
    {
        VectorContainer <T> currRow = *((*matrix)[i]);

        #pragma omp parallel shared(res)
        for(int j = 0; j < this->no_cols; j++)
        {
            res[i][j] = currRow[j] + obj;
        }
    }

    return res;
}

template <Numeric T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator -(T obj)
{
    Matrix <T, rows, cols> res;

    #pragma omp parallel shared(res)
    for(int i = 0; i < this->no_rows; i++)
    {
        VectorContainer <T> currRow = *((*matrix)[i]);

        #pragma omp parallel shared(res)
        for(int j = 0; j < this->no_cols; j++)
        {
            res[i][j] = currRow[j] - obj;
        }
    }

    return res;
}

template <Numeric T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator *(T obj)
{
    Matrix <T, rows, cols> res;

    #pragma omp parallel shared(res)
    for(int i = 0; i < this->no_rows; i++)
    {
        VectorContainer <T> currRow = *((*matrix)[i]);

        #pragma omp parallel shared(res)
        for(int j = 0; j < this->no_cols; j++)
        {
            res[i][j] = currRow[j] * obj;
        }
    }

    return res;
}

template <Numeric T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator /(T obj)
{
    Matrix <T, rows, cols> res;

    #pragma omp parallel shared(res)
    for(int i = 0; i < this->no_rows; i++)
    {
        VectorContainer <T> currRow = *((*matrix)[i]);

        #pragma omp parallel shared(res)
        for(int j = 0; j < this->no_cols; j++)
        {
            res[i][j] = currRow[j] / obj;
        }
    }

    return res;
}

template <Numeric T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator +(Matrix<T, rows, cols>& m)
{  
    Matrix <T, rows, cols> res;

    #pragma omp parallel shared(res)
    for(int i = 0; i < this->no_rows; i++)
    {
        VectorContainer <T> currRow = *((*matrix)[i]);

        #pragma omp parallel shared(res)
        for(int j = 0; j < this->no_cols; j++)
        {
            res[i][j] = currRow[j] + m[i][j];
        }
    }

    return res;
}

template <Numeric T, int rows, int cols>
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator -(Matrix<T, rows, cols>& m)
{
    Matrix <T, rows, cols> res;

    #pragma omp parallel shared(res)
    for(int i = 0; i < this->no_rows; i++)
    {
        VectorContainer <T> currRow = *((*matrix)[i]);

        #pragma omp parallel shared(res)
        for(int j = 0; j < this->no_cols; j++)
        {
            res[i][j] = currRow[j] - m[i][j];
        }
    }

    return res;
}

/*
Note : Operator overloading was not used for matrix-matrix multiplication since it'd become quite messy 
considering the current implementation. Hence, a friend function was created instead to handle it.
*/
template <Numeric U, int rows1, int cols1, int rows2, int cols2>
Matrix<U, rows1, cols2> multiply(Matrix<U, rows1, cols1>& m1, Matrix<U, rows2, cols2>& m2)
{
    if(cols1 != rows2)
        throw std::invalid_argument("Incorrect dimensions for matrix multiplication");

    Matrix <U, rows1, cols2> res;

    for(int i = 0; i < rows1; i++)
    {
        for(int j = 0; j < cols2; j++)
        {
            for(int k = 0; k < rows2; k++)
            {
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return res;
}

/*
The following shows partial template specialization of the multiply function.
We need one less for loop when we have an mxn matrix and an nx1 matrix/vector.
*/
template <Numeric U, int rows1, int cols1, int rows2>
Matrix<U, rows1, 1> multiply(Matrix<U, rows1, cols1>& m1, Matrix<U, rows2, 1>& m2)
{
    if(cols1 != rows2)
        throw std::invalid_argument("Incorrect dimensions for matrix multiplication");

    Matrix <U, rows1, 1> res;

    for(int i = 0; i < rows1; i++)
    {
        for(int k = 0; k < rows2; k++)
        {
            res[i][0] += m1[i][k] * m2[k][0];
        }
    }

    std::cout << "specialization" << std::endl;

    return res;
}

template <typename x, typename T, typename U, int rows1 = 1, int cols1 = 0, int rows2 = 1, int cols2 = 0>
Matrix<x, rows1, cols2> multiply2(T& m1, U& m2)
{
    Matrix <x, rows1, cols2> res;

    res[0][0] = m1 * m2;

    return res;
}

template <typename x, int rows1, int cols1, int rows2, int cols2>
Matrix<x, rows1, cols2> multiply2(Matrix<x, rows1, cols1>& m1, Matrix<x, rows2, cols2>& m2)
{
    Matrix <x, rows1, cols2> res;

    for(int i = 0; i < rows1; i++)
    {
        for(int j = 0; j < cols2; j++)
        {
            for(int k = 0; k < rows2; k++)
            {
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    std::cout << "specialization 1" << std::endl;

    return res;
}

template <typename x, int rows1, int cols1, int rows2, int cols2 = 1>
Matrix<x, rows1, cols2> multiply2(Matrix<x, rows1, cols1>& m1, Vector<x>& m2)
{
    Matrix <x, rows1, cols2> res;

    for(int i = 0; i < rows1; i++)
    {
        for(int k = 0; k < rows2; k++)
        {
            res[i][0] += m1[i][k] * m2[k];
        }
    }

    std::cout << "specialization 2" << std::endl;

    return res;
}

template <typename x, int rows1, int cols2>
Matrix<x, rows1, cols2> multiply2(Vector<x>& m1, Vector<x>& m2)
{
    Matrix <x, rows1, cols2> res;

    for(int i = 0; i < rows1; i++)
    {
        for(int j = 0; j < cols2; j++)
        {
            res[i][j] += m1[i] * m2[j];
        }
    }

    std::cout << "specialization 3" << std::endl;

    return res;
}

template <Numeric T, int rows, int cols>
void Matrix<T, rows, cols>::displayMatrix()
{
    for(int i = 0; i < this->no_rows; i++)
    {
        std::cout << std::endl;
        VectorContainer <T> currRow = *((*matrix)[i]);

        #pragma omp for
        for(int j = 0; j < this->no_cols; j++)
            std::cout << currRow[j] << " ";

        std::cout << std::endl;
    }
}

// Returns transpose of input matrix
template <Numeric T, int rows, int cols>
Matrix<T, cols, rows> transpose(Matrix<T, rows, cols>& m)
{
    Matrix <T, cols, rows> res;

    #pragma omp for
    for(int i = 0; i < cols; i++)
        for(int j = 0; j < rows; j++)
            res[i][j] = m[j][i];

    return res;
}

// Helper function for the main determinant function
template <Numeric T, int rows, int cols>
double determinant_helper(Matrix<T, rows, cols>& m, int n)
{
    double det = 0;

    Matrix<T, rows, cols> submatrix;

    if (n == 2)
        return ((m[0][0] * m[1][1]) - (m[1][0] * m[0][1]));

    else 
    {
        for (int x = 0; x < n; x++) 
        {
            int subi = 0;

            for (int i = 1; i < n; i++) 
            {
                int subj = 0;

                for (int j = 0; j < n; j++) 
                {
                    if (j == x)
                        continue;
                    
                    submatrix[subi][subj] = m[i][j];
                    subj++;
                }
                subi++;
            }

            det = det + (pow(-1, x) * m[0][x] * determinant_helper(submatrix, n - 1));
        }
    }
    return det;
}

// Returns determinant of a matrix (only applicable to square matrices)
template <Numeric T, int rows, int cols>
double determinant(Matrix<T, rows, cols>& m)
{
    if(m.no_rows != m.no_cols)
        throw std::invalid_argument("Determinant can be found only for square matrices");

    double det = determinant_helper(m, rows);
    return det;
}

// Returns LU decomposition of input matrix (only applicable to square matrices)
template <Numeric T, int rows, int cols>
void luDecomposition(Matrix<T, rows, cols>& m)
{
    if(m.no_rows != m.no_cols)
        throw std::invalid_argument("LU decomposition can be found only for square matrices");

    VectorContainer <Matrix<T, rows, cols>> res;

    Matrix <T, rows, cols> upper;
    Matrix <T, rows, cols> lower;

    int n = rows;

    for(int i = 0; i < n; i++)
    {
        for(int k = i; k < n; k++)
        {
            double sum = 0;

            for(int j = 0; j < i; j++)
                sum += (lower[i][j] * upper[j][k]);

            upper[i][k] = m[i][k] - sum;
        }

        for(int k = i; k < n; k++)
        {
            if(i == k)
                lower[i][i] = 1;

            else
            {
                double sum = 0;

                for(int j = 0; j < i; j++)
                    sum += (lower[k][j] * upper[j][i]);

                lower[k][i] = (m[k][i] - sum) / upper[i][i];
            }
        }
    }

    lower.displayMatrix();
    std::cout << std::endl;

    upper.displayMatrix();
    std::cout << std::endl;
}

#endif
