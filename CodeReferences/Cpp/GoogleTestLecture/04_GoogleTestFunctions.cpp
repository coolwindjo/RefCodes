// GoogleTestFunctions.cpp
#include "gtest/gtest.h"

/*
1.	ASSERT_XX
	: ������ ���, ������ ������ �������� �ʴ´�.
	EXPECT_XX => '���� �ܾ�'�� ������ �ذ��ϰ��� �Ѵ�.
	: �����ϴ��� ������ ������ �����Ѵ�.
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

	// ���� ���� ������ ������ �� �ִ� MACRO
	ASSERT_NEAR(0.7, 0.1*7, 0.1);
}

/*
4. Exception Test
	: SUT�� Ư�� ��Ȳ���� ����� ���ܰ� �߻��ϴ� �� ���θ� �����ϴ� �۾�

*/
void foo(const string& name)
{
	if (name.empty())
		throw std::invalid_argument("name is empty");

	throw 1;
}

// Google Test�� �����ϴ� ���� Test
TEST(DISABLED_GoogleTest, exceptionTest)
{
	string filename = "";

	//EXPECT_THROW(foo(filename), std::invalid_argument);
	EXPECT_ANY_THROW(foo(filename));	// ���ܰ� �߻��ϸ� ����
}

/*
Test�� ��Ȱ��ȭ �ϱ� ���ؼ� ���� �ּ�ó�� ���� ����.
	=> ��Ȱ�� ���, ���â�� ǥ�����ش�.
	5. ��Ȱ�� ���
	TEST_F(Disabled_XXX, Disabled_XXX)
	=> gtest runner; ��Ȱ��ȭ�� Test���� ���� ������ ���
		unittest.exe --gtest_also_run_disabled_tests
*/

TEST(DISABLED_GoogleTest, DISABLED_exceptionTestOld)
{
	string filename = "";

	try
	{
		foo(filename);
		FAIL() << "����� ���ܰ� �߻����� ����";
	}
	catch (std::invalid_argument& e)
	{
		SUCCEED();
	}
	catch (...)
	{
		FAIL() << "�ٸ� ���ܰ� �߻��Ͽ���";
	}
}