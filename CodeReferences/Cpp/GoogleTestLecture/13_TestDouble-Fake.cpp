// 13_TestDouble-Fake.cpp
#include <iostream>
#include <string>

using namespace std;

class UserInfo
{
public:
	UserInfo(string id, int level, int gold);
	~UserInfo();
	string id() const { return id_; }
	int level() const { return level_; }
	int gold() const { return gold_; }

private:
	string id_;
	int level_;
	int gold_;

};

UserInfo::UserInfo(string id, int level, int gold)
	: id_(id)
	, level_(level)
	, gold_(gold)
{
}

UserInfo::~UserInfo()
{
}

struct IDatabase
{
	virtual void save(string id, UserInfo* ui) = 0;
	virtual UserInfo* load(string id) = 0;

	virtual ~IDatabase() {}
};

/*
1. 아직 구현되지 않았다.
2. 환경으로 인해 사용할 수 없는 경우
3. 느린 경우
*/
// Could be replaced with a Fake.
class Database	: public IDatabase
{
public:
	Database();
	~Database();
	void save(string id, UserInfo* ui) override
	{
		// Database 에서 SQL 을 통해 저장하는 Code

	}

	UserInfo* load(string id) override
	{
		// Database 에서 SQL 을 통해 불러와서 객체를 생성해주는 Code
		return nullptr;
	}

private:

};

Database::Database()
{
}

Database::~Database()
{
}

// SUT
class UserManager
{
public:
	UserManager(IDatabase* p);
	~UserManager();
	void save(UserInfo* ui)
	{
		// ...
		database->save(ui->id(), ui);
	}

	UserInfo* load(string id)
	{
		// ...
		return database->load(id);
	}

private:
	IDatabase* database;
};

UserManager::UserManager(IDatabase* p)
	: database(p)
{
}

UserManager::~UserManager()
{
}


///////////////////////////////////////////////////////////////////////
#include "gtest\gtest.h"

/*
Test Double 목적 2. 아직 준비되지 않은 의존 객체로 인해 Test 할 수 없을 때,
	=> Fake Object Pattern
		1) 의존 객체를 사용할 수 없을 때,
			해당 Logic 을 Independent test 할 수 있다.
		2) 느린 Test 를 개선한다.

SUT 에 의존하는 Component 를 훨씬 가볍고 빠르게 동작하는 것으로 교체한다.
	=> Test Stub 으로 문제를 해결할 수 없는 경우 Fake 사용
*/

#include <map>
class MemoryDatabase	: public IDatabase
{
public:
	MemoryDatabase();
	~MemoryDatabase();
	void save(string id, UserInfo* ui) override
	{
		data[id] = ui;
	}

	UserInfo* load(string id) override
	{
		return data[id];
	}
private:
	// Just use simple memory for a Fake database. - KEY !!
	map<string, UserInfo*> data;

};

MemoryDatabase::MemoryDatabase()
{
}

MemoryDatabase::~MemoryDatabase()
{
}


class UserManagerTest	: public ::testing::Test
{
public:
	UserManagerTest();
	~UserManagerTest();

private:

};

UserManagerTest::UserManagerTest()
{
}

UserManagerTest::~UserManagerTest()
{
}

// 사용자 정의 Type 에 대한 단언 MACRO를 사용하기 위해서는 반드시
// 정의해야 한다.
bool operator==(const UserInfo& lhs, const UserInfo& rhs)
{
	return lhs.id() == rhs.id() &&
		lhs.level() == rhs.level() &&
		lhs.gold() == rhs.gold();
}

bool operator!=(const UserInfo& lhs, const UserInfo& rhs)
{
	return lhs.id() != rhs.id() &&
		lhs.level() != rhs.level() &&
		lhs.gold() != rhs.gold();
}

// ...
// ...

TEST_F(UserManagerTest, save)
{
	MemoryDatabase mdb;
	UserManager manager(&mdb);
	string testId = "test_id";
	int testLevel = 10;
	int testGold = 1000;
	UserInfo ui(testId, testLevel, testGold);

	manager.save(&ui);
	UserInfo* actual = manager.load(testId);

	ASSERT_NE(nullptr, actual);
	ASSERT_EQ(ui, *actual);
	// ASSERT_GE(ui, *actual);
	// ASSERT_LT(ui, *actual);
	// ASSERT_GT(ui, *actual);
}