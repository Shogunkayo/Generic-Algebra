#ifndef DATA_H
#define DATA_H

#include <initializer_list>
#include <stdexcept>
#include <type_traits>
#include <concepts>
#include <utility>
#include "myvector.h"

template <typename T, typename U>
class ComplexNumber
{
private:
    T real;
    U imaginary;

public:
	ComplexNumber();
    ComplexNumber(T real, U imaginary);
    T getReal();
    U getImaginary();
    
    ComplexNumber<T, U> operator+(ComplexNumber<T, U> const& obj)
    {
        ComplexNumber<T, U> res;
        res.real = this->real + obj.real;
        res.imaginary = this->imaginary + obj.imaginary;
        return res;
    }
    
    ComplexNumber<T, U> operator-(ComplexNumber<T, U> const& obj)
    {
        ComplexNumber<T, U> res;
        res.real = this->real - obj.real;
        res.imaginary = this->imaginary - obj.imaginary;
        return res;
    }
};

template <typename T, typename U>
ComplexNumber<T, U>::ComplexNumber()
{
    if constexpr (!std::is_arithmetic_v<T> || !std::is_arithmetic_v<U>) 
	{
		throw std::invalid_argument( "Non-arithmetic arguments passed" );
	}
	
	this->real = 0;
	this->imaginary = 0;
}

template <typename T, typename U>
ComplexNumber<T, U>::ComplexNumber(T real, U imaginary)
{
    if constexpr (!std::is_arithmetic_v<T> || !std::is_arithmetic_v<U>) 
	{
		throw std::invalid_argument( "Non-arithmetic arguments passed" );
	}

    this->real = real;
    this->imaginary = imaginary;
}

template <typename T, typename U>
T ComplexNumber<T, U>::getReal()
{
    return this->real;
}

template <typename T, typename U>
U ComplexNumber<T, U>::getImaginary()
{
    return this->imaginary;
}

//---------------------------------------------------------------------------------
template <typename T>
concept Arithmetic = std::is_arithmetic_v<T> 
	|| std::is_same_v<T, ComplexNumber<int, int>>
	|| std::is_same_v<T, ComplexNumber<double, double>>
	|| std::is_same_v<T, ComplexNumber<int, double>>
	|| std::is_same_v<T, ComplexNumber<double, int>>;

template <Arithmetic T>
class ColumnVector : public Vector<T> {
	public:
		int dim_l;
		const int dim_r;
	
		ColumnVector() : dim_l(0), dim_r(1) {}
		ColumnVector(std::initializer_list<T> init) : Vector<T>(init), dim_l(init.size()), dim_r(1) {}
		ColumnVector(ColumnVector& obj) : dim_r(1) {
			this->capacity = obj.capacity;
			this->no_elements = obj.no_elements;
			this->dim_l = obj.no_elements;
			this->arr = new T[this->capacity];

			for (int i = 0; i < this->no_elements; i++) {
				this->arr[i] = obj.arr[i];
			}
		}
		ColumnVector& operator= (ColumnVector&& other) noexcept {
			if (this != &other) {
				if constexpr (std::is_class<T>::value) {
					for (int i = 0; i < this->no_elements; i++) {
						this->arr[i].~T();
					}
				}
				delete[] this->arr;

				this->no_elements = other.no_elements;
				this->arr = other.arr;
				this->capacity = other.capacity;

				other.no_elements = 0;
				other.capacity = 1;
				other.arr = nullptr;
			}

			return (*this);
		}
		
		void push_back(T key);
		void insert(T key, int index);
		void pop();

		Vector<int> get_dimensions();

		ColumnVector<T> operator+ (const T obj);
		ColumnVector<T> operator- (const T obj);
		ColumnVector<T> operator* (const T obj);
		ColumnVector<T> operator/ (const T obj);
		ColumnVector<T> operator+ (const ColumnVector<T> obj);
		ColumnVector<T> operator- (const ColumnVector<T> obj);
}; 

template <Arithmetic T>
void ColumnVector<T>::push_back(T key) {
	Vector<T>::push_back(key);
	dim_l++;
}

template <Arithmetic T>
void ColumnVector<T>::insert(T key, int index) {
	Vector<T>::insert(key, index);
	dim_l++;
}

template <Arithmetic T>
void ColumnVector<T>::pop() {
	Vector<T>::pop();
	dim_l--;
}

template <Arithmetic T>
Vector<int> ColumnVector<T>::get_dimensions() {
	return Vector<int> (dim_l, dim_r);
}

template <Arithmetic T>
ColumnVector<T> ColumnVector<T>::operator+ (const T obj) {
	ColumnVector<T> result;
	result.capacity = this->capacity;
	result.no_elements = this->no_elements;
	result.dim_l = this->dim_l;
	result.arr = new T[result.capacity];

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] = this->arr[i] + obj;
	}

	return result;
}

template <Arithmetic T>
ColumnVector<T> ColumnVector<T>::operator- (const T obj) {
	ColumnVector<T> result;
	result.capacity = this->capacity;
	result.no_elements = this->no_elements;
	result.dim_l = this->dim_l;
	result.arr = new T[result.capacity];

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] = this->arr[i] - obj;
	}

	return result;
}

template <Arithmetic T>
ColumnVector<T> ColumnVector<T>::operator* (const T obj) {
	ColumnVector<T> result;
	result.capacity = this->capacity;
	result.no_elements = this->no_elements;
	result.dim_l = this->dim_l;
	result.arr = new T[result.capacity];

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] = this->arr[i] * obj;
	}

	return result;
}

template <Arithmetic T>
ColumnVector<T> ColumnVector<T>::operator/ (const T obj) {
	ColumnVector<T> result;
	result.capacity = this->capacity;
	result.no_elements = this->no_elements;
	result.dim_l = this->dim_l;
	result.arr = new T[result.capacity];

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] = this->arr[i] / obj;
	}

	return result;
}

template <Arithmetic T>
ColumnVector<T> ColumnVector<T>::operator+ (const ColumnVector<T> obj) {
	if (this->dim_l != obj.dim_l) {
		throw std::invalid_argument("Dimensions do not match");
	}

	ColumnVector<T> result;
	result.capacity = this->capacity;
	result.no_elements = this->no_elements;
	result.dim_l = this->dim_l;
	result.arr = new T[result.capacity];

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] = this->arr[i] + obj.arr[i];
	}

	return result;
}

template <Arithmetic T>
ColumnVector<T> ColumnVector<T>::operator- (const ColumnVector<T> obj) {
	if (this->dim_l != obj.dim_l) {
		throw std::invalid_argument("Dimensions do not match");
	}

	ColumnVector<T> result;
	result.capacity = this->capacity;
	result.no_elements = this->no_elements;
	result.dim_l = this->dim_l;
	result.arr = new T[result.capacity];

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] = this->arr[i] - obj.arr[i];
	}

	return result;
}
#endif
