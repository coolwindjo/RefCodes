// 6_GlobalFIxture.cpp
/*
: google test ������ Global Fixture SetUp / TearDown �� �����Ѵ�.

Global Fixture Setup ��� - gtest_main.cc
	1) Global variable �� ���� ��ġ �����ϴ�.
	2) main() function �� ���� ��ġ �����ϴ�.
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
// Global Variable �� ���� SetUp�ϴ� ���
::testing::Environment* const env
= ::testing::AddGlobalTestEnvironment(new MyTestEnvironment);
#endif

/*
main() function �� ���ؼ� SetUp�ϴ� ���
	- gtest_main.cc �� gtest static library ���� �����ؾ� �Ѵ�.
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