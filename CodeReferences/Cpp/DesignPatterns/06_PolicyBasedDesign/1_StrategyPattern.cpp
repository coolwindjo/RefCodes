#include <iostream>
using namespace std;

// ����ȭ ���θ� Interface based Class�� �и��Ѵ�. (Strategy Pattern)
// ����: ���� �ð��� ��å�� ��ü�� �� �ִ�. - set_sync()
// ����: Virtual function based �̹Ƿ� ������.
struct ISync
{
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual ~ISync() {}
};

class MultiThread : public ISync
{
public:
    virtual void lock()
    {
        cout << "Mutex Lock" << endl;
    }
    virtual void unlock()
    {
        cout << "Mutex Unlock" << endl;
    }
};

class SingleThread : public ISync
{
public:
    virtual void lock() {}
    virtual void unlock() {}
};

template <typename T>
class List
{
    ISync* pSync;
public:
    List() :pSync(0) {
        if (pSync == 0)
        {
            pSync = new SingleThread;
        }
    }
    void set_sync(ISync* p)
    {
        pSync = p;
    }
    void push_front(const T& a) 
    {
        // mutex lock
        pSync->lock();
        //...
        // mutex unlock
        pSync->unlock();

    }
};

List<int> st; // ���� ����

int main()
{
    st.set_sync(new MultiThread);

    st.push_front(10);

    st.set_sync(new SingleThread);

    st.push_front(20);

    system("pause");
    return 0;
}

