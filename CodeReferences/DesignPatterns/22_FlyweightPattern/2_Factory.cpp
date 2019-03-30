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
    ~Image() {}

    void draw()
    {
        cout << "Draw Image : " << url << endl;
    }
private:
    Image(const string& s)
        : url(s)
    {
        cout << "Loading from " << url << endl;
        Sleep(3000);
    }
    string url;

    friend class ImageFactory;
};



// 구현하는 방법
// 1. 팩토리: 객체를 만드는 역활을 수행하는 것

// Image 객체를 만드는 공장
// - 객체의 생성을 한 곳에서 중앙 집중적으로 관리할 수 있다.

#include <map>

class ImageFactory
{
    // 공장은 싱글톤인 경우가 많다.
    map<string, Image*> cache;
public:
    static ImageFactory& get_instance() {
        static ImageFactory instance;
        return instance;
    }

    Image* create_image(const string& url)
    {
        if (cache[url] == 0)
        {
            cache[url] = new Image(url);
        }

        //return new Image(url);
        return cache[url];
    }

private:
    ImageFactory() {}
    ImageFactory(const ImageFactory&) = delete;
    void operator=(const ImageFactory&) = delete;
};


int main()
{
    ImageFactory& factory = ImageFactory::get_instance();

    Image* image1 = factory.create_image("http://www.a.com/a.png");
    image1->draw();
    Image* image2 = factory.create_image("http://www.a.com/b.png");
    image2->draw();

    system("pause");
    return 0;
}