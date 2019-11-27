// GoogleTestFunctions.cpp
#include "gtest/gtest.h"

/*
1.	ASSERT_XX
	: 실패할 경우, 이후의 동작은 수행하지 않는다.
	EXPECT_XX => '죽은 단언문'의 문제를 해결하고자 한다.
	: 실패하더라도 이후의 검증을 수행한다.
*/
TEST(GoogleTest, sample1)
{
	int expected = 3;

	// Act
	int actual1 = 42;
	int actual2 = 42;

	// Assert
	EXPECT_EQ(expected, actual1) << "Reason1"; 
	EXPECT_EQ(expected, actual2) << "Reason2";
}

/*
2. String Comparison Assertion
	: ASSERT_STREQ() / EXPECT_STREQ()

*/
#include <string>
using std::string;

TEST(GoogleTest, sample2)
{

	// Act
	string s1 = "hello";
	string s2 = "hello";

	// Assert
	ASSERT_EQ(s1, s2) << "s1 == s2";

	const char* s3 = "hello";
	const char* s4 = s1.c_str();
	
	ASSERT_STREQ(s3, s4) << "s3 == s4";
}

/*
3. Floating point number comparison
*/
TEST(GoogleTest, sample3)
{
	// Assert
	EXPECT_DOUBLE_EQ(0.7, 0.1*7) << "4 ULP's";	// Unit in the Last Place
	ASSERT_DOUBLE_EQ(0.7, 0.1*7) << "4 ULP's";	// Unit of Last Precision

	// 직접 오차 범위를 지정할 수 있는 MACRO
	ASSERT_NEAR(0.7, 0.1*7, 0.1);
}

/*
4. Exception Test
	: SUT가 특정 상황에서 기대한 예외가 발생하는 지 여부를 검증하는 작업

*/
void foo(const string& name)
{
	if (name.empty())
		throw std::invalid_argument("name is empty");

	throw 1;
}

// Google Test가 제공하는 예외 Test
TEST(DISABLED_GoogleTest, exceptionTest)
{
	string filename = "";

	//EXPECT_THROW(foo(filename), std::invalid_argument);
	EXPECT_ANY_THROW(foo(filename));	// 예외가 발생하면 성공
}

/*
Test를 비활성화 하기 위해서 절대 주석처리 하지 말라.
	=> 비활성 기능, 결과창에 표시해준다.
	5. 비활성 기능
	TEST_F(Disabled_XXX, Disabled_XXX)
	=> gtest runner; 비활성화된 Test만을 따로 돌리는 기능
		unittest.exe --gtest_also_run_disabled_tests
*/

TEST(DISABLED_GoogleTest, DISABLED_exceptionTestOld)
{
	string filename = "";

	try
	{
		foo(filename);
		FAIL() << "기대한 예외가 발생하지 않음";
	}
	catch (std::invalid_argument& e)
	{
		SUCCEED();
	}
	catch (...)
	{
		FAIL() << "다른 예외가 발생하였음";
	}
}