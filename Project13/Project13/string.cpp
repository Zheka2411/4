#include <iostream>
#include <cstring>

class String {
private:
    char* data;
public:
    // Конструктор
    String(const char* str = "") {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    // Конструктор копіювання
    String(const String& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    // Оператор = (глибоке копіювання)
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    // Оператор + (конкатенація рядків)
    String operator+(const String& other) const {
        size_t newLength = strlen(data) + strlen(other.data) + 1;
        char* newData = new char[newLength];
        strcpy(newData, data);
        strcat(newData, other.data);
        return String(newData);
    }

    // Оператор += (конкатенація з присвоєнням)
    String& operator+=(const String& other) {
        size_t newLength = strlen(data) + strlen(other.data) + 1;
        char* newData = new char[newLength];
        strcpy(newData, data);
        strcat(newData, other.data);
        delete[] data;
        data = newData;
        return *this;
    }

    // Оператор [] (доступ до символу по індексу)
    char operator[](size_t index) const {
        return data[index];
    }

    // Оператор << (виведення рядка в консоль)
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        os << str.data;
        return os;
    }

    // Оператор == (порівняння на рівність)
    bool operator==(const String& other) const {
        return strcmp(data, other.data) == 0;
    }

    // Оператор != (порівняння на нерівність)
    bool operator!=(const String& other) const {
        return strcmp(data, other.data) != 0;
    }

    // Оператор > (порівняння за довжиною)
    bool operator>(const String& other) const {
        return strlen(data) > strlen(other.data);
    }

    // Оператор < (порівняння за довжиною)
    bool operator<(const String& other) const {
        return strlen(data) < strlen(other.data);
    }

    // Деструктор
    ~String() {
        delete[] data;
    }
};

int main() {
    String str1("Hello");
    String str2("World");
    String str3 = str1 + str2; // конкатенація
    std::cout << str3 << std::endl;

    str1 += str2; // +=
    std::cout << str1 << std::endl;

    std::cout << (str1 == str2) << std::endl; // порівняння на рівність
    std::cout << (str1 > str2) << std::endl;  // порівняння за довжиною

    std::cout << str1[1] << std::endl; // доступ до символу

    return 0;
}
