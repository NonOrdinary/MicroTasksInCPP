#include<iostream>
#include<vector>
#include <cstddef>
#include <new>
#include <utility>
#include <type_traits>

/** we can also add an align function to make sure that the memory is aligned to a certain boundary, for example 8 bytes
/* this helps in cache performance and also prevents undefined behavior when we try to access misaligned memory 
/* this will ensure int is aligned to 4 bytes, double is aligned to 8 bytes, etc 
/* we might have to pad the memory with some extra bytes to make sure that the next allocation is aligned to the desired boundary
*/

size_t align(size_t offset, size_t alignment){
    size_t misalignment = offset % alignment;
    if(misalignment == 0){
        return offset;
    }
    return offset + (alignment - misalignment);
}

class arena{
    // data membe
    size_t offset; // the position of new segment
    // a modern allocator with vector of c++, this manages space overhead thing
    // we don't need to give a shit about what happens when we run out of space
    std :: vector<std::byte>buffer;
    size_t totalSize;



    public:
    // following 
    // constructor 0 3 5 rule of CPP
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

    //default destructor is fine because vector will take care of memory management, because we aim
    // to store simple data types like int, double, etc, we don't need to worry about destructors of complex objects,
    // but if we want to store complex objects we might have to call their destructors manually when we reset the arena or when we want to free some memory,
    // but for now we will keep it simple and just store simple data types.
    
    template<typename T, typename... Args>
    T* create(Args&&... args){

        static_assert(
            std::is_trivially_destructible_v<T>,
            "arena only supports simple destructible types"
        );

        void* mem = allocate(sizeof(T), alignof(T));

        if(mem == nullptr)
            return nullptr;

        return new(mem) T(std::forward<Args>(args)...);
    }

    void* allocate(size_t requestedSize, size_t alignment){
        // // we actually cannot use this, because all pointers will be lost in resize
        // // so what we do is intialise with atleast 2 *totalSize intially for better storage handling
        // while(offset + requestedSize > totalSize) {
        //     buffer.resize(totalSize * 2LL);
        //     totalSize *= 2;
        // }
        
        // we return void pointer because arena allocator is actually a generic type of storage,
        // so we cannot return int* or byte *
        size_t alignedOffset = align(offset, alignment);

        if(alignedOffset > totalSize - requestedSize)
            return nullptr;
        
        
        void *start = buffer.data() + alignedOffset;  // we cannot use buffer.begin() because .begin() is an iterator
        offset = alignedOffset + requestedSize;    // offset is the position of new segment, so we need to move it by the size of the requested segment
        return start;
    }

    void reset(){
        offset = 0;
    }
    
    void reset(size_t newSize){
        
        buffer.resize(newSize * 2);
        totalSize = newSize * 2;
        offset = 0;
    }
    

};