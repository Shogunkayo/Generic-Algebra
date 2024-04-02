/*
Data structures:
    Scalar
    Complex number
    Vector
    Matrix
        Identity 
        Diagonal
        Row
        Column
        Zero
        Random
*/

#include <type_traits>

template <typename T, typename U>
class ComplexNumber
{
private:
    T real;
    U imaginary;

public:
    ComplexNumber(T real, U imaginary);
    friend ComplexNumber operator +(ComplexNumber<T, U> const& c1, ComplexNumber<T, U> const& c2);
    friend ComplexNumber operator -(ComplexNumber<T, U> const& c1, ComplexNumber<T, U> const& c2);
    friend ComplexNumber operator *(ComplexNumber<T, U> const& c1, ComplexNumber<T, U> const& c2);
};

template <typename T, typename U>
ComplexNumber<T, U>::ComplexNumber(T real, U imaginary)
{
    if(!std::is_arithmetic_v<T> || !std::is_arithmetic_v<U>) 
	{
		throw std::invalid_argument( "non-arithmetic arguments passed" );
	}

    this->real = real;
    this->imaginary = imaginary;
}

template <typename T, typename U>
ComplexNumber<T, U> operator +(ComplexNumber<T, U> const& c1, ComplexNumber<T, U> const& c2)
{
    return ComplexNumber<T, U>(c1.real + c2.real, c1.imaginary + c2.imaginary);
}

template <typename T, typename U>
ComplexNumber<T, U> operator -(ComplexNumber<T, U> const& c1, ComplexNumber<T, U> const& c2)
{
    return ComplexNumber<T, U>(c1.real - c2.real, c1.imaginary - c2.imaginary);
}

template <typename T, typename U>
ComplexNumber<T, U> operator *(ComplexNumber<T, U> const& c1, ComplexNumber<T, U> const& c2)
{

}