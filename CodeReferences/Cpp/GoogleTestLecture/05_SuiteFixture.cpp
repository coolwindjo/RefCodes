// 5_SuiteFixture_2.cpp
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
Test case를 구성하는 일반적인 방법
	=> Testcase Class for every Class
	: 하나의 SUT class에 대한 Test function을 하나의 Testcase Class 안에 
	전부 집어넣는다.
*/
class DatabaseTest : public ::testing::Test
{
protected:
	Database* database;

	virtual void SetUp() override
	{
		printf("SetUp()\n");
		database = new Database;
		database->connect();
	}

	virtual void TearDown() override
	{
		printf("TearDown()\n");
		database->disconnect();
		delete database;
	}
};

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
*/
