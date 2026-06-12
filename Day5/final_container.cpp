#include <iostream>
#include <stdexcept>
#include <utility>

class Buffer {
    int* arr = nullptr;
    size_t size_ = 0;

public:
    Buffer(size_t n) : arr(new int[n]), size_(n) {
        for (size_t i = 0; i < size_; i++) {
            arr[i] = 1;
        }
    }

    Buffer(const Buffer& other) : arr(new int[other.size_]), size_(other.size_) {
        for (size_t i = 0; i < size_; i++) {
            arr[i] = other.arr[i];
        }
    }

    Buffer(Buffer&& other) noexcept : arr(other.arr), size_(other.size_) {
        other.arr = nullptr;
        other.size_ = 0;
    }

    Buffer& operator=(const Buffer& other) {
        if (this == &other) return *this;

        int* temp = new int[other.size_];
        for (size_t i = 0; i < other.size_; i++) {
            temp[i] = other.arr[i];
        }

        delete[] arr;
        arr = temp;
        size_ = other.size_;

        return *this;
    }

    Buffer& operator=(Buffer&& other) noexcept {
        if (this == &other) return *this;

        delete[] arr;
        arr = other.arr;
        size_ = other.size_;

        other.arr = nullptr;
        other.size_ = 0;

        return *this;
    }

    ~Buffer() {
        delete[] arr;
    }

    // Task 1: operator[] overloads
    int& operator[](size_t index) {
        return arr[index];
    }

    const int& operator[](size_t index) const {
        return arr[index];
    }

    // Task 2: checked access
    int& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Buffer::at - index out of range");
        }
        return arr[index];
    }

    const int& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Buffer::at - index out of range");
        }
        return arr[index];
    }

    size_t size() const {
        return size_;
    }

    void print() const {
        for (size_t i = 0; i < size_; i++) {
            std::cout << arr[i] << ' ';
        }
        std::cout << '\n';
    }

    // Task 3: stream output
    friend std::ostream& operator<<(std::ostream& os, const Buffer& b) {
        os << '[';
        for (size_t i = 0; i < b.size_; i++) {
            os << b.arr[i];
            if (i + 1 < b.size_) os << ", ";
        }
        os << ']';
        return os;
    }
};

int main() {
    Buffer a(5);
    a[2] = 99;

    const Buffer b = a;

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';

    std::cout << "b[2] = " << b[2] << '\n';

    try {
        std::cout << "a.at(2) = " << a.at(2) << '\n';
        std::cout << "a.at(100) = " << a.at(100) << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << '\n';
    }

    Buffer c = std::move(a);
    std::cout << "c = " << c << '\n';
    std::cout << "a after move = " << a << '\n';

    return 0;
}