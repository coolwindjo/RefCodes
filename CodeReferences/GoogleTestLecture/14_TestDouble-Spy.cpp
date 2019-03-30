// 14_TestDouble-Spy.cpp
#include <iostream>

using namespace std;

#include <vector>

enum Level
{
	INFO,
	WARN,
	CRITICAL
};

struct DLogTarget
{
	virtual void write(Level level, const string& message) = 0;
	virtual ~DLogTarget() {};
};

// Multiple targets
class FileTarget	: public DLogTarget
{
public:
	FileTarget();
	~FileTarget();
	void write(Level level, const string& message)
	{
		// ���޵� Message �� File �� �����Ѵ�.
	}

private:

};

FileTarget::FileTarget()
{
}

FileTarget::~FileTarget()
{
}

class TCPTarget	: public DLogTarget
{
public:
	TCPTarget();
	~TCPTarget();

	void write(Level level, const string& message)
	{
	}

private:

};

TCPTarget::TCPTarget()
{
}

TCPTarget::~TCPTarget()
{
}

// Message logger on targets.
class DLog
{
public:
	DLog();
	~DLog();
	void addTarget(DLogTarget* p) { targets.push_back(p); }
	void write(Level level, const string& message)
	{
		for (DLogTarget* e : targets)
			e->write(level, message);
	}


private:
	vector<DLogTarget*> targets;

};

DLog::DLog()
{
}

DLog::~DLog()
{
}


//////////////////////////////////////////////////////////////////////////
/*
Object Design
	1. Mutable Object: ��ü�� ���°� ���� ���ķ� ����� �� �ִ�.
	2. Immutable Object: ��ü�� ���°� ���� ���ķ� ������ �Ұ����ϴ�.
		1) �����ϰ� ��� �����ϴ�.
		2) ���ü��� �����ϴ�.

Test Double Usage 3.
	: Function �� ȣ�� �Ͽ��� ��, �߻��ϴ� ���ۿ��� ������ �� ����
	Test �ȵ� Requirement �� �ִ�.
	=> Test Spy

Spy: ����� ���� ����صξ��ٰ�, ���߿� Test���� Ȯ���� �� �ֵ��� 
	������� Test Double
	=> �ٸ� Component �κ����� ���� ����� �����صξ��ٰ�, �����Ѵ�.
*/
#include "gtest\gtest.h"
#include <algorithm>


class DLogTest	: public ::testing::Test
{
public:
	DLogTest();
	~DLogTest();

private:

};

DLogTest::DLogTest()
{
}

DLogTest::~DLogTest()
{
}


// Here's the solution!
class SpyTarget	: public DLogTarget
{
public:
	SpyTarget();
	~SpyTarget();

	// Test ���� ���� �����ϵ��� �ؾ� �Ѵ�.
	bool received(Level level, const string& message)
	{
		string log = concat(level, message);
		return logs.end() != find(logs.begin(), logs.end(), log);
	}

	void write(Level level, const string& message)	override
	{
		logs.push_back(concat(level, message));
	}

private:
	// Vector container is the KEY !!
	vector<string> logs;
	string concat(Level level, const string& message)
	{
		static const char* level_string[] = {
			"INFO", "WARN", "CRITICAL"
		};

		return string(level_string[level]) + ":" + message;
	}

};

SpyTarget::SpyTarget()
{
}

SpyTarget::~SpyTarget()
{
}

TEST_F(DLogTest, writeEachMessageToTargets)
{
	DLog log;
	SpyTarget spy1, spy2;

	log.addTarget(&spy1);
	log.addTarget(&spy2);

	log.write(INFO, "test_message");
	log.write(CRITICAL, "test_message");

	EXPECT_TRUE(spy1.received(INFO, "test_message"));
	EXPECT_TRUE(spy1.received(CRITICAL, "test_message"));
	EXPECT_TRUE(spy2.received(INFO, "test_message"));
	EXPECT_TRUE(spy2.received(CRITICAL, "test_message"));
}
