// 12_TestDouble_2.cpp
/*
목적: SUT를 최대한 격리시켜, 원하는 Point 를 검증한다.

Test Double
	=> Test Double 을 적용 할 수 있는 Design 인가?
*/
#include <string>
#include <iostream>

using namespace std;

/*
Testable Design
	=> Test Double 을 고려한 Testable Design

Refactoring:
틈새만들기 - 의존하는 객체를 교체가능한 형태 (느슨한 결합)
교체 가능한 유연한 Design 이 핵심! => Interface

문제점
	1. Specific type 을 바로 사용하는 것은 Strong coupling 을 형성한다.
		FileSystem => IFileSystem
	2. 절대 의존하는 객체를 new 하지 말아야 한다.
		객체 내부에서 new 를 쓰지 말아야한다.
		=> 의존하는 객체를 직접 생성하는 것이 아니라,
			외부에서 주입 받아야 한다.
		=> Dependency Injection
			의존성 주입
	3. Dependency Injection 의 방법 - 2가지
		1) 생성자를 통한 주입
			객체를 동작할 때, 필수적인 의존성일 때...
		2) Setter 로 주입
			없어도 무방한 경우...

		빈자의 의존성 주입
*/

struct IFileSystem
{
	virtual bool isValid(string filename) = 0;
	virtual ~IFileSystem() {}

};

class FileSystem	: public IFileSystem
{
public:
	FileSystem();
	~FileSystem();
	bool isValid(string filename)
	{
		// 현재 File system 의 종류에 따라서 다른 Code
		// NTFS, ext4...
		return true;
	}

private:

};

FileSystem::FileSystem()
{
}

FileSystem::~FileSystem()
{
}

class Logger
{
public:
	Logger();
	~Logger();
	// 틈새 만들기: 기존의 사용법과 동일해야 한다.
	Logger(IFileSystem* p = 0) : fs(p) 
	{
		if (fs == 0)
			fs = new FileSystem;
	}

	// file.log
	// File 의 이름이 다섯 글자 이상 이어야 한다.
	bool isValidFilename(string filename)
	{
		size_t index = filename.find_last_of(".");
		string name = filename.substr(0, index);

		// 1. Check the length of the filename.
		cout << "name: " << name << endl;
		if (name.size() < 5)
			return false;

		// 2. Check file system.
		//FileSystem* fs = new FileSystem;
		return fs->isValid(filename);
	}

private:
	IFileSystem* fs;

};

Logger::Logger()
{
}

Logger::~Logger()
{
}


////////////////////////////////////////////////////////////////////////
#include "gtest\gtest.h"
class LoggerTest : public ::testing::Test
{
public:
	LoggerTest();
	~LoggerTest();

private:

};

LoggerTest::LoggerTest()
{
}

LoggerTest::~LoggerTest()
{
}

class StubFileSystem	: public IFileSystem
{
public:
	StubFileSystem();
	~StubFileSystem();
	virtual bool isValid(string filename) override
	{
		return true;
	}

private:

};

StubFileSystem::StubFileSystem()
{
}

StubFileSystem::~StubFileSystem()
{
}

// 과연 아래의 Test 는 Unit Test 인가? 1. 2. 모두 Test 하고 있다1
TEST_F(LoggerTest, isValidFilename_NameShorterThan5Chars_ReturnsFalse)
{
	StubFileSystem stub;
	Logger logger(&stub);
	string filename = "bad.log";

	bool actual = logger.isValidFilename(filename);

	ASSERT_FALSE(actual) << "When the filename is shorter than 5 letters.";
}

TEST_F(LoggerTest, isValidFilename_NameShorterThan5Chars_ReturnsTrue)
{
	StubFileSystem stub;
	Logger logger(&stub);
	string filename = "logger.log";

	bool actual = logger.isValidFilename(filename);

	ASSERT_FALSE(actual) << "When the filename is longer than 5 letters.";
}
