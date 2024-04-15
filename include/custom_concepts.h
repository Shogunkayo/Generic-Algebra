#ifndef CUSTOMCONCEPTS_H
#define CUSTOMCONCEPTS_H

#include <concepts>
#include "data.h"
#include "complexnumber.h"

// Concept of acceptable types for Vector
template <typename T>
concept Arithmetic = std::is_arithmetic_v<T> 
	|| std::is_same_v<T, ComplexNumber<int, int>>
	|| std::is_same_v<T, ComplexNumber<double, double>>
	|| std::is_same_v<T, ComplexNumber<int, double>>
	|| std::is_same_v<T, ComplexNumber<double, int>>
    || std::is_same_v<T, struct Data> ;

// This concept is just to ensure that non-arithmetic types are not being passed to the matrix
template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

#endif // DEBUG
