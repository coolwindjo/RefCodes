// 3_TestFixture.cpp
#include "gtest\gtest.h"

// SUT(Test 대상 system), CUT(Test 대상 Class)
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

Fixture 설치 방법 2 - Delegation(위임) 설치
	1. 동일한 Fixture를 가진 Test 함수를 Class로 묶는다.
	2. Fixture 설치에 관한 중복되는 Code를 Function으로 제공한다.
*/
#include "gtest\gtest.h"

// google test - test case class 만드는 법
class CalculatorTest : public ::testing::Test
{
	/*
google test에서 test utility method의 접근 지정자는 반드시 
protected로 지정해야 한다.
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
