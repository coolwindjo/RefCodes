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
		// 연결이 갑자기 끊어진 경우
		throw IOException();
	}

	void attack() override
	{
		//....
		// 연결이 갑자기 끊어진 경우
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
Test Double Usage 1. Specific 한 Event 를 Simulation 할 수 있다.
	- Network 연결이 끊긴 경우
	- 시간 제어
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

// 연결이 성립되지 않을 경우, move()를 호출하면 
// 예외가 제대로 발생하는지 여부를 검증
TEST_F(UserTest, move_CheckExceptionAfterDisconnection)
{
	ASSERT_THROW(user->move(10, 10), IOException);

}

TEST_F(UserTest, attack_CheckExceptionAfterDisconnection)
{
	ASSERT_THROW(user->attack(), IOException);

}