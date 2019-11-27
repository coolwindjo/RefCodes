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
Test case�� �����ϴ� �Ϲ����� ���
	=> Testcase Class for every Class
	: �ϳ��� SUT class�� ���� Test function�� �ϳ��� Testcase Class �ȿ� 
	���� ����ִ´�.
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
