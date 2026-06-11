/**
 * Task 1: Make your Buffer fully const-correct

Take your current class and make these methods const where appropriate:

print()
container_size()
get()

Also make your copy constructor and copy assignment work with const objects:

const Buffer a(5);
Buffer b = a;
 */

/**
 * Non - Const function and members can never be called from const objects
 */

#include <iostream>
class Buffer
{
    int *arr = nullptr;
    size_t container_size;
    void init(){
        for(int i = 0; i < container_size; i++){
            arr[i] = 1; 
        }
    }

public:
    
    Buffer(size_t N) : container_size(N){
        arr = new int[this->container_size];
        init();
    }
    // move constructor
    // noexcept : guarantees that this function shall never throw exception
    Buffer(Buffer &&b) noexcept {
        this->arr = b.arr;
        this->container_size = b.container_size;
        // reset
        b.arr = nullptr;
        b.container_size = 0;
    }

    Buffer &operator=(Buffer &&other) noexcept{
        if (this == &other){
            return *this;
        }

        delete[] arr; // release current resource

        arr = other.arr; // steal
        container_size = other.container_size;

        other.arr = nullptr; // leave source valid
        other.container_size = 0;
        return *this;
    }

    Buffer (const Buffer& other) noexcept{
        this->container_size = other.container_size;
        this->arr = new int[container_size];
        init();
    }

    Buffer& operator=(const Buffer& other) noexcept {
        this->container_size = other.container_size;
        this -> arr = new int[container_size];
        for(int i = 0; i < container_size; i++){
            arr[i] = other.arr[i];
        }
        return *this;
    }

    void put(size_t index, int val){
        arr[index] = val;
    }

    void print() const {
        for (int i = 0; i < this->container_size; i++)
        {
            std ::cout << arr[i] << " ";
        }
        std ::cout << std ::endl;
    }

    size_t size() const {
        return this->container_size;
    }

    int get(int index) const {
        if(index >= this->container_size){
            throw ("Not found at index : %d",index);
        }
        return this->arr[index];
    }
};

int main()
{
    Buffer a(3);
    Buffer b(5);
    Buffer c = a;
    b = a;
    Buffer d = std::move(a);
    c = std::move(b);
    a.print();
    b.print();
    c.print();
    return 0;
}