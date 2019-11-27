// 1_���� ������
#include <iostream>
using namespace std;

// 1. �����ڿ��� ���и� �˸��� ����� ���� �ۿ� ����.
// 2. �����ڿ��� ���ܰ� �߻��ϸ� �Ҹ��ڰ� ȣ����� �ʴ´�.

// ��� ����
// - Exceptional C++
// - More Exceptional C++
// - Exceptional C++ Style

// Exception Safety
// 1. ���� ����: ���ܰ� ����.
// 2. ���� ����: ���ܰ� �߻��ص� ���� ���, ��ü ���´� ���� �߻������� �����ȴ�.
//              => STL
// 3. �⺻ ����: ���ܰ� �߻��ص� �ڿ������� ����. 
//              ��, ��ü ���´� �� �� ���� ������ ����� �Ұ����ϴ�.


#include <memory>  // unique_ptr : smart pointer

class Image
{
public:
    Image() { cout << "Image constructed" << endl; }
    ~Image() { cout << "Image destructed" << endl; }
};


class Test
{
    unique_ptr<Image> p1;
    unique_ptr<Image> p2;
public:
    // ��� ������ Ÿ���� ��ü Ÿ���̶��, �����ڿ��� ���ܰ� �߻��Ͽ��� ���
    // ��� ������ �Ҹ����� ȣ���� ǥ�ؿ����� �����ϰ� �ִ�.
    Test() : p1(new Image), p2(new Image)
    {
        throw std::bad_alloc();
        // �� ���� �޸𸮰� �����߽��ϴ�. � ������ �������?
        // �޸𸮰� �����ϸ� bad_alloc �̶�� ���ܰ� �߻��մϴ�.
    }

    ~Test()
    {
        cout << "Destructor called" << endl;
    }
};

int main()
{
    try
    {
        Test t;
    }
    catch (...)
    {

    }

    system("pause");
    return 0;
}

