// 6_GlobalFIxture.cpp
/*
: google test 에서는 Global Fixture SetUp / TearDown 도 지원한다.

Global Fixture Setup 방법 - gtest_main.cc
	1) Global variable 을 통해 설치 가능하다.
	2) main() function 을 통해 설치 가능하다.
*/

#include <stdio.h>
#include "gtest\gtest.h"

class MyTestEnvironment : public ::testing::Environment
{
public:
	void SetUp()
	{
		printf("Global SetUp()\n");
	}

	void TearDown()
	{
		printf("Global TearDown()\n");
	}
};

#if 0
// Global Variable 을 통해 SetUp하는 방법
::testing::Environment* const env
= ::testing::AddGlobalTestEnvironment(new MyTestEnvironment);
#endif

/*
main() function 을 통해서 SetUp하는 방법
	- gtest_main.cc 를 gtest static library 에서 제외해야 한다.
*/

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	testing::AddGlobalTestEnvironment(new MyTestEnvironment);
	
	int ret = RUN_ALL_TESTS();
	system("pause");
	return ret;
}

TEST(testcase, foo)
{

}