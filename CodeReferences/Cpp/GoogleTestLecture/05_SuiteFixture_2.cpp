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
	// connect()�� disconnect()�� ���� �۾�
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
	: Static member function SetUpTestCase / TearDownTestCase�� ����
	��ġ / ��ü �� �� �ִ�.

Pitfall - Important!
	: Test function �� �� �̻� Indenpendent ���� �ʴ�.
	=> [���������� Test]�� ������ �߻��� �� �ִ�.
	: Shared fixture �� status �� ���� Test result �� ���Ѵ�.
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

// C++ ����: Static Member Variable �� File�� �ܺ� ���Ǹ� �ؾ��Ѵ�.
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
Fixture SetUp/TearDown�� �۾��� ���� ���, Test function�� �߰��� ������
Test�� �������� ������ �߻��Ѵ�.
	=> ���� Test ����
	: Test�� �ʹ� ������, �����ڵ��� SUT�� ����Ǿ �Ź� Test��
	�������� �ʴ´�.
	(Test�� �����ϴ� �������� ���꼺�� ����߸���.)
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
