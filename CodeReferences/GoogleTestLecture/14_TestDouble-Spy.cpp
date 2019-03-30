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
		// 전달된 Message 를 File 에 저장한다.
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
	1. Mutable Object: 객체의 상태가 생성 이후로 변경될 수 있다.
	2. Immutable Object: 객체의 상태가 생성 이후로 변경이 불가능하다.
		1) 안전하게 사용 가능하다.
		2) 동시성에 안전하다.

Test Double Usage 3.
	: Function 을 호출 하였을 때, 발생하는 부작용을 관찰할 수 없어
	Test 안된 Requirement 가 있다.
	=> Test Spy

Spy: 목격한 일을 기록해두었다가, 나중에 Test에서 확인할 수 있도록 
	만들어진 Test Double
	=> 다른 Component 로부터의 간접 출력을 저장해두었다가, 검증한다.
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

	// Test 에서 검증 가능하도록 해야 한다.
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
