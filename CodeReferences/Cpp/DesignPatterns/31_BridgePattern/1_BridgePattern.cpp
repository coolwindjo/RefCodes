// Bridge Pattern �߿�!!
// Design Pattern�� �ٽ� ������ Interface!! DIP
// Interface�� ��ȭ�� ������ �� �ִ� Pattern
// ������ ��Ȯ�� �����ϴ� ���� �߿�
#include <iostream>
using namespace std;

struct IMP3
{
    virtual void play() = 0;
    virtual void stop() = 0;

    // virtual void playOneMinute() = 0;
    // �������̽��� ������ ��� �������̽��� ������ ��� ���� Ŭ������
    // ������ ������ �߻��Ѵ�.
    
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