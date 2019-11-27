// 3_TestFixture.cpp
#include "gtest\gtest.h"

// SUT(Test 대상 system), CUT(Test 대상 Class)
class Calculator
{
public:
	Calculator();
	~Calculator();
	double display() { return 4; }
	void enter(double value){}
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
	1. Definition: xUnit Test Pattern에서는 SUT를 실행하기 위해서 준비해야 하는 모든 것
	2. Fixture를 구성하는 모든 Logic부분을 'Fixture Setup' 이라고 합니다.

Fixture 설치 방법 1 - Inline fixture 설치
	: 모든 Fixture 설치를 Test function 안에서 처리한다.
	장점: Fixture설치와 검증 로직이 Test function 안에서 존재하기 때문에,
		인과 관계를 쉽게 파악할 수 있다.
	단점: 모든 Test Function 안에서 '코드중복'이 발생한다.

DRY 원칙(Do not Repeat Yourself)
Code 중복 - Test smell
	=> [깨지기 쉬운 Test]
	=> Fixture 설치 작업이 복잡해지면, [애매한 Test]
*/
#include "gtest\gtest.h"

TEST(CalculatorTestCase, display_AddingTwoPlusTwo_ReturnsFour_1)
{
	// Arrange
	Calculator* calc = new Calculator;

	// Act
	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	// Assert
	ASSERT_EQ(4, calc->display()) << "When adding 2+2";
}

TEST(CalculatorTestCase, display_AddingTwoPlusTwo_ReturnsFour_2)
{
	// Arrange
	Calculator* calc = new Calculator;

	// Act
	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	// Assert
	ASSERT_EQ(4, calc->display()) << "When adding 2+2";
}

TEST(CalculatorTestCase, display_AddingTwoPlusTwo_ReturnsFour_3)
{
	// Arrange
	Calculator* calc = new Calculator;

	// Act
	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	// Assert
	ASSERT_EQ(4, calc->display()) << "When adding 2+2";
}
