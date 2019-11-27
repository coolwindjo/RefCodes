// 5_싱글톤4 using CRTP
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

// 싱글톤을 만드는 로직은 항상 동일합니다.
// 부모 클래스로 제공하면 편리하게 사용할 수 있습니다.
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

// static 멤버 변수는 반드시 외부에 정의를 해야 합니다.
template <typename TYPE> Mutex   Singleton<TYPE>::sLock;
template <typename TYPE> TYPE* Singleton<TYPE>::sInstance = 0;

class Cursor : public Singleton<Cursor>
{
    // 외부에서 생성하지 못하도록 private으로 만든다.
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