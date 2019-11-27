// 15_TestDouble-Mock.cpp
#include <iostream>

using namespace std;

struct IMP3
{
	virtual void play() = 0;
	virtual ~IMP3() {}
};


class iPod	: public IMP3
{
public:
	iPod();
	~iPod();
	void play() override
	{
		cout << "Play mp3 with iPod" << endl;
	}

private:

};

iPod::iPod()
{
}

iPod::~iPod()
{
}

class Person
{
public:
	Person();
	~Person();

	void playMP3(IMP3* mp3)
	{
		// ...
		mp3->play();
	}
private:

};

Person::Person()
{
}

Person::~Person()
{
}

/////////////////////////////////////////////////////////////////////
// Person �� playMP3() -> mp3->play() ����

/*
Mock Object
	: �Լ��� ȣ���Ͽ��� ��, �߻��ϴ� ���ۿ��� ������ �� ����
	Test �ȵ� Requirement �� �ִٸ� Mock Object �� ����Ѵ�.
	=> ���� ��� Test

Mock Object �� ���� �����ؼ� ����ϴ� ���� �ƴ϶�
 => Mock Framework
	1. Google Mock (The only choice)
	2. jMock, easyMock, Mockito

Google Mock
	jMock, EasyMock, Hamcraest(�� ǥ���� Ȯ�� Library)
	assertThat(is(), true())
	assertTrue(...)

Test ���� ���
	1) ���� ���� - ���� ��� Test
		: Test �� �����ؾ� �� ���°� ���� ��, ��� Test �� �� �ΰ�?
			=> SUT �� ���� ��, ���¸� ���� �̸� ��밪�� ���Ѵ�.
	2) ���� ���� - ���� ��� Test
		: Test �� �����ؾ� �� ���°� ���� ��, ��� Test �� ���ΰ�?
			=> �Լ��� Return ���� ���ų�, ���ϰ��� Ȯ���ϴ� �͸����δ�
				������ ���������� �����ϱ� ����� �� ����Ѵ�.

Google Mock
	1. Static Library Project
	2. src �߰�
		gmock-all.cc
		gtest-all.cc
		gmock_main.cc
	3. include path
		$GTEST/googlemock
		$GTEST/googlemock/include
		$GTEST/googletest
		$GTEST/googletest/include

Test Project
	1. include path
		$GTEST/googlemock/include
		$GTEST/googletest/include
	2. gmock Static Library �� ����
		
Test Double ����
	����: �ݸ� => ���ϴ� �κ��� Test �ϰ��� �Ѵ�.
	1) ������� ��Ҹ� ����
		�ð�, Network, File system
	2) ��������� ���� ����� �����ϴ� ��ü�� Test
	3) ���� Test
		SUite Fixture => Shared Fixture ����
	4) ������ ������ Ȯ��
	5) ���� ��� ����

Test Double ���� - xUnit Test Pattern ���� ������� ���� (3,4���� �������)
	1. Stub: ���ϴ� ����� ����
	2. Fake object: ��¥ ��ü�� ����ϱ� ��ưų�, �ӵ� ���� �뵵
	3. Test Spy: ���� �Ұ����� ���� ���� Ȯ��
	4. Mock Object: ���� ��� Test
*/
#include "gtest\gtest.h"
#include "gmock\gmock.h"

// int -> int
// void play() -> void()

class Mock	: public iPod
{
public:
	Mock();
	~Mock();

	// MOCK_METHOD{���ڰ���} (�Լ��̸�, �Լ�Ÿ��)
	MOCK_METHOD0(play, void());

private:

};

Mock::Mock()
{
}

Mock::~Mock()
{
}

TEST(PersonTest, playMusic)
{
	Person person;
	/*
	Mock �� Deleted �� ��, Test �� ����ǹǷ�,
		=> Local object �� ����� ���� ����.
	*/
	Mock mock;

	// ���� ��� ���� ��Ҹ� �����Ѵ�.
	EXPECT_CALL(mock, play());

	// Act - the last
	person.playMP3(&mock);
}