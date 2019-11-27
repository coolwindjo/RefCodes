// Static Factory Method - recommanded
// Flyweight 
#include <iostream>
#include <string>
#include <Windows.h>    // Sleep(ms)

using namespace std;

// 2. Static Factory Method - Effective Java
//  : ���� ��� ���� ���丮 �޼ҵ带 ���ؼ� �ش��ϴ� ������
//    �ذᰡ���ϴ�.

// ���� ���丮 �޼ҵ� - �������� �Ѱ�
// 1. ������ �̸��� ������ Ŭ���� �̸��� �����ϴ�.
//     Image(string path), Image(string url)
//   - �����ε��� �Ѱ踦 �غ��� �� �ִ�.

// 2. ���� �������� ������ �� �ִ�.
//    Color(int r, int g, int b) {}
//    static Color* newRedColor() 
//    { return new Color(255, 0, 0); }

//    Color* red = new Color(255, 0, 0);
//    Color* red = Color::newRedColor();

// 3. ��ü�� �����ϴ� ��å�� ������ �� �ִ�.
//    - new: ���ο� ��ü�� �����Ѵ�.
//    - ���� ���丮 �޼ҵ�: �̱���, �ö��̿���Ʈ, ������ �̱���

// 4. Ȱ��
// List<Integer> arr = new ArrayList<>();
// for (int i = 0 ; i < 100 ; ++i)
//    arr.add(i); -> arr.add(Integer.valueOf(i));


//-------------------------------------------------------------


// �߿�: ��ü�� [�Һ� ��ü]�� �����ؾ� �Ѵ�.
// Object�� ���������� ����Ǹ� Copy or Write ����� ������ �־�� �Ѵ�. ??
// 


#include <map>

class Image
{
public:
    ~Image() {}
    static Image* image_with_url(const string& url)
    {
        if (cache[url] == 0)
        {
            cache[url] = new Image(url);
        }
        return cache[url];
    }

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
    static map<string, Image*> cache;
};

map<string, Image*> Image::cache;

int main()
{
    Image* image1 = Image::image_with_url("http://www.a.com/a.png");
    image1->draw();
    Image* image2 = Image::image_with_url("http://www.a.com/b.png");
    image2->draw();

    system("pause");
    return 0;
}