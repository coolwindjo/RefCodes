// 12_TestDouble.cpp
/*
목적: SUT를 최대한 격리시켜, 원하는 Point 를 검증한다.

Test Double
	=> Test Double 을 적용 할 수 있는 Design 인가?
*/
#include <string>
#include <iostream>

using namespace std;

/*
Refactoring:
틈새만들기: Test Double 을 적용할 수 있도록 하는 Refactoring
틈새: Test Double 등의 다양한 기능을 Code 상에 삽입할 수 있는 위치
*/

class FileSystem
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
		FileSystem* fs = new FileSystem;
		return fs->isValid(filename);
	}

private:

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

// 과연 아래의 Test 는 Unit Test 인가? 1. 2. 모두 Test 하고 있다1
TEST_F(LoggerTest, isValidFilename_NameShorterThan5Chars_ReturnsFalse)
{
	Logger logger;
	string filename = "bad.log";

	bool actual = logger.isValidFilename(filename);

	ASSERT_FALSE(actual) << "When the filename is shorter than 5 letters.";
}