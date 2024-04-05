#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <stdexcept>
#include "./complexnumber.h"

template<typename T>
class Vector {
	public:
		T* arr;
		int capacity;
		int no_elements;
	
		Vector () : arr(new T[1]), capacity(1), no_elements(0) {}
		Vector (std::initializer_list<T> init): capacity(init.size()), no_elements(init.size()) {
			arr = new T[capacity];
			auto first = init.begin();
			auto last = init.end();
			for (int i = 0; first != last ; ++i, (void)++first)
				arr[i] = *first;
		}
		Vector (Vector &obj) {
			capacity = obj.capacity;
			no_elements = obj.no_elements;
			arr = new T[capacity];

			for (int i = 0; i < no_elements; i++) {
				arr[i] = obj.arr[i];
			}

		}
		Vector& operator= (Vector &obj) {
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
		~Vector();

		void resize();
		void push_back(T key);
		void insert(T key, int index);
		void pop();

		T& at(int index);
		T& operator[](int index);
		const T& operator[](int index) const;

		int size();
		int getcapacity();
};

template <typename T>
Vector<T>::~Vector() {
    if constexpr (std::is_class<T>::value) {
        for (int i = 0; i < no_elements; i++) {
            arr[i].~T();
        }
    }
    delete[] arr;
}

template <typename T>
void Vector<T>::resize() {
	T* new_arr = new T[capacity * 2];

	for (int i = 0; i < no_elements; i++) {
		new_arr[i] = arr[i];
	}

	delete[] arr;
	arr = new_arr;
	capacity *= 2;
}

template <typename T>
void Vector<T>::push_back(T key) {
    if (no_elements == capacity) {
        resize();
    }
    arr[no_elements++] = key;
}

template <typename T>
void Vector<T>::insert(T key, int index) {
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
T& Vector<T>::at(int index) {
    if (index < 0 || index > no_elements - 1) {
        throw std::out_of_range("Index out of bounds");
    }
    return arr[index];
}

template <typename T>
T& Vector<T>::operator[](int index) {
    if (index < 0 || index > no_elements - 1) {
        throw std::out_of_range("Index out of bounds");
    }
    return arr[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const {
    if (index < 0 || index > no_elements - 1) {
        throw std::out_of_range("Index out of bounds");
    }
    return arr[index];
}

template <typename T>
void Vector<T>::pop() {
    no_elements--;
}

template <typename T>
int Vector<T>::size() {
    return no_elements;
}

template <typename T>
int Vector<T>::getcapacity() {
    return capacity;
}

// ----------------------------------------------------------------------------

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
