// 3_TestFixture.cpp
#include "gtest\gtest.h"

// SUT(Test ��� system), CUT(Test ��� Class)
class Calculator
{
public:
	Calculator();
	~Calculator();
	double display() { return 4; }
	void enter(double value) {}
	void pressPlus() {}
	void pressMinus() {}
	void pressEqual() {}
	void calculate() {}

private:

};

Calculator::Calculator()
{
}

Calculator::~Calculator()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/*
Fixture

Fixture ��ġ ��� 2 - Delegation(����) ��ġ
	1. ������ Fixture�� ���� Test �Լ��� Class�� ���´�.
	2. Fixture ��ġ�� ���� �ߺ��Ǵ� Code�� Function���� �����Ѵ�.
*/
#include "gtest\gtest.h"

// google test - test case class ����� ��
class CalculatorTest : public ::testing::Test
{
	/*
google test���� test utility method�� ���� �����ڴ� �ݵ�� 
protected�� �����ؾ� �Ѵ�.
	*/
//private:
protected:
	// test utility method - creation method
	Calculator* create()
	{
		return new Calculator;
	}
};

//::testing::Test
//CalculatorTest
//	=> test method (TEST)

TEST_F(CalculatorTest, display_AddingTwoPlusTwo_ReturnsFour)
{
	// Arrange
	Calculator* calc = create();

	// Act
	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	// Assert
	ASSERT_EQ(4, calc->display()) << "When adding 2+2";
}

TEST_F(CalculatorTest, display_AddingTwoMinusTwo_ReturnsZero)
{
	// Arrange
	Calculator* calc = create();

	// Act
	calc->enter(2);
	calc->pressMinus();
	calc->enter(2);
	calc->pressEqual();

	// Assert
	ASSERT_EQ(0, calc->display()) << "When adding 2-2";
}
