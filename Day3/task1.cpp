/**
 * Task 1: Make your raw-pointer class safely copyable

Take the Buffer / DIA style class from Day 1 and add:

copy constructor
copy assignment operator
destructor

Requirements:

deep copy the array
each object must own its own memory
changing one object must not affect the other
print messages in each special member so you can see which one runs
 */
/**
 * learning :
 * Const object when used inside a function only grant access to const member functions
 */

#include<iostream>

class Buffer{
    int N;

    int *arr = nullptr;
    public:
    Buffer(int N){
        this->N = N;
        arr = new int[N];
        for(int i = 0; i < N; i++){
            arr[i] = 1;
        }

    }

    Buffer (const Buffer &b){
        this->N = b.size();
        this -> arr = new int[N];
        for(int i = 0; i < N; i++){
            arr[i] = b.get(i);
        }
    }

    Buffer& operator=(const Buffer& b){
        this->N = b.size();
        if(this == &b){
            // same objects
            return *this;
        }

        delete[] arr;
        arr = new int[N];
        for(int i = 0; i < N; i++){
            arr[i] = b.get(i);
        }
        return *this;
    }
    ~Buffer(){
        delete[] arr;
    }
    void print(){
        for(int i = 0; i < N; i++){
            std :: cout << arr[i] <<" ";
        }
        std :: cout << std :: endl;
    }


    int get(int index)const {
        if(index >= N){
            return -1;
        }
        return arr[index];
    }

    void put(int index,int val){
        if(index >= N) return;
        arr[index] = val;
    }
    size_t size()const{
        return N;
    }
};
int main(){
    Buffer a{5},b{6},c{10};
    a.print();
    b.print();
    c.print();
    b.put(3,20);
    a = b;
    a.print();

}