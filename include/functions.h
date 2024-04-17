#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "vector.h"
#include "multivector.h"
#include "matrix.h"
#include <type_traits>

namespace CHECK {
    struct No {}; 

    template<typename T, typename Arg>
    No operator* (const T&, const Arg&);

    template<typename T, typename Arg = T>
    struct MultiplicationExists {
        enum { value = !std::is_same<decltype(std::declval<T>() * std::declval<Arg>()), No>::value };
    };  
}

// base function for dot product, returns a * b
template <typename T, typename U>
typename std::enable_if<CHECK::MultiplicationExists<T, U>::value, T>::type
dot(const T& a, const U& b) {
    return a * b; 
}

/*
// calculate dot product of two Vectors
template <typename T, typename U>
auto dot(const Vector<T>& v1, const Vector<U>& v2) {
	if (v1.no_elements != v2.no_elements) {
		throw std::invalid_argument("Vectors should have equal number of elements");
	}
    
    // if both Vectors are of type int, return type will be int
    // else return type will be double
	using ReturnType = std::conditional_t<std::is_same_v<T, int> && std::is_same_v<U, int>, int, double>;
	ReturnType result = 0;
	for (int i = 0; i < v1.no_elements; i++) {
		result += v1.arr[i] * v2.arr[i];
	}

	return result;
}
*/

/*
// calculate the dot product of two MultiVectors
template <>
double dot(MultiVector mv1, MultiVector mv2) {
    if (mv1.vector.size() != mv2.vector.size()) {
		throw std::invalid_argument("MultiVectors should have equal number of elements");
	}
    
    Data result(0.0);
    for (int i = 0; i < mv1.vector.size(); i++) {
        result += mv1.vector[i] * mv2.vector[i];
    }

    return result.value.d_val;
}
*/

#endif // !DEBUG
