#include <iostream>
using namespace std;

// ���� ����� �̱���
// - �ȵ���̵� �����ӿ�ũ�� ����ϰ� �ִ� �̱��� �Դϴ�.


class Mutex
{
public:
    void lock() { cout << "Mutex lock" << endl; }
    void unlock() { cout << "Mutex unlock" << endl; }

    // ����ȭ ��ü ���� ���ܰ� �߻��ϸ� ������� Ȯ���� �ֽ��ϴ�.
    // ������/�Ҹ��ڷ� ����ȭ ��ü�� �����ϸ� ���ϴ�.
    // RAII(Resource Acqusition Is Initialization) ��� ���
    // - ���Ǽ�, ���� ������
    // http://occamsrazr.net/tt/297 ����
    
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


#include <mutex>        // lock_guard ����


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
            sInstance = new Cursor; // std::bad_alloc ���ܰ� �߻� 
                                    // �� �� �ֽ��ϴ�.

        }
        //sLock.unlock();

        return *sInstance;
    }

};

// static member variable�� �ݵ�� �ܺο� �����ؼ� �ʱ�ȭ �ؾ� �Ѵ�.
Mutex Cursor::sLock;
Cursor* Cursor::sInstance = 0;

int main()
{
    Cursor& c1 = Cursor::get_instance();
    Cursor& c2 = Cursor::get_instance();

    cout << &c1 << endl;
    cout << &c2 << endl;
}