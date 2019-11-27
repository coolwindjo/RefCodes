
#include <iostream>
using namespace std;

// �Ʒ� ������ CRTP�� �̿��ؼ� ���� �ٸ� ���� ������ ����ϴ� ����Դϴ�.

// ��ü�� ������ N���� �����ϴ� ���
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
        cout << "��ü ���� ����" << endl;
    }
}