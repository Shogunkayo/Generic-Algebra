#ifndef DATA_H
#define DATA_H

#include <iostream>

// Union to hold different types of values
union Value {
    char c_val;
    int i_val;
    float f_val;
    double d_val;
};

// Enum to specify the type of data stored in Value
enum class DataType {
    CHAR,
    INT,
    FLOAT,
    DOUBLE
};

struct Data {
    DataType type;
    Value value;
    
    // Default constructor used in MultiVector
    Data() = default;

    // Parameterized constructor to store value
    template <typename T>
    Data(T val) {
        if constexpr (std::is_same_v<T, char>) {
            type = DataType::CHAR;
            value.c_val = val;
        } else if constexpr (std::is_same_v<T, int>) {
            type = DataType::INT;
            value.i_val = val;
        } else if constexpr (std::is_same_v<T, float>) {
            type = DataType::FLOAT;
            value.f_val = val;
        } else if constexpr (std::is_same_v<T, double>) {
            type = DataType::DOUBLE;
            value.d_val = val;
        } else {
            throw std::invalid_argument("Invalid type for Data constructor");
        }
    }

    // Relational operator overloads
    bool operator==(const Data& other) const {
        if (type != other.type)
            return false;

        switch (type) {
            case DataType::CHAR:
                return value.c_val == other.value.c_val;
            case DataType::INT:
                return value.i_val == other.value.i_val;
            case DataType::FLOAT:
                return value.f_val == other.value.f_val;
            case DataType::DOUBLE:
                return value.d_val == other.value.d_val;
        }

        return false;
    }

    bool operator!=(const Data& other) const {
        return !(*this == other);
    }

    // Assignment operator overloads for accepted types
    Data& operator=(char c) {
        type = DataType::CHAR;
        value.c_val = c;
        return *this;
    }

    Data& operator=(int i) {
        type = DataType::INT;
        value.i_val = i;
        return *this;
    }

    Data& operator=(float f) {
        type = DataType::FLOAT;
        value.f_val = f;
        return *this;
    }

    Data& operator=(double d) {
        type = DataType::DOUBLE;
        value.d_val = d;
        return *this;
    }

    // Arithmetic operator overloads
    // Handle each type seperately to preserve precision
    Data& operator+=(const Data& other) {
        switch (type) {
            case DataType::CHAR:
                switch (other.type) {
                    case DataType::CHAR:
                        value.c_val += other.value.c_val;
                        break;
                    case DataType::INT:
                        value.c_val += static_cast<char>(other.value.i_val);
                        break;
                    case DataType::FLOAT:
                        value.c_val += static_cast<char>(other.value.f_val);
                        break;
                    case DataType::DOUBLE:
                        value.c_val += static_cast<char>(other.value.d_val);
                        break;
                }
                break;
            case DataType::INT:
                switch (other.type) {
                    case DataType::CHAR:
                        value.i_val += other.value.c_val;
                        break;
                    case DataType::INT:
                        value.i_val += other.value.i_val;
                        break;
                    case DataType::FLOAT:
                        value.i_val += static_cast<int>(other.value.f_val);
                        break;
                    case DataType::DOUBLE:
                        value.i_val += static_cast<int>(other.value.d_val);
                        break;
                }
                break;
            case DataType::FLOAT:
                switch (other.type) {
                    case DataType::CHAR:
                        value.f_val += other.value.c_val;
                        break;
                    case DataType::INT:
                        value.f_val += other.value.i_val;
                        break;
                    case DataType::FLOAT:
                        value.f_val += other.value.f_val;
                        break;
                    case DataType::DOUBLE:
                        value.f_val += static_cast<float>(other.value.d_val);
                        break;
                }
                break;
            case DataType::DOUBLE:
                switch (other.type) {
                    case DataType::CHAR:
                        value.d_val += other.value.c_val;
                        break;
                    case DataType::INT:
                        value.d_val += other.value.i_val;
                        break;
                    case DataType::FLOAT:
                        value.d_val += other.value.f_val;
                        break;
                    case DataType::DOUBLE:
                        value.d_val += other.value.d_val;
                        break;
                }
                break;
        }
        return *this;
    }

    Data operator+(const Data& other) const {
        Data result(*this);
        result += other;
        return result;
    }

    Data& operator-=(const Data& other) {
        switch (type) {
            case DataType::CHAR:
                switch (other.type) {
                    case DataType::CHAR:
                        value.c_val -= other.value.c_val;
                        break;
                    case DataType::INT:
                        value.c_val -= static_cast<char>(other.value.i_val);
                        break;
                    case DataType::FLOAT:
                        value.c_val -= static_cast<char>(other.value.f_val);
                        break;
                    case DataType::DOUBLE:
                        value.c_val -= static_cast<char>(other.value.d_val);
                        break;
                }
                break;
            case DataType::INT:
                switch (other.type) {
                    case DataType::CHAR:
                        value.i_val -= other.value.c_val;
                        break;
                    case DataType::INT:
                        value.i_val -= other.value.i_val;
                        break;
                    case DataType::FLOAT:
                        value.i_val -= static_cast<int>(other.value.f_val);
                        break;
                    case DataType::DOUBLE:
                        value.i_val -= static_cast<int>(other.value.d_val);
                        break;
                }
                break;
            case DataType::FLOAT:
                switch (other.type) {
                    case DataType::CHAR:
                        value.f_val -= other.value.c_val;
                        break;
                    case DataType::INT:
                        value.f_val -= other.value.i_val;
                        break;
                    case DataType::FLOAT:
                        value.f_val -= other.value.f_val;
                        break;
                    case DataType::DOUBLE:
                        value.f_val -= static_cast<float>(other.value.d_val);
                        break;
                }
                break;
            case DataType::DOUBLE:
                switch (other.type) {
                    case DataType::CHAR:
                        value.d_val -= other.value.c_val;
                        break;
                    case DataType::INT:
                        value.d_val -= other.value.i_val;
                        break;
                    case DataType::FLOAT:
                        value.d_val -= other.value.f_val;
                        break;
                    case DataType::DOUBLE:
                        value.d_val -= other.value.d_val;
                        break;
                }
                break;
        }
        return *this;
    }

    Data operator-(const Data& other) const {
        Data result(*this);
        result -= other;
        return result;
    }

    Data& operator*=(const Data& other) {
        switch (type) {
            case DataType::CHAR:
                switch (other.type) {
                    case DataType::CHAR:
                        value.c_val *= other.value.c_val;
                        break;
                    case DataType::INT:
                        value.c_val *= static_cast<char>(other.value.i_val);
                        break;
                    case DataType::FLOAT:
                        value.c_val *= static_cast<char>(other.value.f_val);
                        break;
                    case DataType::DOUBLE:
                        value.c_val *= static_cast<char>(other.value.d_val);
                        break;
                }
                break;
            case DataType::INT:
                switch (other.type) {
                    case DataType::CHAR:
                        value.i_val *= other.value.c_val;
                        break;
                    case DataType::INT:
                        value.i_val *= other.value.i_val;
                        break;
                    case DataType::FLOAT:
                        value.i_val *= static_cast<int>(other.value.f_val);
                        break;
                    case DataType::DOUBLE:
                        value.i_val *= static_cast<int>(other.value.d_val);
                        break;
                }
                break;
            case DataType::FLOAT:
                switch (other.type) {
                    case DataType::CHAR:
                        value.f_val *= other.value.c_val;
                        break;
                    case DataType::INT:
                        value.f_val *= other.value.i_val;
                        break;
                    case DataType::FLOAT:
                        value.f_val *= other.value.f_val;
                        break;
                    case DataType::DOUBLE:
                        value.f_val *= static_cast<float>(other.value.d_val);
                        break;
                }
                break;
            case DataType::DOUBLE:
                switch (other.type) {
                    case DataType::CHAR:
                        value.d_val *= other.value.c_val;
                        break;
                    case DataType::INT:
                        value.d_val *= other.value.i_val;
                        break;
                    case DataType::FLOAT:
                        value.d_val *= other.value.f_val;
                        break;
                    case DataType::DOUBLE:
                        value.d_val *= other.value.d_val;
                        break;
                }
                break;
        }
        return *this;
    }

    Data operator*(const Data& other) const {
        Data result(*this);
        result *= other;
        return result;
    }

    Data& operator/=(const Data& other) {
        switch (type) {
            case DataType::CHAR:
                switch (other.type) {
                    case DataType::CHAR:
                        value.c_val /= other.value.c_val;
                        break;
                    case DataType::INT:
                        value.c_val /= static_cast<char>(other.value.i_val);
                        break;
                    case DataType::FLOAT:
                        value.c_val /= static_cast<char>(other.value.f_val);
                        break;
                    case DataType::DOUBLE:
                        value.c_val /= static_cast<char>(other.value.d_val);
                        break;
                }
                break;
            case DataType::INT:
                switch (other.type) {
                    case DataType::CHAR:
                        value.i_val /= other.value.c_val;
                        break;
                    case DataType::INT:
                        value.i_val /= other.value.i_val;
                        break;
                    case DataType::FLOAT:
                        value.i_val /= static_cast<int>(other.value.f_val);
                        break;
                    case DataType::DOUBLE:
                        value.i_val /= static_cast<int>(other.value.d_val);
                        break;
                }
                break;
            case DataType::FLOAT:
                switch (other.type) {
                    case DataType::CHAR:
                        value.f_val /= other.value.c_val;
                        break;
                    case DataType::INT:
                        value.f_val /= other.value.i_val;
                        break;
                    case DataType::FLOAT:
                        value.f_val /= other.value.f_val;
                        break;
                    case DataType::DOUBLE:
                        value.f_val /= static_cast<float>(other.value.d_val);
                        break;
                }
                break;
            case DataType::DOUBLE:
                switch (other.type) {
                    case DataType::CHAR:
                        value.d_val /= other.value.c_val;
                        break;
                    case DataType::INT:
                        value.d_val /= other.value.i_val;
                        break;
                    case DataType::FLOAT:
                        value.d_val /= other.value.f_val;
                        break;
                    case DataType::DOUBLE:
                        value.d_val /= other.value.d_val;
                        break;
                }
                break;
        }
        return *this;
    }

    Data operator/(const Data& other) const {
        Data result(*this);
        result /= other;
        return result;
    }

    // Friend function to overload output and input stream operators
    friend std::ostream& operator<<(std::ostream& os, const Data& data);
    friend std::istream& operator>>(std::istream& is, Data& data);
};

std::ostream& operator<<(std::ostream& os, const Data& data) {
    switch (data.type) {
        case DataType::CHAR:
            os << data.value.c_val;
            break;
        case DataType::INT:
            os << data.value.i_val;
            break;
        case DataType::FLOAT:
            os << data.value.f_val;
            break;
        case DataType::DOUBLE:
            os << data.value.d_val;
            break;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Data& data) {
    switch (data.type) {
        case DataType::CHAR:
            is >> data.value.c_val;
            break;
        case DataType::INT:
            is >> data.value.i_val;
            break;
        case DataType::FLOAT:
            is >> data.value.f_val;
            break;
        case DataType::DOUBLE:
            is >> data.value.d_val;
            break;
    }
    return is;
}

#endif
