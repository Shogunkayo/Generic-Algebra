#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>
#include <iostream>
#include <variant>
#include "complexnumber.h"
#include "data.h"

template<typename T>
class VectorContainer {
	public:
		T* arr;
		int capacity;
		int no_elements;
	
		VectorContainer () : arr(new T[1]), capacity(1), no_elements(0) {}
		VectorContainer (std::initializer_list<T> init): capacity(init.size()), no_elements(init.size()) {
			arr = new T[capacity];
			auto first = init.begin();
			auto last = init.end();
			for (int i = 0; first != last ; ++i, (void)++first)
				arr[i] = *first;
		}
		VectorContainer (VectorContainer &obj) {
			capacity = obj.capacity;
			no_elements = obj.no_elements;
			arr = new T[capacity];

			for (int i = 0; i < no_elements; i++) {
				arr[i] = obj.arr[i];
			}

		}
		VectorContainer& operator= (VectorContainer &obj) {
			if (this->capacity != obj.capacity) {
				if constexpr (std::is_class<T>::value) {
					for (int i = 0; i < this->no_elements; i++) {
						this->arr[i].~T();
					}
				}
				delete[] this->arr;
				this->capacity = obj.capacity;
				this->arr = new T[this->capacity];
			}

			for (int i = 0; i < obj.no_elements; i++) {
				this->arr[i] = obj.arr[i];
			}

			this->no_elements = obj.no_elements;
			return (*this);
		}
		~VectorContainer();

		void resize();
		void push_back(const T key);
		void insert(const T key, const int index);
		void pop();

		T& at(const int index);
		T& operator[](const int index);
		const T& operator[](const int index) const;

		int size() const;
		int getcapacity() const;
};

template <typename T>
VectorContainer<T>::~VectorContainer() {
    if constexpr (std::is_class<T>::value) {
        for (int i = 0; i < no_elements; i++) {
            arr[i].~T();
        }
    }
    delete[] arr;
}

template <typename T>
void VectorContainer<T>::resize() {
	T* new_arr = new T[capacity * 2];

	for (int i = 0; i < no_elements; i++) {
		new_arr[i] = arr[i];
	}

	delete[] arr;
	arr = new_arr;
	capacity *= 2;
}

template <typename T>
void VectorContainer<T>::push_back(const T key) {
    if (no_elements == capacity) {
        resize();
    }
    arr[no_elements++] = key;
}

template <typename T>
void VectorContainer<T>::insert(const T key, const int index) {
    if (index < 0) {
        throw std::out_of_range("Index must be positive");
    }
    if (index >= no_elements) {
        // same operation as push_back
        return push_back(key);
    }
    if (no_elements == capacity) {
        resize();
    }
    for (int i = no_elements; i >= 0; i--) {
        if (i == index) {
            arr[i] = key;
            no_elements++;
            break;
        }
        arr[i] = arr[i - 1];
    }
}

template <typename T>
T& VectorContainer<T>::at(const int index) {
    if (index < 0 || index > no_elements - 1) {
        throw std::out_of_range("Index out of bounds");
    }
    return arr[index];
}

template <typename T>
T& VectorContainer<T>::operator[](const int index) {
    if (index < 0 || index > no_elements - 1) {
        throw std::out_of_range("Index out of bounds");
    }
    return arr[index];
}

template <typename T>
const T& VectorContainer<T>::operator[](const int index) const {
    if (index < 0 || index > no_elements - 1) {
        throw std::out_of_range("Index out of bounds");
    }
    return arr[index];
}

template <typename T>
void VectorContainer<T>::pop() {
    no_elements--;
}

template <typename T>
int VectorContainer<T>::size() const {
    return no_elements;
}

template <typename T>
int VectorContainer<T>::getcapacity() const {
    return capacity;
}

// ----------------------------------------------------------------------------

template <Arithmetic T>
class Vector;

template <typename T>
double euclidean_distance(const Vector<T>& v1, const Vector<T>& v2);

template <Arithmetic T>
class Vector : public VectorContainer<T> {
	public:
		int dim_l;
		int dim_r;
		int isColumn;
	
		Vector() : dim_l(0), dim_r(1), isColumn(1) {}
		Vector(std::initializer_list<T> init) : VectorContainer<T>(init), dim_l(init.size()), dim_r(1), isColumn(1) {}
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
		Vector& operator= (Vector&& other) noexcept {
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
		
		void push_back(const T key);
		void insert(const T key, const int index);
		void pop();

		VectorContainer<int> get_dimensions();

		Vector<T> operator+ (const T obj);
		Vector<T> operator- (const T obj);
		Vector<T> operator* (const T obj);
		Vector<T> operator/ (const T obj);
		Vector<T> operator+ (Vector<T> obj);
		Vector<T> operator- (Vector<T> obj);

		double magnitude();
		void transpose();

		friend double euclidean_distance<>(const Vector<T>& v1, const Vector<T>& v2);

		template <typename Func>
		void map(Func&& func) {
			for (int i = 0; i < this->no_elements; i++) {
				this->arr[i] = func(this->arr[i]);
			}
		}

		void square();
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
VectorContainer<int> Vector<T>::get_dimensions() {
	return VectorContainer<int> (dim_l, dim_r);
}

template <Arithmetic T>
Vector<T> Vector<T>::operator+ (const T obj) {
	Vector<T> result = (*this);

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] += obj;
	}

	return result;
}

template <Arithmetic T>
Vector<T> Vector<T>::operator- (const T obj) {
	Vector<T> result = (*this);

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] -= obj;
	}

	return result;
}

template <Arithmetic T>
Vector<T> Vector<T>::operator* (const T obj) {
	Vector<T> result = (*this);

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] *= obj;
	}

	return result;
}

template <Arithmetic T>
Vector<T> Vector<T>::operator/ (const T obj) {
	Vector<T> result = (*this);

	for (int i = 0; i < result.no_elements; i++) {
		result.arr[i] /= obj;
	}

	return result;
}

template <Arithmetic T>
Vector<T> Vector<T>::operator+ (const Vector<T> obj) {
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
Vector<T> Vector<T>::operator- (const Vector<T> obj) {
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
double Vector<T>::magnitude () {
	double result = 0;
	for (int i = 0; i < this->no_elements; i++) {
		result += this->arr[i] * this->arr[i];
	}

	return sqrt(result);
}

template <Arithmetic T>
void Vector<T>::transpose () {
	isColumn = !isColumn;
	dim_r = dim_r ^ dim_l;
	dim_l = dim_r ^ dim_l;
	dim_r = dim_r ^ dim_l;
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

template <typename T, typename U>
auto dot(const Vector<T>& v1, const Vector<U>& v2) {
	if (v1.no_elements != v2.no_elements) {
		throw std::invalid_argument("Vectors should have equal number of elements");
	}

	using ReturnType = std::conditional_t<std::is_same_v<T, int> && std::is_same_v<U, int>, int, double>;
	ReturnType result = 0;
	for (int i = 0; i < v1.no_elements; i++) {
		result += v1.arr[i] * v2.arr[i];
	}

	return result;
}

template <Arithmetic T>
void Vector<T>::square () {
	this->map([] <Arithmetic U> (U a) {return a * a;});
}

// ----------------------------------------------------------------------------

class MultiVector {
    public:
        Vector<Data> vector;

        MultiVector() = default;

        template <typename... Args>
        MultiVector(Args&&... args) {
            (push_back(args), ...);
        }

        template <typename T>
        void push_back(const T& value) {
            Data data;
            if constexpr (std::is_same_v<T, char>) {
                data.type = DataType::CHAR;
                data.value.c_val = value;
            }
            else if constexpr (std::is_same_v<T, int>) {
                data.type = DataType::INT;
                data.value.i_val = value;
            }
            else if constexpr (std::is_same_v<T, float>) {
                data.type = DataType::FLOAT;
                data.value.f_val = value;
            }
            else if constexpr (std::is_same_v<T, double>) {
                data.type = DataType::DOUBLE;
                data.value.d_val = value;
            }
            else {
                throw std::invalid_argument("Invalid type");
            }

            vector.push_back(data);
        }

        template <typename T>
        T at(const int index) {
            Data& data = vector.at(index);
            if (data.type == DataType::CHAR) {
                return data.value.c_val;
            }
            else if (data.type == DataType::INT) {
                return data.value.i_val;
            }
            else if (data.type == DataType::FLOAT) {
                return data.value.f_val;
            }
            else if (data.type == DataType::DOUBLE) {
                return data.value.d_val;
            }
            else {
                throw std::invalid_argument("Invalid type");
                return 0;
            }
        }

        void transpose() {
            vector.transpose();
        }

        Data& operator[](const int index) {
            if (index >= vector.size()) {
                throw std::out_of_range("Index out of bounds");
            } 

            return vector[index];
        }

        MultiVector operator+(const Data obj) {
            MultiVector result;
            result.vector = vector + obj;
            
            return result;
        }

        MultiVector operator+(MultiVector& obj) {
            if (vector.size() != obj.vector.size()) {
                throw std::invalid_argument("MultiVectors should have equal number of elements");
            }

            MultiVector result;
            result.vector = vector + obj.vector;

            return result;
        }

        MultiVector operator-(MultiVector& obj) {
            if (vector.size() != obj.vector.size()) {
                throw std::invalid_argument("MultiVectors should have equal number of elements");
            }

            MultiVector result;
            result.vector = vector - obj.vector;

            return result;
        }
        void square() {
            vector.square();
        }

        template <typename Func>
        void map(Func &&func) {
            vector.map(func);
        }

        double magnitude() {
            Data result(0.0); 
            for (int i = 0; i < vector.size(); i++) {
                result += vector[i] * vector[i];
            }

            return sqrt(result.value.d_val);
        }
};

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

#endif
