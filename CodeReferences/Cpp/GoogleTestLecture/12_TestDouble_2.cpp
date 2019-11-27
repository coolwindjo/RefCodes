// 12_TestDouble_2.cpp
/*
����: SUT�� �ִ��� �ݸ�����, ���ϴ� Point �� �����Ѵ�.

Test Double
	=> Test Double �� ���� �� �� �ִ� Design �ΰ�?
*/
#include <string>
#include <iostream>

using namespace std;

/*
Testable Design
	=> Test Double �� ����� Testable Design

Refactoring:
ƴ������� - �����ϴ� ��ü�� ��ü������ ���� (������ ����)
��ü ������ ������ Design �� �ٽ�! => Interface

������
	1. Specific type �� �ٷ� ����ϴ� ���� Strong coupling �� �����Ѵ�.
		FileSystem => IFileSystem
	2. ���� �����ϴ� ��ü�� new ���� ���ƾ� �Ѵ�.
		��ü ���ο��� new �� ���� ���ƾ��Ѵ�.
		=> �����ϴ� ��ü�� ���� �����ϴ� ���� �ƴ϶�,
			�ܺο��� ���� �޾ƾ� �Ѵ�.
		=> Dependency Injection
			������ ����
	3. Dependency Injection �� ��� - 2����
		1) �����ڸ� ���� ����
			��ü�� ������ ��, �ʼ����� �������� ��...
		2) Setter �� ����
			��� ������ ���...

		������ ������ ����
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
	// ƴ�� �����: ������ ������ �����ؾ� �Ѵ�.
	Logger(IFileSystem* p = 0) : fs(p) 
	{
		if (fs == 0)
			fs = new FileSystem;
	}

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

// ���� �Ʒ��� Test �� Unit Test �ΰ�? 1. 2. ��� Test �ϰ� �ִ�1
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
