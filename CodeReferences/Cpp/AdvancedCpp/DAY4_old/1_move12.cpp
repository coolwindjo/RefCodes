#include "cppmaster.h"
//using namespace std;

class Data
{
public:
	Data() = default;
	Data(const Data& d) { LOG_FUNCTION_NAME(); }
	Data& operator=(const Data&) { LOG_FUNCTION_NAME(); return *this; }
	Data(Data&& d) { LOG_FUNCTION_NAME(); }
	Data& operator=(Data&&) { LOG_FUNCTION_NAME(); return *this; }
};

// �ٽ� 1. ���ø� ���鶧  "T&" �� ����  "T&&" �� ���� �� �Ǵ��ϼ���
// T&  : lvalue �� �ްڴ�.
// T&& : lvalue �� rvalue�� ��� �ްڴٴ°�  

// std::move() �Լ��� ���� ����� ���ô�.
/*
template<typename T> T&& move(T& obj)
{
	return static_cast<T&&>(obj);
}
*/

// ���ڰ� T&& �϶�
// lvalue(d1)�� �����ϸ� T �� "Data&" �� �ȴٴ� ���� ���� �߿��մϴ�.
// static_cast<T&&>(obj) => static_cast<Data& &&>(obj) => static_cast<Data&>(obj)

template<typename T> std::remove_reference_t<T>&& move(T&& obj)
{
	// �Ʒ� ĳ������ "lvalue �� move�� �����ϸ� lvalue�� ĳ����"
	//               "rvalue �� move�� �����ϸ� rvalue�� ĳ����"
	//return static_cast<T&&>(obj);
	// �Ʒ� ĳ������ ������ "rvalue" �� ĳ�����ϴ� �ڵ��Դϴ�.
	return static_cast<std::remove_reference_t<T>&&>(obj);
}
template<typename T> 
//std::conditional_t< std::is_nothrow_move_constructible_v<T> , T&&, const T&> 
std::conditional_t< !std::is_nothrow_move_constructible_v<T> && std::is_copy_constructible_v<T>, const T&, T&&>
move_if_noexcept(T& obj)
{
	return move(obj); // ������ ���� move �ٽ� ȣ��.
					  // �ᱹ Data&&  Ÿ������ ��ȯ���� ���� �ȴ�
}

int main()
{
	Data d1;
	Data d2 = d1;				// ����
	Data d3 = std::move(d1);	// move 
	Data d4 = move(d1);			// move 		

	Data d5 = move(  Data() ); // �Ǿ�� �ұ�� ? �ȵǾ� �ұ�� ?

	Data d6 = move_if_noexcept( d2 );
				// if ( d2 �� move �����ڰ� ���ܰ� ������ )
				//    static_cast<Data&&>(d2);		// move ������ ȣ��
				// else 
				//    static_cast<const Data&>(d2); // ���� ������ ȣ��
}






