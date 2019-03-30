// 1_start.cpp
#include "gtest/gtest.h"

/*
gtest에서 Test case 작성하는 방법
	TEST(TestCaseName, TestName)

절대 실패하지 않는 Test - Test smell
	=> 만약 Test를 작성하는 도중이라면, 실패하는 Test로 작성해야 한다.

Test가 가져야하는 속성!!
	=> 자체검사 Test
	Test가 실패한 경우, 실패의 이유를 결과창을 통해서 알 수 있어야 한다.
	즉, 실패의 원인을 반드시 명시해야 한다.
*/

// Sample class 내부의 foo라는 함수를 Test하겠다.
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
1. Solution 생성
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