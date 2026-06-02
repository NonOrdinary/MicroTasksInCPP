/*
A standard std::vector always allocates memory on the heap, even if it only holds one or two elements.
 This causes cache misses and allocator overhead.
 A SmallVector<T, N> contains a tiny, inline raw byte array capable of holding up to N elements directly on the stack.
 - Case A: If your vector has $\le N$ elements, it uses the stack buffer. Zero heap allocations.
 - Case B: The moment you add the $(N+1)$-th element, it dynamically allocates heap memory, copies/moves the existing elements over, and acts like a normal vector from then on.*/

/**
 * Ever wondered how does int arr[4] work,but int arr[N] doesn't ? The answer is how the array receives
 * the size, if it's a const value i.e if N is a const value, then we can otherwise not, so watch the template 
 *  
 */

 #include <iostream>
#include <new>       
#include <utility>   

template <typename T, std::size_t N>
class small_vector {
private:
    // Forcing the raw byte array to be perfectly aligned for type T ~ 
    alignas(T) std::byte stack_buffer[N * sizeof(T)];
    
    T* data_ptr = nullptr;
    
    std::size_t current_size = 0;
    std::size_t current_capacity = N;
    bool is_on_heap = false;

    void grow() {
        
        std::size_t new_capacity = current_capacity * 2;
        
        
        T* new_heap = reinterpret_cast<T*>(new std::byte[new_capacity * sizeof(T)]);

        for (std::size_t i = 0; i < current_size; ++i) {

            new (&new_heap[i]) T(std::move(data_ptr[i]));
            

            data_ptr[i].~T();
        }

        if (is_on_heap) {
            delete[] reinterpret_cast<std::byte*>(data_ptr);
        }

        data_ptr = new_heap;
        current_capacity = new_capacity;
        is_on_heap = true;
    }

public:
    
    small_vector() {
        // reinterprer_cast cast a pointer of a type to other type : basically forces
        data_ptr = reinterpret_cast<T*>(stack_buffer);
    }

    
    ~small_vector() {
        for (std::size_t i = 0; i < current_size; ++i) {
            data_ptr[i].~T(); // Call the destructor manually
        }
        if (is_on_heap) {
            delete[] reinterpret_cast<std::byte*>(data_ptr);
        }
    }

    void push_back(const T& element) {
        if (current_size == current_capacity) {
            grow();
        }
        
        new (data_ptr + current_size) T(element);
        current_size++;
    }

    void pop_back() {
        if (current_size > 0) {
            current_size--;
            
            data_ptr[current_size].~T();
        }
    }

    std::size_t size() const { return current_size; }
    std::size_t capacity() const { return current_capacity; }

    T& operator[](std::size_t index) { return data_ptr[index]; }
};

int main() {
    small_vector<std::string, 2> sv;

    std::cout << "Initial capacity: " << sv.capacity() << "\n";

    sv.push_back("Stack String 1");
    sv.push_back("Stack String 2");
    std::cout << "Size after 2 pushes: " << sv.size() << " | Capacity: " << sv.capacity() << "\n";

    sv.push_back("Heap String 3");
    std::cout << "Size after 3 pushes: " << sv.size() << " | Capacity: " << sv.capacity() << "\n";

    std::cout << "Element at index 2: " << sv[2] << "\n";
}