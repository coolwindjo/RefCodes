// 5_SuiteFixture.cpp
#include <iostream>
#include <string>

using namespace std;

// SUT
#include <Windows.h>
void delay(int sec)
{
	Sleep(sec * 1000);
}

class Database
{
public:
	// connect()와 disconnect()가 느린 작업
	void connect() { delay(3); }
	void disconnect() { delay(1); }

	void login(const string& id, const string& password) {}
	void logout() {}

	bool isLogin() { return true; }
};

//////////////////////////////////////////////////////////////////////////
#include "gtest\gtest.h"

/*
Slow Test => Suite Fixture SetUp / TearDown
	: Static member function SetUpTestCase / TearDownTestCase를 통해
	설치 / 해체 할 수 있다.

Pitfall - Important!
	: Test function 은 더 이상 Indenpendent 하지 않다.
	=> [변덕스러운 Test]의 문제가 발생할 수 있다.
	: Shared fixture 의 status 에 따라서 Test result 가 변한다.
*/

class DatabaseTest : public ::testing::Test
{
protected:
	static Database* database;
	static void SetUpTestCase()
	{
		printf("SetUpTestCase()\n");
		database = new Database;
		database->connect();
	}

	static void TearDownTestCase()
	{
		printf("TearDownTestCase()\n");
		database->disconnect();
		delete database;
	}

	virtual void SetUp() override
	{
		printf("SetUp()\n");
	}

	virtual void TearDown() override
	{
		printf("TearDown()\n");
	}
};

// C++ 문법: Static Member Variable 은 File에 외부 정의를 해야한다.
Database* DatabaseTest::database = 0;

TEST_F(DatabaseTest, login)
{
	database->login("test_id", "test_password");

	ASSERT_TRUE(database->isLogin());

	database->logout();
}

TEST_F(DatabaseTest, logout)
{
	database->login("test_id", "test_password");
	database->logout();

	ASSERT_TRUE(database->isLogin());
}

/*
Fixture SetUp/TearDown의 작업이 느릴 경우, Test function을 추가할 때마다
Test가 느려지는 문제가 발생한다.
	=> 느린 Test 문제
	: Test가 너무 느려서, 개발자들이 SUT가 변경되어도 매번 Test를
	실행하지 않는다.
	(Test를 실행하는 개발자의 생산성을 떨어뜨린다.)
*/
TEST_F(DatabaseTest, foo)
{

}

/*
google test => TestCase fixture SetUp / TearDown
xUnit - Suite Fixture SetUp / TearDown

CalculatorTest.SetUpTestCase()

CalculatorTest* testcase = new CalculatorTest;
testcase->SetUp()
testcase->test1()
testcase->TearDown()
delete testcase;

CalculatorTest* testcase = new CalculatorTest;
testcase->SetUp()
testcase->test1()
testcase->TearDown()
delete testcase;

CalculatorTest.TearDownTestCase()

*/
