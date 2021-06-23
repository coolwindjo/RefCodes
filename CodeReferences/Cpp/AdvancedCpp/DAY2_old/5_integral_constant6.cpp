#include <iostream>

#include <type_traits>

template<typename T> void foo(T a)
{
	// T�� ������ ���ο� ���� �ٸ� �˰����� �ۼ��ϰ� �ʹ�.
	// ��� 1. if �����

	if  (std::is_pointer_v<T>)
	{
		//....
		// ��, "*a" ǥ����� ����Ҽ� ����. 
	}
	else
	{
		//....
	}
	// ��� 2. "*a" ǥ����� �ʿ� �ߴٸ�... true_type/false_type�� ����� �Լ� �����ε����
	foo_imp(a, std::is_pointer<T>());
}
template<typename T> void foo_imp(T a, std::true_type) { }  // ������ �ΰ��
template<typename T> void foo_imp(T a, std::false_type) { } // �����Ͱ� �ƴ� ���



int main()
{

}