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

    // MFC, Android Framework에서도 많이 사용
    int call_f3()
    {
        return this ? f3() : NULL;  // this가 NULL이 되는 것은 아래처럼,
                                    // Memory Allocation Failure가 일어나서 0이 할당될 때...
                                    // Clang에서는 this가 NULL인 것은 Warning 발생시킨다.
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