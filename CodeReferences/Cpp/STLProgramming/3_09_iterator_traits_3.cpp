#include <iterator>	// for iterator_traits
using namespace std;

template<typename T>
void foo(T a)
{
	// T가 iterator일 때, iterator가 가리키는 type을 사용하고 싶다.
    typename T::value_type n1;

    typename iterator_traits<T>::value_type n2;
}
