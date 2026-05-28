#include<iostream>
#include<vector>


class arena{
    // data membe
    size_t offset; // the position of new segment
    // a modern allocator with vector of c++, this manages space overhead thing
    // we don't need to give a shit about what happens when we run out of space
    std :: vector<std::byte>buffer;
    size_t totalSize;

    public:
    // constructor
    arena(size_t totalSize) : totalSize(totalSize*2), offset(0){
        buffer.resize(this->totalSize);
    }
    // destructor : default though

    // a copy constructor
    arena (const arena& a) = delete;
    // a copy assignment : we return the reference to left side object that's why arena (&) ,it is to support chaining
    arena& operator=(const arena &a) = delete;

    // a move constructor
    arena (arena && a) = delete;
    // a move assignment : we return the reference to left side object that's why arena (&)
    arena& operator=(arena && a) = delete;

    void* allocate(size_t requestedSize){
        // // we actually cannot use this, because all pointers will be lost
        // // so what we do is intialise with atleast 2 *totalSize intially for better storage handling
        // while(offset + requestedSize > totalSize) {
        //     buffer.resize(totalSize * 2LL);
        //     totalSize *= 2;
        // }
        
        // we return void pointer because arena allocator is actually a generic type of storage,
        // so we cannot return int* or byte *

        if(offset + requestedSize > totalSize)
            return nullptr;
        void *start = buffer.data() + offset;  // we cannot use buffer.begin() because .begin() is an iterator
        offset += requestedSize;
        return start;
    }
    void reset(size_t newSize = -1){
        if(newSize != -1){
            buffer.resize(newSize * 2);
            totalSize = newSize * 2;
        }
        offset = 0;
    }
};