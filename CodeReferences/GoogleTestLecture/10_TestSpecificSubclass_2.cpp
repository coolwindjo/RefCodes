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
// C++ 제품 코드가 pImpl idiom으로 되어 있으면 소용없습니다.
//#include "User.h"

// C 언어 기능 Test
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
C++ 에서 Test Specific Subclass를 만드는 방법
	=> protected 필드를 Test 목적으로 접근하는 방법
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