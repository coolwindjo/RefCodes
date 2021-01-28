void f1(int&  r) {}
void f2(int&& r) {}
template<typename T> void f3(T& a)
{
}

template<typename T> void f4(T&& a)
{
}

int main()
{
    int n = 10;

/*/
    f3<int>(n);     // T: int   T&: int&    Resultant: void f3(int& a)
    f3<int&>(n);    // T: int&  T&: int& &  Resultant: void f3(int& a)
    f3<int&&>(n);   // T: int&& T&: int&& & Resultant: void f3(int& a)
/*/
    // 1. 사용자가 Type을 전달할 때
    f4<int>(10);    // T: int   T&&: int&&    Resultant: void f4(int&& a)
    f4<int&>(n);    // T: int&  T&&: int& &&  Resultant: void f4(int& a)
    f4<int&&>(10);   // T: int&& T&&: int&& && Resultant: void f4(int&& a)

    // 2. 사용자가 Type을 전달하지 않으면,
    //      인자를 보고 함수를 생성할 수 있도록 T를 결정
    f4(n);    // T: int& 로 결정,  Resultant: void f4(int& a)
    f4(10);   // T: int  로 결정,  Resultant: void f4(int&& a)
//*/
    return 0;
}
