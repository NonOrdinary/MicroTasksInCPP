// Task 1: Build a Buffer class with raw memory

// Write a class that owns a dynamic integer array.

// Requirements:

// constructor takes size
// allocates size integers
// fills them with values 1..size
// prints the values using a member function
// destructor releases memory

// Extra:

// // print messages in constructor and destructor so you can see when they run

/*
// Allocate Heap memory
    int* array = new int[10];

    // Deallocate Heap memory
    delete[] array;*/
    
#include<iostream>

class DIA{
    const std :: size_t capacity;
    int *data_ptr;
    public:
    DIA(const std :: size_t & s_N) : capacity(s_N){
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
    ~DIA(){
        std :: cout <<"Destructor" << std :: endl;
        delete data_ptr;
    }

};
int main(){
   {    
        // inside scope to witness the destructor get activated
        DIA storage= DIA(5);
        storage.print();
        storage.put(4,1);
        storage.print();
    }
    return 0;
}