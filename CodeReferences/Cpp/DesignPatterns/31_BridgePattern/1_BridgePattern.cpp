// Bridge Pattern 중요!!
// Design Pattern의 핵심 패턴은 Interface!! DIP
// Interface의 변화에 대응할 수 있는 Pattern
// 개념을 정확히 이해하는 것이 중요
#include <iostream>
using namespace std;

struct IMP3
{
    virtual void play() = 0;
    virtual void stop() = 0;

    // virtual void playOneMinute() = 0;
    // 인터페이스를 변경할 경우 인터페이스를 구현한 모든 서브 클래스가
    // 깨지는 문제가 발생한다.
    
    virtual ~IMP3() {}
};

class iPod
{
public:
    iPod() {}
    ~iPod() {}
    void play() { cout << "Play music with iPod!" << endl; }
    void stop() { cout << "Stop the music" << endl; }
private:

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