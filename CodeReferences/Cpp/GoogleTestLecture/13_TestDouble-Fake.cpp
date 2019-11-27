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
1. ���� �������� �ʾҴ�.
2. ȯ������ ���� ����� �� ���� ���
3. ���� ���
*/
// Could be replaced with a Fake.
class Database	: public IDatabase
{
public:
	Database();
	~Database();
	void save(string id, UserInfo* ui) override
	{
		// Database ���� SQL �� ���� �����ϴ� Code

	}

	UserInfo* load(string id) override
	{
		// Database ���� SQL �� ���� �ҷ��ͼ� ��ü�� �������ִ� Code
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
Test Double ���� 2. ���� �غ���� ���� ���� ��ü�� ���� Test �� �� ���� ��,
	=> Fake Object Pattern
		1) ���� ��ü�� ����� �� ���� ��,
			�ش� Logic �� Independent test �� �� �ִ�.
		2) ���� Test �� �����Ѵ�.

SUT �� �����ϴ� Component �� �ξ� ������ ������ �����ϴ� ������ ��ü�Ѵ�.
	=> Test Stub ���� ������ �ذ��� �� ���� ��� Fake ���
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

// ����� ���� Type �� ���� �ܾ� MACRO�� ����ϱ� ���ؼ��� �ݵ��
// �����ؾ� �Ѵ�.
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