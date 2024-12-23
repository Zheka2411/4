#include <iostream>

template <typename T>
class Array {
private:
    T* data;
    size_t size;

public:
    // Конструктор
    Array(size_t size = 0) : size(size) {
        data = new T[size];
    }

    // Конструктор копіювання
    Array(const Array& other) : size(other.size) {
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Оператор = (глибоке копіювання)
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Оператор + (поелементне об'єднання)
    Array operator+(const Array& other) const {
        size_t newSize = size + other.size;
        Array newArray(newSize);
        for (size_t i = 0; i < size; ++i) {
            newArray.data[i] = data[i];
        }
        for (size_t i = 0; i < other.size; ++i) {
            newArray.data[size + i] = other.data[i];
        }
        return newArray;
    }

    // Оператор += (поелементне об'єднання з присвоєнням)
    Array& operator+=(const Array& other) {
        size_t newSize = size + other.size;
        T* newData = new T[newSize];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        for (size_t i = 0; i < other.size; ++i) {
            newData[size + i] = other.data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
        return *this;
    }

    // Оператор [] (доступ до елементу по індексу)
    T& operator[](size_t index) {
        return data[index];
    }

    // Оператор << (виведення масиву в консоль)
    friend std::ostream& operator<<(std::ostream& os, const Array& arr) {
        for (size_t i = 0; i < arr.size; ++i) {
            os << arr.data[i] << " ";
        }
        return os;
    }

    // Оператор == (поелементне порівняння)
    bool operator==(const Array& other) const {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    // Оператор != (поелементне порівняння на нерівність)
    bool operator!=(const Array& other) const {
        return !(*this == other);
    }

    // Оператор > (порівняння за довжиною)
    bool operator>(const Array& other) const {
        return size > other.size;
    }

    // Оператор < (порівняння за довжиною)
    bool operator<(const Array& other) const {
        return size < other.size;
    }

    // Оператор * (спільні елементи)
    Array operator*(const Array& other) const {
        size_t minSize = std::min(size, other.size);
        Array commonArray(minSize);
        size_t index = 0;
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < other.size; ++j) {
                if (data[i] == other.data[j]) {
                    commonArray.data[index++] = data[i];
                }
            }
        }
        return commonArray;
    }

    // Деструктор
    ~Array() {
        delete[] data;
    }
};

int main() {
    Array<int> arr1(5);
    Array<int> arr2(3);

    for (int i = 0; i < 5; ++i) arr1[i] = i + 1;
    for (int i = 0; i < 3; ++i) arr2[i] = i + 4;

    Array<int> arr3 = arr1 + arr2; // поелементне об'єднання
    std::cout << arr3 << std::endl;

    arr1 += arr2; // поелементне об'єднання з присвоєнням
    std::cout << arr1 << std::endl;

    std::cout << (arr1 == arr2) << std::endl; // порівняння на рівність
    std::cout << (arr1 > arr2) << std::endl;  // порівняння за довжиною

    Array<int> common = arr1 * arr2; // спільні елементи
    std::cout << common << std::endl;

    return 0;
}
