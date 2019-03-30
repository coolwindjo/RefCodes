// Singleton
#include <iostream>
using namespace std;

// ���� : ���� �Ѱ��� ��ü�� ����� �ְ� ��𿡼��� ������ ������� ��ü��
//        ���� �� �ְ� �ϴ� ����.
//  - Chromium, Webkit, Firefox
class Cursor
{
public:
    //Cursor();
    ~Cursor();
    // ��Ģ 2. ���� �� ���� ����� static member function
    //  - Meyers�� Singleton
    static Cursor& get_instance()       // Thread Safety�� ���� ���� ����
    {
        static Cursor instance;
        // Cursor s = instance;

        return instance;
    }
private:
    Cursor();       // ��Ģ 1. private ������

    // ��Ģ 3. ����� ���� ����
    //  �ٽ�: ���� �Ѵ�. ������ ����!
    //Cursor(const Cursor&) {}
    //Cursor(const Cursor&);
    //void operator=(const Cursor&);

    // ���� ���� ���� ����� C++11���� ����ȭ �Ǿ����ϴ�.
    // "Delete function"�̶�� ����
    Cursor(const Cursor&) = delete;
    void operator=(const Cursor&) = delete;

    // in Java 1.5
    // static final Cursor INSTANCE = new Cursor();
    // Lazy Initialization

};

Cursor::Cursor()
{
}

Cursor::~Cursor()
{
}

//Cursor c;         // ���� ��ü�� ����ϸ� �ȵȴ�!!
                    // Compiler ���� module���� Compile�ϴ� ������ ��ġ���� �ʾƼ�
                    // ������ �Ҹ��� ������ ��Ȯ�ϰ� ���ǵǾ� ���� �ʴ�.

int main()
{
    // Cursor::get_instance();  // Thread Safety�� �����ϱ� ���ؼ� �������ڸ���
                                // �ϳ� ���� �س��� �����Ѵ�.
                                // �ֽ� Compiler�� Thread Safety �������ش�.

    Cursor& c1 = Cursor::get_instance();
    Cursor& c2 = Cursor::get_instance();

    cout << &c1 << endl;
    cout << &c2 << endl;

    //Cursor c3 = Cursor::get_instance();     // ����, ����
    //cout << &c3 << endl;

    system("pause");
    return 0;
}