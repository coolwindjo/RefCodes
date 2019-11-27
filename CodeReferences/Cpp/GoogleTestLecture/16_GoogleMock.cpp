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
	Unit 을 상속 받는 형태로 Mock을 생성해야 하기 때문에
	반드시 가상 소멸자를 제공해야 한다.
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
Function 을 MACRO 를 통해서 MOCK 을 수행하는 방법
	1. MOCK_METHOD{파라메터갯수}(함수명, 함수타입)
	2. MOCK_CONST_METHOD{파라메터갯수}(함수명, 함수타입)
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
	1. 호출 여부 검증
	2. 호출 횟수 검증
	3. 호출 순서 검증
	4. 인자 검증
*/

void foo(MockUnit* p)
{
	p->stop();
}

// 	1. 호출 여부 검증
TEST(MockUnitTest, Sample1)
{
	// 1. Mock 생성
	MockUnit mock;

	// 2. 기대 행위 명시
	EXPECT_CALL(mock, stop());

	// 3. Mock 이 적용된 Code 를 실행
	foo(&mock);
}

void goo(MockUnit* p)
{
	p->stop();
	p->stop();
}

// 2. 호출 횟수 검증
using ::testing::AnyNumber;

TEST(MockUnitTest, Sample2)
{
	// 1. Mock 생성
	MockUnit mock;

	// 2. 기대 행위 명시
	//EXPECT_CALL(mock, stop()).Times(AnyNumber());
	EXPECT_CALL(mock, stop()).Times(4);

	// 3. Mock 이 적용된 Code 를 실행
	goo(&mock);
}

void hoo(MockUnit* p)
{
	p->attack(nullptr);
	p->move(10, 2000);
}

// 4. 호출 인자 검증
using ::testing::_;

TEST(MockUnitTest, Sample4)
{
	// 1. Mock 생성
	MockUnit mock;

	// 2. 기대 행위 명시
	EXPECT_CALL(mock, move(10, _));
	EXPECT_CALL(mock, attack(_));

	// 3. Mock 이 적용된 Code 를 실행
	hoo(&mock);
}

// 3. 호출 순서 검증
using ::testing::InSequence;

TEST(MockUnitTest, Sample3)
{
	// 1. Mock 생성
	InSequence seq;
	MockUnit mock;

#if 0
	// 2. 기대 행위 명시
	EXPECT_CALL(mock, move(10, 20));
	EXPECT_CALL(mock, attack(nullptr));

	// 3. Mock 이 적용된 Code 를 실행
	hoo(&mock);
#endif	// #if 0
}

/*
Mock Framework
	=> Test Double
	=> 격리 Framework
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