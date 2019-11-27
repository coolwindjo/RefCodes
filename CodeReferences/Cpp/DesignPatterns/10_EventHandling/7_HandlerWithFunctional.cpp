#include <iostream>
using namespace std;

class Dialog
{
public:
    void close() { cout << "Dialog close" << endl; }
};

void foo() { cout << "foo" << endl; }

#include <functional>   // 이미 표준에 범용적 함수 포인터가 있다.
                        // C++ 11 표준
                        // TR1 - 2008년도에 추가됨

#if 0
int main()
{
    function<void()> f = &foo;
    f();

    Dialog dialog;
    f = bind(&Dialog::close, &dialog);
    f();

    system("pause");
    return 0;
}
#endif

void goo(int n) { cout << "goo" << n << endl; }
void hoo(int a, int b) { cout << "hoo" << a << b << endl; }
void koo(int a, int b, int c, int d) { cout << "koo" << a << b << c << d << endl; }

#if 0
int main()
{
    function<void()> f = &foo;
    f();

    f = bind(&goo, 10);
    f();
    f = bind(&hoo, 10, 20);
    f();
    f = bind(&koo, 10, 20, 30, 40);
    f();

    system("pause");
    return 0;
}
#endif

using namespace std::placeholders;

#if 0
int main()
{
    function<void(int)> f = &goo;
    f(10);

    f = bind(&hoo, 10, _1);
    f(300);

    f = bind(&koo, 10, _1, 30, _1);
    f(20);

    system("pause");
    return 0;
}
#endif

int main()
{
    function<void(int, int)> f;

    f = bind(&koo, _2, _1, _1, _2);
    f(10, 20);

    system("pause");
    return 0;
}
