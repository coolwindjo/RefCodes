// 5_�̱���4 using CRTP
#include <iostream>
using namespace std;

class Mutex
{
public:
    void lock() { cout << "Mutex lock" << endl; }
    void unlock() { cout << "Mutex unlock" << endl; }

    class AutoLock
    {
        Mutex& mLock;
    public:
        inline AutoLock(Mutex& m) : mLock(m) { mLock.lock(); }
        inline ~AutoLock() { mLock.unlock(); }
    };
};

// �̱����� ����� ������ �׻� �����մϴ�.
// �θ� Ŭ������ �����ϸ� ���ϰ� ����� �� �ֽ��ϴ�.
template <typename TYPE>
class Singleton
{
protected:
    Singleton() {}

private:
    Singleton(const Singleton&);
    void operator=(const Singleton&) = delete;

    static Mutex   sLock;
    static TYPE* sInstance;
public:
    static TYPE& get_instance()
    {
        Mutex::AutoLock al(sLock);

        if (sInstance == 0)
            sInstance = new TYPE;

        return *sInstance;
    }
};

// static ��� ������ �ݵ�� �ܺο� ���Ǹ� �ؾ� �մϴ�.
template <typename TYPE> Mutex   Singleton<TYPE>::sLock;
template <typename TYPE> TYPE* Singleton<TYPE>::sInstance = 0;

class Cursor : public Singleton<Cursor>
{
    // �ܺο��� �������� ���ϵ��� private���� �����.
private:
    Cursor(){}

    friend class Singleton<Cursor>;

};


int main()
{
    //Cursor c;


    Cursor& c1 = Cursor::get_instance();
    Cursor& c2 = Cursor::get_instance();

    cout << &c1 << endl;
    cout << &c2 << endl;

}