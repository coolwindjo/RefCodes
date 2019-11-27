// 인라인 함수와 함수 포인터의 이야기
// VS2015용 개발자 명령 프롬프트
// cl 4_FunctionAndStrategy_2.cpp /FAs /Ob1
// Assembly 파일 만들기 /FAs
// inline : 최적화 명령 /Ob1
// 예외처리모드 지정 /EHsc

// gcc에서는 inline 최적화 명령이 -O2 이다.

// 1. inline 치환은 Compile 시간 문법
// 2. inline function이라도 funtion pointer에 담아서 호출하면 inline 치환 될 수 없다.
//      (function pointer는 결국 변수이다. 실행시간에 변경될 수 있다.)
int add1(int a, int b)
{
    return a + b;
}
inline int add2(int a, int b)
{
    return a + b;
}

int main()
{
    int n1 = add1(10, 20);  // 호출
    int n2 = add2(10, 20);  // 치환

    int (*f)(int, int) = &add2;
    f(10, 20);              // 호출
}