// 12_TestDouble.cpp
/*
����: SUT�� �ִ��� �ݸ�����, ���ϴ� Point �� �����Ѵ�.

Test Double
	=> Test Double �� ���� �� �� �ִ� Design �ΰ�?
*/
#include <string>
#include <iostream>

using namespace std;

/*
Refactoring:
ƴ�������: Test Double �� ������ �� �ֵ��� �ϴ� Refactoring
ƴ��: Test Double ���� �پ��� ����� Code �� ������ �� �ִ� ��ġ
*/

class FileSystem
{
public:
	FileSystem();
	~FileSystem();
	bool isValid(string filename)
	{
		// ���� File system �� ������ ���� �ٸ� Code
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
	// File �� �̸��� �ټ� ���� �̻� �̾�� �Ѵ�.
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

// ���� �Ʒ��� Test �� Unit Test �ΰ�? 1. 2. ��� Test �ϰ� �ִ�1
TEST_F(LoggerTest, isValidFilename_NameShorterThan5Chars_ReturnsFalse)
{
	Logger logger;
	string filename = "bad.log";

	bool actual = logger.isValidFilename(filename);

	ASSERT_FALSE(actual) << "When the filename is shorter than 5 letters.";
}