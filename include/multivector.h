#ifndef MULTIVECTOR_H
#define MULTIVECTOR_H

#include "vector.h"
#include "data.h"

class MultiVector {
    public:
        // Vector of Data
        Vector<Data> vector;

        // Default constructor
        MultiVector() = default;

        // Variadic template constructor
        template <typename... Args>
        MultiVector(Args&&... args) {
            // fold expression to push each argument into vector
            (push_back(args), ...);
        }

        // Push value to vector by converting
        // T& value to Data object
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

        // Insert value at position index of vector
        // by converting T& value to Data object
        template <typename T>
        void insert(const T& value, const int& index) {
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

            vector.insert(data, index);
        }

        // Pop element from vector
        void pop() {
            vector.pop();
        }

        // returns the value of Data at position index
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

        // [] operator overload which returns a reference to Data 
        // [] operator return type cannot be templatized
        Data& operator[](const int index) {
            if (index >= vector.size()) {
                throw std::out_of_range("Index out of bounds");
            } 

            return vector[index];
        }

        // scalar arithmetic operator overloads
        MultiVector operator+(const Data obj) {
            MultiVector result;
            result.vector = vector + obj;
            
            return result;
        }

        MultiVector operator-(const Data obj) {
            MultiVector result;
            result.vector = vector - obj;
            
            return result;
        }

        MultiVector operator*(const Data obj) {
            MultiVector result;
            result.vector = vector * obj;
            
            return result;
        }

        MultiVector operator/(const Data obj) {
            MultiVector result;
            result.vector = vector / obj;
            
            return result;
        }

        // vector arithmetic operator overloads
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

        // return the magnitude of MultiVector
        double magnitude() {
            Data result(0.0); 
            for (int i = 0; i < vector.size(); i++) {
                result += vector[i] * vector[i];
            }

            return sqrt(result.value.d_val);
        }

        // apply vector transpose
        void transpose() {
            vector.transpose();
        }

        // apply vector map
        template <typename Func>
        void map(Func &&func) {
            vector.map(func);
        }

        // apply vector square
        void square() {
            vector.square();
        }

        // apply vector pow
        void pow(const size_t& exponent) {
            vector.pow(exponent);  
        }
};

#endif
