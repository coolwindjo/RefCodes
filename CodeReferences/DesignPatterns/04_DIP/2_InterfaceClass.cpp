#include <iostream>

using namespace std;

// 1. ī�޶� ����ڿ� ī�޶� ������ ������ ��Ģ�� ���� ���� ����.
//      - �������̽�, ��༭, ��������

#if 0
// ���� ����: ��ü�� �Ұ����� ������ ������ ���� ���
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

// C++���� Interface�� ����� ���
struct ICamera
{
    virtual void take() = 0;
    virtual ~ICamera() {}   // Interface�� �ᱹ Parent class�̹Ƿ�,
                            // �ݵ�� Virtual destructor�� �ʿ��ϴ�.
    //virtual void save() = 0;  // Interface�� ����� �߰��ϸ� ��� Derived Class���� ������ �־�� �Ѵ�.
    virtual void save() {}  // Default Method ����� �̿��ϸ�, DC�� ������ ���� �ʾƵ� �ȴ�.
};

// 2. ����ڴ� ��¥ ī�޶�� ������ ��Ģ�� �ִ�. ��Ģ��θ� ����ϸ� �ȴ�.
class Person
{
public:
    void take_photo(ICamera* p)
    {
        p->take();
    }
};

// 3. ī�޶��� �����ڴ� interface�� ��ӵ� �Լ��� �����ϴ� ������ ��ü Ŭ������ ����� �ȴ�.

// ��Ģ: ��� ī�޶�� ICamera �κ��� Deriving�Ǿ�� �Ѵ�. �� �ƴ϶�,
//      ��� ī�޶�� ICamera �� �����ؾ� �Ѵ�. ��� ǥ���Ѵ�.
class Camera : public ICamera
{
public:
    virtual void take()
    {
        cout << "take picture with Camera" << endl;
    }
};

// 4. ������ ����: Client�� ��ü Class�� �����ϴ� ���� �ƴ϶�
//                  Abstract class�� interface�� �����ϴ� ������ ������
//                  DIP (Dependency Inversion Principal)
//                  => ����ڴ� interface�� �����ϴ� ��ü Class�� ��ü�� �� �ִ�.
//                  => ��ü������ ������ ������
//                  => OCP�� �����Ѵ�.
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

