#include <iostream>
using namespace std;

template<typename T,
         typename Allocator = allocator<T> >
class vector
{
private:
    /* data */
    Allocator ax;
public:
    void push_back(const T &a)
    {
        // memory allcoation
        // new, malloc, shared_memory, memory pool, system call, ...
        T* p = ax.allocate(1);

        ax.deallocate(p, 1);
    }
};

int main()
{
    vector<int/*, MyAlloc*/> v;

    v.push_back(10);

    return 0;
}


