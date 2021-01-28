int main()
{
	int n = 10;

	// ������ ������ ��� ������
	auto a1 = n;	// ok
	auto a2 = 10;	// ok

	auto& a3 = n;	// ok
	auto& a4 = 10;	// error

	// �ٽ� . auto �� �׻� T�� �����մϴ�.
	// auto&& �� �ᱹ T&& �� �ǹ� �Դϴ�
	// T&&  arg = �Լ� ����;
	// auto&& a = �캯
	auto&& a5 = n;	// auto : int&    auto&& : int& &&    int& a5 = n;
	auto&& a6 = 10; // auto : int     auto&& : int&&      int&& a6 = 10;

	// �ٽ� : auto&& �� "forwarding reference" �Դϴ�.

//	auto a5 = n; // �̷��� �ϸ� int a5 = n;
}

//template<typename T> void foo(T&& arg) {}
//foo(n); // T : int&