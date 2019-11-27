// Flyweight 
#include <iostream>
#include <string>
#include <Windows.h>    // Sleep(ms)

using namespace std;

// Flyweight pattern
// �ǵ�: �Ӽ��� ������ ��ü�� ��������!

// �����ϴ� ���
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



// �����ϴ� ���
// 1. ���丮: ��ü�� ����� ��Ȱ�� �����ϴ� ��

// Image ��ü�� ����� ����
// - ��ü�� ������ �� ������ �߾� ���������� ������ �� �ִ�.

#include <map>

class ImageFactory
{
    // ������ �̱����� ��찡 ����.
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