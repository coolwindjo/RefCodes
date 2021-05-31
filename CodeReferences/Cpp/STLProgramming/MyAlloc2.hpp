#include <cstddef>

template<typename T>
class MyAlloc
{
public:
    using value_type = T;

    MyAlloc() noexcept {}

    template<typename U>
    MyAlloc(const MyAlloc<U>&) noexcept {}

    T* allocate(std::size_t num)
    {
#if 1
        std::cout << typeid(T).name() <<std::endl;
        std::cout << "size: " << num <<std::endl;
#endif
        return static_cast<T*>(::operator new(sizeof(T) * num));
    }
    void deallocate(T* p, std::size_t num)
    {
#if 1
        std::cout << "delete: " << num <<std::endl;
#endif
        ::operator delete(p);
    }
};
template <class T1, class T2>
bool operator== (const MyAlloc<T1>&, const MyAlloc<T2>&) noexcept
{
	return true;
}
template <class T1, class T2>
bool operator!= (const MyAlloc<T1>&, const MyAlloc<T2>&) noexcept
{
	return false;
}
