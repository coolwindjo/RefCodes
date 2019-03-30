#include <iostream>

using namespace std;

// 1. 카메라 사용자와 카메라 제작자 사이의 규칙을 먼저 설계 하자.
//      - 인터페이스, 계약서, 프로토콜

#if 0
// 강한 결합: 교체가 불가능한 형태의 경직된 설계 방식
class SmartPhone
{
public:
    void take()
    {
        cout << "take photo with Smart Phone" << endl;
    }
};

class Camera
{
public:
    void take()
    {
        cout << "take photo with Camera" << endl;
    }
};

class Person
{
public:
    void take_photo(SmartPhone* p)
    {
        p->take();
    }
    void take_photo(Camera* p)
    {
        p->take();
    }
};
#endif

// C++에서 Interface를 만드는 방법
struct ICamera
{
    virtual void take() = 0;
    virtual ~ICamera() {}   // Interface도 결국 Parent class이므로,
                            // 반드시 Virtual destructor가 필요하다.
    //virtual void save() = 0;  // Interface에 기능을 추가하면 모든 Derived Class에도 구현해 주어야 한다.
    virtual void save() {}  // Default Method 기능을 이용하면, DC에 구현해 주지 않아도 된다.
};

// 2. 사용자는 진짜 카메라는 없지만 규칙이 있다. 규칙대로만 사용하면 된다.
class Person
{
public:
    void take_photo(ICamera* p)
    {
        p->take();
    }
};

// 3. 카메라의 제작자는 interface로 약속된 함수를 제공하는 형태의 구체 클래스를 만들면 된다.

// 규칙: 모든 카메라는 ICamera 로부터 Deriving되어야 한다. 가 아니라,
//      모든 카메라는 ICamera 를 구현해야 한다. 라고 표현한다.
class Camera : public ICamera
{
public:
    virtual void take()
    {
        cout << "take picture with Camera" << endl;
    }
};

// 4. 느슨한 결합: Client가 구체 Class에 의존하는 것이 아니라
//                  Abstract class나 interface에 의존하는 형태의 설계방법
//                  DIP (Dependency Inversion Principal)
//                  => 사용자는 interface를 만족하는 구체 Class를 교체할 수 있다.
//                  => 교체가능한 유연한 디자인
//                  => OCP를 만족한다.
class SmartPhone : public ICamera
{
public:
    virtual void take()
    {
        cout << "take photo with Smart Phone" << endl;
    }
};

int main()
{
    Camera camera;
    Person person;

    system("pause");
    return 0;
}

