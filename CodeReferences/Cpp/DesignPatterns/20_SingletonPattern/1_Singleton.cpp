// Singleton
#include <iostream>
using namespace std;

// 개념 : 오직 한개의 객체를 만들수 있고 어디에서도 동일한 방법으로 객체를
//        얻을 수 있게 하는 패턴.
//  - Chromium, Webkit, Firefox
class Cursor
{
public:
    //Cursor();
    ~Cursor();
    // 규칙 2. 오직 한 개만 만드는 static member function
    //  - Meyers의 Singleton
    static Cursor& get_instance()       // Thread Safety가 보장 되지 않음
    {
        static Cursor instance;
        // Cursor s = instance;

        return instance;
    }
private:
    Cursor();       // 규칙 1. private 생성자

    // 규칙 3. 복사와 대입 금지
    //  핵심: 선언만 한다. 구현이 없다!
    //Cursor(const Cursor&) {}
    //Cursor(const Cursor&);
    //void operator=(const Cursor&);

    // 위의 복사 금지 기법은 C++11에서 문법화 되었습니다.
    // "Delete function"이라는 문법
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

//Cursor c;         // 전역 객체를 사용하면 안된다!!
                    // Compiler 마다 module별로 Compile하는 시점이 일치하지 않아서
                    // 생성과 소멸의 시점이 명확하게 정의되어 있지 않다.

int main()
{
    // Cursor::get_instance();  // Thread Safety를 보장하기 위해서 시작하자마자
                                // 하나 생성 해놓고 시작한다.
                                // 최신 Compiler는 Thread Safety 보장해준다.

    Cursor& c1 = Cursor::get_instance();
    Cursor& c2 = Cursor::get_instance();

    cout << &c1 << endl;
    cout << &c2 << endl;

    //Cursor c3 = Cursor::get_instance();     // 복사, 대입
    //cout << &c3 << endl;

    system("pause");
    return 0;
}