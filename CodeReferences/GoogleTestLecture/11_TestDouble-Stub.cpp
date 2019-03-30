// 11_TestDouble-Stub.cpp
#include <iostream>

class IOException : public std::exception
{
public:
	virtual const char* what() {
		return "Pipe is broken";
	}
};

struct IConnection
{
	virtual void move(int x, int y) = 0;
	virtual void attack() = 0;
	virtual ~IConnection() {}
};

class TCPConnection : public IConnection
{
	void move(int x, int y) override
	{
		//....
		// ������ ���ڱ� ������ ���
		throw IOException();
	}

	void attack() override
	{
		//....
		// ������ ���ڱ� ������ ���
		throw IOException();
	}
};

class User
{
	IConnection* connection;
public:
	User(IConnection* p) : connection(p) {}
	void move(int x, int y) { connection->move(x, y); }
	void attack() { connection->attack(); }
};


/////////////////////////////////////////////////////////////////////////
/*
Test Double Usage 1. Specific �� Event �� Simulation �� �� �ִ�.
	- Network ������ ���� ���
	- �ð� ����
	=> Test Stub Pattern
*/
class BaddConnection	: public IConnection
{
public:
	BaddConnection();
	~BaddConnection();

	virtual void move(int x, int y) override
	{
		throw IOException();
	}

	virtual void attack() override
	{
		throw IOException();
	}

private:

};

BaddConnection::BaddConnection()
{
}

BaddConnection::~BaddConnection()
{
}

#include "gtest\gtest.h"

class UserTest	: public ::testing::Test
{
public:
	UserTest();
	~UserTest();

protected:
	User* user;
	virtual void SetUp() override
	{
		//user = new User(new TCPConnection);
		user = new User(new BaddConnection);
	}

	virtual void TearDown() override
	{
		delete user;
	}

};

UserTest::UserTest()
{
}

UserTest::~UserTest()
{
}

// ������ �������� ���� ���, move()�� ȣ���ϸ� 
// ���ܰ� ����� �߻��ϴ��� ���θ� ����
TEST_F(UserTest, move_CheckExceptionAfterDisconnection)
{
	ASSERT_THROW(user->move(10, 10), IOException);

}

TEST_F(UserTest, attack_CheckExceptionAfterDisconnection)
{
	ASSERT_THROW(user->attack(), IOException);

}