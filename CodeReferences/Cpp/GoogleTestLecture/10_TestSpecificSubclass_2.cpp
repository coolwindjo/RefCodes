// 10_TestSpecificSubclass_2.cpp
#include <stdio.h>

// FRIEND_TEST
// User.h
#include "gtest/gtest.h"
//	#define class struct
//	#define private public
class User
{
public:
	User();
	~User();
	void levelUp()
	{
		++level;
	}

	FRIEND_TEST(UserTest, levelUp);

protected:
	int level;
	int getLevel()
	{
		return level;
	}

};

User::User()
	: level(1)
{
}

User::~User()
{
}

/////////////////////////////////////////////////////////////////
//#define private public
// C++ ��ǰ �ڵ尡 pImpl idiom���� �Ǿ� ������ �ҿ�����ϴ�.
//#include "User.h"

// C ��� ��� Test
// foo.c
// static void foo() {}
// #include "foo.c"
#include "gtest\gtest.h"
class UserTest	: public ::testing::Test
{
public:
	UserTest();
	~UserTest();

private:

};

UserTest::UserTest()
{
}

UserTest::~UserTest()
{
}

/*
C++ ���� Test Specific Subclass�� ����� ���
	=> protected �ʵ带 Test �������� �����ϴ� ���
*/
class TestUser	: public User
{
public:
	TestUser();
	~TestUser();
	using User::getLevel;

private:
	
};

TestUser::TestUser()
{
}

TestUser::~TestUser()
{
}

TEST_F(UserTest, levelUp)
{
	TestUser user;

	user.levelUp();

	ASSERT_EQ(2, user.getLevel());

}