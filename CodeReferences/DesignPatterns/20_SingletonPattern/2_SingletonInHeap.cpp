#include <iostream>
using namespace std;

// 힙에 만드는 싱글톤
// - 안드로이드 프레임워크가 사용하고 있는 싱글톤 입니다.


class Mutex
{
public:
    void lock() { cout << "Mutex lock" << endl; }
    void unlock() { cout << "Mutex unlock" << endl; }

    // 동기화 객체 사용시 예외가 발생하면 데드락의 확률이 있습니다.
    // 생성자/소멸자로 동기화 객체를 관리하면 편리하다.
    // RAII(Resource Acqusition Is Initialization) 라는 기술
    // - 편의성, 예외 안정성
    // http://occamsrazr.net/tt/297 참고
    
    class AutoLock
    {
    public:
        inline AutoLock(Mutex& m)
            : mLock(m)
        {
            mLock.lock();
        }

        inline ~AutoLock()
        {
            mLock.unlock();
        }

    private:
        Mutex& mLock;
    };

};


#include <mutex>        // lock_guard 존재


class Cursor
{
private:
    Cursor() {}
    Cursor(const Cursor&);
    void operator=(const Cursor&) = delete;

    static Mutex sLock;
    static Cursor* sInstance;
public:
    static Cursor& get_instance()
    {
        //sLock.lock();
        //*
        Mutex::AutoLock al(sLock);
        /*/
        lock_guard<Mutex> al(sLock);
        //*/
        if (sInstance == 0)
        {
            sInstance = new Cursor; // std::bad_alloc 예외가 발생 
                                    // 할 수 있습니다.

        }
        //sLock.unlock();

        return *sInstance;
    }

};

// static member variable은 반드시 외부에 정의해서 초기화 해야 한다.
Mutex Cursor::sLock;
Cursor* Cursor::sInstance = 0;

int main()
{
    Cursor& c1 = Cursor::get_instance();
    Cursor& c2 = Cursor::get_instance();

    cout << &c1 << endl;
    cout << &c2 << endl;
}