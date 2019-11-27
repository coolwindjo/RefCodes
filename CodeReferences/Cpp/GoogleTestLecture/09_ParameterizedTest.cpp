// 9_ParameterizedTest.cpp
/*
- xUnit Test Pattern - framework ������ �ؾ���.
	: �Է� �����͸� �ٲ㰡�鼭, ������ �ݺ� �˻��ϴ�
	������ �߽� �׽�Ʈ�� �ߺ��� �����ִ� ���

������: Test�� �̸� ��ü���� Data�� � �������� �巯�� �� ����.
	=> JUnit4 ������ 'Parameterized Test' ���� Test �� �̸��� ������ �� �ִ�
		����� �����Ѵ�.

Google Test�� �����ϰ� ���� ���
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

// ���� �����Ϳ� ���ؼ� �������� ������ �����ϰ��� ��.
//					public ::testing:TestWithParam<�Է� ������ Ÿ��>
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