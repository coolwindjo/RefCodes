// 교재에 없는 내용
// Builder -> 공정은 동일하지만 표현이 달라지는 객체를 만들 때 사용
//  => Object 생성의 방법

//  => Constructor Parameter가 많을 때 사용하면 좋음

#include <iostream>
using namespace std;
#include <string>

class UserInfo
{
public:
    // 방법 1. Telescoping Constructor Pattern
    //    : 점층적 생성자 패턴
#if 0
    UserInfo(string i, string a)
        : id(i)
        , address(a)
    {}
    UserInfo(string i, string a, int l)
        : id(i)
        , address(a)
    {}
    UserInfo(string i, string a, int l, int g)
        : id(i)
        , address(a)
        , level(l)
    {}
    UserInfo(string i, string a, int l, int g, int c)
        : id(i)
        , address(a)
        , level(l)
        , cash(c)
    {}

    UserInfo(string i, string a, int l, int g)
    {
        // this(i, a, l, g, 0); - 생성자 위임 기능 in java
    }
#endif
    UserInfo(string i, string a)
        : UserInfo(i, a, 0, 0, 0) {}
    UserInfo(string i, string a, int l)
        : UserInfo(i, a, l, 0, 0) {}
    UserInfo(string i, string a, int l, int g)
        : UserInfo(i, a, l, g, 0) // C++11 Delegating Constructor
    {}

    UserInfo(string i, string a, int l, int g, int c)
        : id(i), address(a), level(l), gold(g), cash(c) {}

    ~UserInfo() {}

private:
    const string id;        // 필수 인자
    const string address;
   
    int level;              // 선택 인자
    int gold;
    int cash;
};

int main()
{
    UserInfo ui("i","a");
    // 이 방법으로 객체를 생성할 때는 설정하려는 인자 개수에 맞는
    // 생성자를 선택해서 생성하면 된다.
    UserInfo ui("chansik.yun", "수원", 0, 1000, 100000);
        // 문제점 
        //   1) 가독성이 좋지 않다. 어떤 인자가 어떤 멤버를 초기화하는지
        //      알기 어렵다.
        //   2) 같은 타입의 인자에 대해서 순서를 바꿀 경우 컴파일 에러가
        //      발생하지 않습니다.

    system("pause");
    return 0;
}