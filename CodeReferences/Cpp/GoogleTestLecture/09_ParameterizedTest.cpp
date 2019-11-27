// 9_ParameterizedTest.cpp
/*
- xUnit Test Pattern - framework 지원을 해야함.
	: 입력 데이터를 바꿔가면서, 수차례 반복 검사하는
	데이터 중심 테스트의 중복을 없애주는 기법

문제점: Test의 이름 자체에서 Data가 어떤 형식인지 드러낼 수 없다.
	=> JUnit4 에서는 'Parameterized Test' 에서 Test 의 이름을 변경할 수 있는
		기능을 제공한다.

Google Test를 수정하고 싶은 경우
*/

// SUT
bool isPrime(int value)
{
	for (int i = 2; i < value; ++i)
	{
		if (value%i == 0 && i != value)
			return false;
		return true;
	}
}

#include "gtest\gtest.h"

// 같은 데이터에 대해서 여러가지 검증을 수행하고자 함.
//					public ::testing:TestWithParam<입력 데이터 타입>
class PrimeTest	:	public ::testing::TestWithParam<int>
{
public:

private:

};

INSTANTIATE_TEST_CASE_P(PrimeValues, PrimeTest,
	::testing::Values(3, 7, 30, 40, 50));

TEST_P(PrimeTest, isPrime)
{
	ASSERT_TRUE(isPrime(GetParam()));
}

#if 0
TEST(PrimeTest, isPrime)
{
	ASSERT_TRUE(isPrime(10));
	ASSERT_TRUE(isPrime(20));
	ASSERT_TRUE(isPrime(30));
	ASSERT_TRUE(isPrime(40));
	ASSERT_TRUE(isPrime(50));
	//...
}
#endif	// #if 0