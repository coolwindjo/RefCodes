// 1_start.cpp
#include "gtest/gtest.h"

/*
gtest���� Test case �ۼ��ϴ� ���
	TEST(TestCaseName, TestName)

���� �������� �ʴ� Test - Test smell
	=> ���� Test�� �ۼ��ϴ� �����̶��, �����ϴ� Test�� �ۼ��ؾ� �Ѵ�.

Test�� �������ϴ� �Ӽ�!!
	=> ��ü�˻� Test
	Test�� ������ ���, ������ ������ ���â�� ���ؼ� �� �� �־�� �Ѵ�.
	��, ������ ������ �ݵ�� ����ؾ� �Ѵ�.
*/

// Sample class ������ foo��� �Լ��� Test�ϰڴ�.
TEST(SampleTestCaseName, SampleTestName)
{
	FAIL() << "On the way to implementing.";
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();
	system("pause");
	return ret;
}

/*
Visual studio - Google Test
1. Solution ����
2. gtest static library project
	source
		- $GTEST\googletest\src\gtest-all.cc
		- $GTEST\googletest\src\gtest_main.cc
	include path
		- $GTEST\googletest\
		= $GTEST\googletest\include
3. unit test project
	include path
		- $GTEST\googletest\include
	reference - gtest static library project

Term definition
1. JUnit term
	TestCaseClass
		- TestCase
2. Google Test term
	TestCase
		- Test
*/