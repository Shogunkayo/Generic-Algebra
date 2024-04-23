#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>
#include <iostream>
#include <variant>
#include "vectorcontainer.h"
#include "custom_concepts.h"

// forward declaration of Vector class
template <Arithmetic T>
class Vector;

// forward declartion of friend function to find the euclidean
// distance between two Vectors
template <typename T>
double euclidean_distance(const Vector<T>& v1, const Vector<T>& v2);

template <Arithmetic T>
class Vector : public VectorContainer<T> {
	public:
        // in the matrix dimension notation AxB,
        // dim_l = A
        // dim_r = B
		size_t dim_l;
		size_t dim_r;
        // flag to indicate whether to use dim_l (column vector)
        // or dim_r (row vector) for operations
		int isColumn;
	    
        // All constructors create a column vector
        // Default constructor
		Vector() : dim_l(0), dim_r(1), isColumn(1) {}

        // Constructor for initializer_list
		Vector(std::initializer_list<T> init) : VectorContainer<T>(init), dim_l(init.size()), dim_r(1), isColumn(1) {}

        // Copy constructor
		Vector(Vector& obj) {
			this->capacity = obj.capacity;
			this->no_elements = obj.no_elements;
			this->dim_l = obj.dim_l;
			this->dim_r = obj.dim_r;
			this->isColumn = obj.isColumn;
			this->arr = new T[this->capacity];

			for (int i = 0; i < this->no_elements; i++) {
				this->arr[i] = obj.arr[i];
			}
		}

        // Move assignment
		Vector& operator= (Vector&& other) noexcept {
			if (this != &other) {
				delete[] this->arr;

				this->no_elements = other.no_elements;
				this->arr = other.arr;
				this->capacity = other.capacity;
				this->dim_r = other.dim_r;
				this->dim_l = other.dim_l;
				this->isColumn = other.isColumn;

				other.dim_l = 0;
				other.dim_r = 1;
				other.no_elements = 0;
				other.capacity = 1;
				other.arr = nullptr;
				other.isColumn = 1;
			}

			return (*this);
		}
        
        // handle changing dimensions while inserting
        // and deleting element
		void push_back(const T key);
		void insert(const T key, const int index);
		void pop();

        // return the dimensions (dim_l, dim_r) as a Vector<int>
		Vector<int> get_dimensions();

        // scalar arithmetic operator overloads
		Vector<T> operator+ (const T obj);
		Vector<T> operator- (const T obj);
		Vector<T> operator* (const T obj);
		Vector<T> operator/ (const T obj);

        // vector arithmetic operator overloads
		Vector<T> operator+ (Vector<T> obj);
		Vector<T> operator- (Vector<T> obj);

        // return the magnitude of Vector
		double magnitude();
        
        // interchange dim_l and dim_r, isColumn
        // used for dimension checking with Matrix operations
		void transpose();

        // function to apply a function to each element of Vector
        // supports lambda templates
		template <typename Func>
        // Func&& accepts both lvalue and rvalue references
		void map(Func&& func) {
			for (int i = 0; i < this->no_elements; i++) {
				this->arr[i] = func(this->arr[i]);
			}
		}

        // example lambda templates to demonstrate map
		void square();
        void pow(const int& exponent);

        // friend function to find euclidean distance between two Vectors
		friend double euclidean_distance<>(const Vector<T>& v1, const Vector<T>& v2);
}; 

template <Arithmetic T>
void Vector<T>::push_back(const T key) {
	VectorContainer<T>::push_back(key);
	dim_r += !isColumn;
	dim_l += isColumn;
}

template <Arithmetic T>
void Vector<T>::insert(const T key, const int index) {
	VectorContainer<T>::insert(key, index);
	dim_r += !isColumn;
	dim_l += isColumn;
}

template <Arithmetic T>
void Vector<T>::pop() {
	VectorContainer<T>::pop();
	dim_r -= !isColumn;
	dim_l -= isColumn;
}

template <Arithmetic T>
Vector<int> Vector<T>::get_dimensions() {
	return Vector<int> (dim_l, dim_r);
}

template <Arithmetic T>
Vector<T> Vector<T>::operator+(const T obj) {
	Vector<T> result = (*this);

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] += obj;
	}

	return result;
}

template <Arithmetic T>
Vector<T> Vector<T>::operator-(const T obj) {
	Vector<T> result = (*this);

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] -= obj;
	}

	return result;
}

template <Arithmetic T>
Vector<T> Vector<T>::operator*(const T obj) {
	Vector<T> result = (*this);

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] *= obj;
	}

	return result;
}

template <Arithmetic T>
Vector<T> Vector<T>::operator/(const T obj) {
	Vector<T> result = (*this);

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] /= obj;
	}

	return result;
}

template <Arithmetic T>
Vector<T> Vector<T>::operator+(const Vector<T> obj) {
	if (this->no_elements != obj.no_elements) {
		throw std::invalid_argument("Vectors should have equal number of elements");
	}

	Vector<T> result = (*this);

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] += obj.arr[i];
	}

	return result;
}

template <Arithmetic T>
Vector<T> Vector<T>::operator-(const Vector<T> obj) {
	if (this->no_elements != obj.no_elements) {
		throw std::invalid_argument("Vectors should have equal number of elements");
	}

	Vector<T> result = (*this);

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] -= obj.arr[i];
	}

	return result;
}

template <Arithmetic T>
double Vector<T>::magnitude() {
	double result = 0;
	for (int i = 0; i < this->no_elements; i++) {
		result += this->arr[i] * this->arr[i];
	}

	return sqrt(result);
}

template <Arithmetic T>
void Vector<T>::transpose() {
	isColumn = !isColumn;
	dim_r = dim_r ^ dim_l;
	dim_l = dim_r ^ dim_l;
	dim_r = dim_r ^ dim_l;
}

template <Arithmetic T>
void Vector<T>::square() {
    // lambda template to square each element
	this->map([] <Arithmetic U> (U a) { return a * a; });
}

template <Arithmetic T>
void Vector<T>::pow(const int& exponent) {
    // lambda template to raise each element to exponent
    this->map([&] <Arithmetic U> (U a) { return std::pow(a, exponent); }); 
}

template <typename T>
double euclidean_distance(const Vector<T>& v1, const Vector<T>& v2) {
	if (v1.no_elements != v2.no_elements) {
		throw std::invalid_argument("Vectors should have equal number of elements");
	}

	double result = 0;
	for (int i = 0; i < v1.no_elements; i++) {
		result += (v1.arr[i] - v2.arr[i]) * (v1.arr[i] - v2.arr[i]);
	}

	return sqrt(result);
}

#endif
