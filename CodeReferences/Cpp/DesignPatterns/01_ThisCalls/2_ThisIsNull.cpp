#include <iostream>

using namespace std;

class Sample
{
    int data;
public:
    void f1()   // f1(Sample *this)
    {
        cout << "f1" << endl;
    }
    int f2()    // f2(Sample *this)
    {
        cout << "f2" << endl;
        return 0;
    }

    // MFC, Android Framework������ ���� ���
    int call_f3()
    {
        return this ? f3() : NULL;  // this�� NULL�� �Ǵ� ���� �Ʒ�ó��,
                                    // Memory Allocation Failure�� �Ͼ�� 0�� �Ҵ�� ��...
                                    // Clang������ this�� NULL�� ���� Warning �߻���Ų��.
    }
    int call_f3_new(const Sample* spl)
    {
        if (spl == NULL) return NULL;
        return const_cast<Sample*>(spl)->f3();
    }

protected:
    int f3()    // f3(Sample *this)
    {
        cout << "f3" << endl;
        return data;
    }
};

int main()
{
    Sample *p = 0;  // Assign 0 due to the Memory allocation failure.

    p->f1();        // f1(p)
    p->f2();        // f2(p)
    //p->call_f3();
    p->call_f3_new(p);

    system("pause");
    return 0;
}