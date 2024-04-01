#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <stdexcept>

template<typename T>
class Vector {
	private:
		T* arr;
		int capacity;
		int no_elements;

		void resize();
	
	public:
		Vector();
		~Vector();
		void push_back(T key);
		void insert(T key, int index);
		T& at(int index);
		T& operator[](int index);
		const T& operator[](int index) const;
		void pop();
		int size();
		int getcapacity();
};

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
Vector<T>::Vector() {
    arr = new T[1];
    capacity = 1;
    no_elements = 0;
}

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

#endif
