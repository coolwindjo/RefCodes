// Bridge Pattern �߿�!!
// Design Pattern�� �ٽ� ������ Interface!! DIP
// Interface�� ��ȭ�� ������ �� �ִ� Pattern
// ������ ��Ȯ�� �����ϴ� ���� �߿�   http://yesarang.tistory.com/316
#include <iostream>
using namespace std;

// Bridge Pattern - pImpl idiom (Pointer To Implementation)
//                - Qt (KDE) : d pointer
// : �����ο� �������̽��� �и��ؼ� ��ȣ �������� ������
//   �����ϵ��� �Ѵ�.

// ���������� ����� ����Ǿ�� �Ѵٸ�, �긴���� ��������.
// - �������̽��� ȿ���� ������ ���·�, ������ ���� ��� Ŭ������
//   ������ �ذ� �����ϴ�.

// C++ pImpl Idiom
// - �����Ϸ� ��ȭ��
#if 0
// Point.h
class Point
{
public:
    Point();
    void foo();

private:
    int x;
    int y;
    int z;  // ����Ǹ� �Ʒ� �� ������ ��� �ٽ� Compile�Ǿ�� �Ѵ�. ������... pImpl��?
};

// Point.cpp
#include "Point.h"
Point::Point() {}
Point::foo() {}

// main.cpp
#include "Point.h"
int main()
{
    Point p;
}
#endif

#if 0

// pImpl idiom - ��� ���Ͽ� ���� �������� ������ �� �����Ƿ�, ������ �ð���
//               ������ �� �ִ�.
// Point.h
class Point
{
public:
    Point();
    void foo();

private:
    PointImpl* pImpl;
};

// Point.cpp
#include "PointImpl.h"

Point::Point()
{
    pImpl = new PointImpl;
}

void Point::foo()
{
    pImpl->foo();
}

// PointImpl.h
class PointImpl
{
public:
    void foo();

private:
    int x;
    int y;
    int z;
};

// PointImpl.cpp
#include "PointImpl.h"

void PointImpl::foo()
{ }

// main.cpp
#include "Point.h"

int main()
{
    Point p;
    p.foo();
}

#endif


struct IMP3
{
    virtual void play() = 0;
    virtual void stop() = 0;
    virtual ~IMP3() {}
};

class iPod : public IMP3
{
public:
    iPod() {}
    ~iPod() {}
    void play() { cout << "Play music with iPod!" << endl; }
    void stop() { cout << "Stop the music" << endl; }
private:

};


// pImpl !!
class MP3 : public IMP3
{
    IMP3* pImpl;
public:
    MP3(IMP3* p = 0) : pImpl(p)
    {
        if (pImpl == 0)
            pImpl = new iPod;
    }

    void play() { pImpl->play(); }
    void stop() { pImpl->stop(); }

    void playOneMinute()
    {
        pImpl->play();
        //...
        pImpl->stop();
    }


};


class Person
{
public:
    Person() {}
    ~Person() {}

    void play_music(iPod* mp3)
    {
        mp3->play();
    }
private:

};


int main()
{
    Person person;
    iPod ipod;

    person.play_music(&ipod);

    system("pause");
    return 0;
}