#ifndef VECTORCONTAINER_H
#define VECTORCONTAINER_H

#include <initializer_list>
#include <type_traits>
#include <stdexcept>

template<typename T>
class VectorContainer {
	public:
		T* arr;
		int capacity;
		int no_elements;
	
        // Default constructor
		VectorContainer() : arr(new T[1]), capacity(1), no_elements(0) {}

        // Contructor for initializer_list
		VectorContainer(std::initializer_list<T> init): capacity(init.size()), no_elements(init.size()) {
			arr = new T[capacity];
			auto first = init.begin();
			auto last = init.end();
			for (int i = 0; first != last ; ++i, ++first)
				arr[i] = *first;
        }

        // Copy constructor
		VectorContainer(VectorContainer &obj) {
			capacity = obj.capacity;
			no_elements = obj.no_elements;
			arr = new T[capacity];

			for (int i = 0; i < no_elements; i++) {
				arr[i] = obj.arr[i];
			}
		}
        
        // Copy assignment
		VectorContainer& operator=(VectorContainer &obj) {
			if (this->capacity != obj.capacity) {
				if constexpr (std::is_class<T>::value) {
					for (int i = 0; i < this->no_elements; i++) {
						this->arr[i].~T();
					}
				}
                if (this->arr != nullptr) {
                    delete[] this->arr;
                }
				this->capacity = obj.capacity;
				this->arr = new T[this->capacity];
			}

			for (int i = 0; i < obj.no_elements; i++) {
				this->arr[i] = obj.arr[i];
			}

			this->no_elements = obj.no_elements;
			return (*this);
		}

        // Destructor
		~VectorContainer() {
            // if the VectorContainer type is a class,
            // call the destructor of each element
            if constexpr (std::is_class<T>::value) {
                for (int i = 0; i < no_elements; i++) {
                    arr[i].~T();
                }
            }
            if (arr != nullptr) {
                delete[] arr;
            }
        }

        // resize arr
		void resize();

        // add key to end of arr
		void push_back(const T key);

        // add key to arr at position index
		void insert(const T key, const int index);

        // remove the last element of arr
		void pop();

        // access the element at position index
		T& at(const int index);

        // [] overload to access element at position index
		T& operator[](const int index);     // for writes
		const T& operator[](const int index) const; // for reads

        // return the size and capacity of arr
		int size() const;
		int getcapacity() const;
};

template <typename T>
void VectorContainer<T>::resize() {
    // resize the arr to new size = capacity * 2
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
    // resize the arr when no_elements = capacity
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
        // resize arr when insert causes
        // no_elements > capacity
        resize();
    }

    // insert at specified index
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
    return at(index);
}

template <typename T>
const T& VectorContainer<T>::operator[](const int index) const {
    return at(index);
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

#endif
