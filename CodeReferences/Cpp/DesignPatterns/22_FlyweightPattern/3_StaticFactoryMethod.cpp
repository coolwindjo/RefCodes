// Static Factory Method - recommanded
// Flyweight 
#include <iostream>
#include <string>
#include <Windows.h>    // Sleep(ms)

using namespace std;

// 2. Static Factory Method - Effective Java
//  : 공장 대신 정적 팩토리 메소드를 통해서 해당하는 문제를
//    해결가능하다.

// 정적 팩토리 메소드 - 생성자의 한계
// 1. 생성자 이름은 무조건 클래스 이름과 동일하다.
//     Image(string path), Image(string url)
//   - 오버로딩의 한계를 극복할 수 있다.

// 2. 좋은 가독성을 제공할 수 있다.
//    Color(int r, int g, int b) {}
//    static Color* newRedColor() 
//    { return new Color(255, 0, 0); }

//    Color* red = new Color(255, 0, 0);
//    Color* red = Color::newRedColor();

// 3. 객체를 생성하는 정책을 변경할 수 있다.
//    - new: 새로운 객체를 생성한다.
//    - 정적 팩토리 메소드: 싱글톤, 플라이웨이트, 스레드 싱글톤

// 4. 활용
// List<Integer> arr = new ArrayList<>();
// for (int i = 0 ; i < 100 ; ++i)
//    arr.add(i); -> arr.add(Integer.valueOf(i));


//-------------------------------------------------------------


// 중요: 객체를 [불변 객체]로 설계해야 한다.
// Object가 내부적으로 변경되면 Copy or Write 기능을 구현해 주어야 한다. ??
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