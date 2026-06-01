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
#include<iostream>
#include<vector>


template <typename T, const std :: size_t U>
class small_vector{
    std :: size_t N = U;
    std :: vector<std :: byte>new_arr; // will be used only when we out capacity the stack
    std :: byte arr[U * sizeof(T)];
    void *mem = &arr;
    int offset = 0;
    

    void* shift(){
        // responsible for changing the pointer, will return new pointer as void *
        mem = &
    }
    public:
    
    size_t size(){
        return N;
    }
};

int main(){
    small_vector<int, 2>sv;
    std :: cout<< sv.size() << std::endl;
}