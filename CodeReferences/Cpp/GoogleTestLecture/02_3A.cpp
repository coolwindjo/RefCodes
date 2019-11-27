// 2_3A.cpp
// Unit test를 구성하는 방법
// SUT(Test 대상 system), CUT(Test 대상 Class)
class Calculator
{
public:
	Calculator();
	~Calculator();
	double display() { return 0; }
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
Unit Test는 3A에 의해서 Test를 구성한다.
	1. Arrange: Object 생성하고, 필요한 경우에 적절하게 설정하고 준비한다.
	2. Act: Object에 작용을 가한다.
	3. Assert: 기대하는 바를 단언한다.

TDD(Test Driven) 
BDD(Behaviour Driven) e.g.) mocha, JUnit5
	- Given
	- When
	- Then
*/
#include "gtest\gtest.h"

TEST(CalculatorTestCase, test1)
{
	// Arrange
	Calculator* calc = new Calculator;

	// Act
	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	// Assert
	if (calc->display() != 4)
		FAIL();
	else
		SUCCEED();
}

// Improve the former test.
/*
Test가 많아지면, 각 Test가 어떤 scenario 로 Test 하는지 여부를 알 수 없다.
	=> 각 Test가 어떤 scenario 로 Test하는지 Test 이름으로 표현해야 한다.
	e.g. Test대상함수_scenario_기대값
	c.f. Junit5 - Test runner에서 표현되는 Test name을 바꿔주기도 함.

*/
TEST(CalculatorTestCase, display_AddingTwoPlusTwo_ReturnsFour)
{
	// Arrange
	Calculator* calc = new Calculator;

	// Act
	calc->enter(2);
	calc->pressPlus();
	calc->enter(2);
	calc->pressEqual();

	// Assert - ASSERT_XX
	/*
	1. Test function은 seperated test가 불가능하다.
		: Test function내에서 조건문이나 반복문의 사용은 피해야 한다.
		=> 조건이나 반복이 필요하다. 별도의 "Test Utility Method"을 만들어서 사용해야 한다.
	2. 기대하는 바를 단언하기 위해서는 xUnit Test Framework가 제공하는 단언 함수를 사용하면 된다. 
		=> gtest 단언 전용 매크로
	3. 실패의 이유를 명확하게 표현해야 한다.
		ASSERT_EQ(expected, actual)
	*/
	ASSERT_EQ(calc->display(), 4) << "When adding 2+2";
}