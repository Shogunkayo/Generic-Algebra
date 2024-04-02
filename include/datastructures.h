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
    T getReal();
    U getImaginary();
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
T ComplexNumber<T, U>::getReal()
{
    return this->real;
}

template <typename T, typename U>
U ComplexNumber<T, U>::getImaginary()
{
    return this->imaginary;
}