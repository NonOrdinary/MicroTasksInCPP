
/**
 * Important : We can access any field of any object of same classes, even if they are private
 * Because here below we can access arr  and size even thought they are private, but we can 
 * because the class we are writing and object class are SAME.
 * 
 * noexcept : Good for creating trust ~ Nice practice
 * 
 * Task 1: Add move constructor to your Buffer

Take your current raw-pointer Buffer class and add a move constructor.

Requirements:

take Buffer&&
steal the pointer from the source object
leave the source object in a valid empty state
print "Move Constructor" when it runs

Test it with code like:

Buffer a(5);
Buffer b(std::move(a));

After the move:

b should own the array
a should not crash when destroyed
a should be safe to print if your empty-state logic supports that
 */
#include <iostream>
class Buffer
{
    int *arr = nullptr;
    size_t size;

public:
    Buffer(size_t N) : size(N)
    {
        arr = new int[this->size];
        for (int i = 0; i < N; i++)
        {
            arr[i] = 1;
        }
    }
    // move constructor
    // noexcept : guarantees that this function shall never throw exception
    Buffer(Buffer &&b) noexcept
    {
        this->arr = b.arr;
        this->size = b.size;
        // reset
        b.arr = nullptr;
        b.size = 0;
    }

    Buffer &operator=(Buffer &&other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] arr; // release current resource

        arr = other.arr; // steal
        size = other.size;

        other.arr = nullptr; // leave source valid
        other.size = 0;

        return *this;
    }

    void put(int index, int val)
    {
        arr[index] = val;
    }

    void print() const
    {
        for (int i = 0; i < this->size; i++)
        {
            std ::cout << arr[i] << " ";
        }
        std ::cout << std ::endl;
    }
};

int main()
{
    Buffer b(10);
    b.put(3, 19);
    Buffer a(std::move(b));
    a.print();
    b.print(); // unsafe

    Buffer c(15);
    c = std ::move(a);
    c.print();
    c = std ::move(c);
    c.print();

    return 0;
}