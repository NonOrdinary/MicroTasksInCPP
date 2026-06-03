/**
 * 
Take the same Buffer class and do this:
create one object
copy it into another object using assignment or copy construction
call print() on both
then let both go out of scope

First observe the problem. Then fix it.

Your fix should make the class safely copyable:

add a copy constructor
add copy assignment
make sure each object owns its own memory
 */

#include<iostream>

class Buffer{
    std :: size_t capacity;
    int *data_ptr;
    public:
    Buffer(const std :: size_t & s_N) : capacity(s_N){
        data_ptr = new int[capacity];  // something new to me, an array of integer with capacity on heap(new key word -> heap)
        for(int i = 0; i < capacity ; i++){
            *(data_ptr + i) = 1; // data_ptr[i] is also validś
        }

        std :: cout <<" Constructor " << std :: endl;
    }
    void print(){
        for(int i = 0; i < capacity; i++){
            std :: cout << data_ptr[i] <<" ";
        }
        std :: cout << std :: endl;
    }
    void put(int ele,int index){
        if(index >= capacity){
            // overflow
            std :: cout <<"Overflow" << std :: endl;
            return;
        }
        data_ptr[index] = ele;
    }
    size_t size(){
        return this->capacity;
    }

    //copy constructor
    Buffer (const Buffer& b) :capacity(b.capacity){
        // the const make sure object cannot be modified
        // the (&) is used to not move to infinite loop
        // because to make a copy, it would invoke copy 
        // thus going to infinite loop
        data_ptr = new int[capacity];
        for(int i = 0; i < capacity; i++){
            data_ptr[i] = *(b.data_ptr + i);
        }
    }

    // copy assignment
    Buffer& operator=(Buffer &b){
        this->capacity = b.capacity;
        data_ptr = new int[capacity];
        for(int i = 0; i < capacity; i++){
            data_ptr[i] = *(b.data_ptr + i);
        }
        return *this;
    }

    ~Buffer(){
        std :: cout <<"Destructor" << std :: endl;
        delete data_ptr;
    }

};
int main(){
   {    
        // inside scope to witness the destructor get activated
        Buffer storage= Buffer(5); // 1
        Buffer another(10);
        another = storage;  // invoked copy assignment
        storage.print();
        
        another.print();
        Buffer copyCons = storage; // 2
        /**
         * Doesn't statement 1 and 2 seem similar, YES, because they are
         * they both invoke constructors one default, other copy constructor
         * 
         */
        copyCons.print();
    }
    return 0;
}