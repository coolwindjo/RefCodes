#include <iostream>

template<typename T> struct default_delete
{
	default_delete() = default;

	template<typename U,
		std::enable_if_t< std::is_convertible_v<T*, U*>, int> = 0>
		default_delete(const default_delete<U>&) {}

	inline void operator()(T* p) noexcept
	{
		static_assert(sizeof(T) > 0, "error, delete incomplete type");
		delete p;
	}
};

int main()
{

}








