// 16_GoogleMock.cpp
#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////////////////////
#include "gmock\gmock.h"
#include "gtest\gtest.h"

class Unit
{
public:
	Unit();
	/*
	Unit �� ��� �޴� ���·� Mock�� �����ؾ� �ϱ� ������
	�ݵ�� ���� �Ҹ��ڸ� �����ؾ� �Ѵ�.
	*/
	virtual	~Unit();

	virtual void stop() = 0;
	virtual void say(const string& message) = 0;
	
	virtual void attack(Unit* target) = 0;
	virtual void move(int x, int y) = 0;

	virtual int getX() const = 0;
	virtual int getY() const = 0;

private:

};

Unit::Unit()
{
}

Unit::~Unit()
{
}

/*
Function �� MACRO �� ���ؼ� MOCK �� �����ϴ� ���
	1. MOCK_METHOD{�Ķ���Ͱ���}(�Լ���, �Լ�Ÿ��)
	2. MOCK_CONST_METHOD{�Ķ���Ͱ���}(�Լ���, �Լ�Ÿ��)
*/

class MockUnit	: public Unit
{
public:
	MockUnit();
	~MockUnit();

	MOCK_METHOD0(stop,
		void());
	MOCK_METHOD1(say,
		void(const string& message));
	MOCK_METHOD1(attack,
		void(Unit* target));
	MOCK_METHOD2(move,
		void(int x, int y));
	MOCK_CONST_METHOD0(getX,
		int());
	MOCK_CONST_METHOD0(getY,
		int());

private:
};

MockUnit::MockUnit()
{
}

MockUnit::~MockUnit()
{
}

/*
Behaviour - based Test
	1. ȣ�� ���� ����
	2. ȣ�� Ƚ�� ����
	3. ȣ�� ���� ����
	4. ���� ����
*/

void foo(MockUnit* p)
{
	p->stop();
}

// 	1. ȣ�� ���� ����
TEST(MockUnitTest, Sample1)
{
	// 1. Mock ����
	MockUnit mock;

	// 2. ��� ���� ���
	EXPECT_CALL(mock, stop());

	// 3. Mock �� ����� Code �� ����
	foo(&mock);
}

void goo(MockUnit* p)
{
	p->stop();
	p->stop();
}

// 2. ȣ�� Ƚ�� ����
using ::testing::AnyNumber;

TEST(MockUnitTest, Sample2)
{
	// 1. Mock ����
	MockUnit mock;

	// 2. ��� ���� ���
	//EXPECT_CALL(mock, stop()).Times(AnyNumber());
	EXPECT_CALL(mock, stop()).Times(4);

	// 3. Mock �� ����� Code �� ����
	goo(&mock);
}

void hoo(MockUnit* p)
{
	p->attack(nullptr);
	p->move(10, 2000);
}

// 4. ȣ�� ���� ����
using ::testing::_;

TEST(MockUnitTest, Sample4)
{
	// 1. Mock ����
	MockUnit mock;

	// 2. ��� ���� ���
	EXPECT_CALL(mock, move(10, _));
	EXPECT_CALL(mock, attack(_));

	// 3. Mock �� ����� Code �� ����
	hoo(&mock);
}

// 3. ȣ�� ���� ����
using ::testing::InSequence;

TEST(MockUnitTest, Sample3)
{
	// 1. Mock ����
	InSequence seq;
	MockUnit mock;

#if 0
	// 2. ��� ���� ���
	EXPECT_CALL(mock, move(10, 20));
	EXPECT_CALL(mock, attack(nullptr));

	// 3. Mock �� ����� Code �� ����
	hoo(&mock);
#endif	// #if 0
}

/*
Mock Framework
	=> Test Double
	=> �ݸ� Framework
*/
// Stub
class Time
{
public:
	Time();
	~Time();

	string getTimeString()
	{
		return "12:56";
	}

private:

};

Time::Time()
{
}

Time::~Time()
{
}

class MockTime	: public Time
{
public:
	MockTime();
	virtual ~MockTime();

	MOCK_METHOD0(getTimeString, string());
private:

};

MockTime::MockTime()
{
}

MockTime::~MockTime()
{
}

using ::testing::Return;
TEST(TimeTest, Sample)
{
	MockTime stub;
	ON_CALL(stub, getTimeString()).WillByDefault(Return("00:00"));

	cout << stub.getTimeString() << endl;
}