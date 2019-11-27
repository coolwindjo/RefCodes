
#include <iostream>
using namespace std;

// 아래 예제는 CRTP를 이용해서 서로 다른 정적 변수를 사용하는 기술입니다.

// 객체의 생성을 N개로 제한하는 기술
template <typename T, int N>
//class Mouse
class LimitMaxObject
{
    static int n;
public:
    LimitMaxObject()
    {
        //if (++n > 5)
        if (++n > N)
            throw 1;
    }
};

template<typename T, int N>
int LimitMaxObject<T, N>::n = 0;

class Mouse : public LimitMaxObject<Mouse, 5>
{
public:
    Mouse() {}
    ~Mouse() {}

private:

};

class Keyboard : public LimitMaxObject<Keyboard, 5>
{
public:
    Keyboard() {}
    ~Keyboard() {}

private:

};

int main()
{
    try {
        Mouse m[6];
        Keyboard k[6];
    }
    catch (...) {
        cout << "객체 생성 실패" << endl;
    }
}