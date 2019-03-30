// Flyweight 
#include <iostream>
#include <string>
#include <Windows.h>    // Sleep(ms)

using namespace std;



// Flyweight pattern
// 의도: 속성이 동일한 객체는 공유하자!

// 구현하는 방법
// 1. Factory
// 2. Static Factory Method



class Image
{
public:
    Image(const string& s)
        : url(s)
    {
        cout << "Loading from " << url << endl;
        Sleep(3000);
    }
    ~Image() {}

    void draw()
    {
        cout << "Draw Image : " << url << endl;
    }
private:
    string url;
};


int main()
{
    Image* image1 = new Image("http://www.a.com/a.png");
    image1->draw();
    Image* image2 = new Image("http://www.a.com/b.png");
    image2->draw();

    system("pause");
    return 0;
}