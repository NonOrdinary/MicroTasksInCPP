/**
 * Task 3: Rewrite the same class using std::unique_ptr

Make a second version of the class that stores its data with:

std::unique_ptr<int[]>

Requirements:

same behavior as before
no manual delete[]
keep the class non-copyable by default
optionally add move support later (that will never come)
 */

#include<iostream>
#include<memory>
#include<exception>

class Buffer{
    std :: unique_ptr<int[]>data_ptr;
    size_t capacity = 0;
    public:
    Buffer(const size_t cap): capacity(cap){
        // to make a unique pointer point to an array, the standard syntax
        // doesn't ask to intialise the object, rather just pass the capacity
        // when using make_unique, however if we didn't , we have to do something like
        // unique_ptr<int[]>data_ptr(new int[capacity])
        data_ptr = std ::make_unique<int[]>(capacity);  
        for(int i = 0; i < capacity; i++){
            data_ptr[i] = 1;
            // we cannot do (data_ptr + i)
            // because pointer arithmetic is banned in unique_ptr
        }
    }
    size_t size(){
        return this->capacity;
    }
    void put(int ele,int index){
        if(index >= capacity){
            std :: cout << "failed, index out of bounds " <<std:: endl;
            return;
        }
        data_ptr[index] = ele;
    }
    void print(){
        std :: cout<<"[ ";
        for(int i = 0; i < capacity; i++){
            std :: cout <<data_ptr[i] <<" ";
        }
        std :: cout <<"]" << std :: endl;
    }
    Buffer (const Buffer &b) = delete; // no copy constructor
    Buffer* operator=(const Buffer &b) = delete; // no copy assignment

};
int main(){
    Buffer b{7};
    b.print();
    b.put(9,1);
    b.put(10,8); // out_of_bounds surely
    b.print();
}