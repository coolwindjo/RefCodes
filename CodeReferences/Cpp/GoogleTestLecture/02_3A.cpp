// 2_3A.cpp
// Unit test�� �����ϴ� ���
// SUT(Test ��� system), CUT(Test ��� Class)
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
Unit Test�� 3A�� ���ؼ� Test�� �����Ѵ�.
	1. Arrange: Object �����ϰ�, �ʿ��� ��쿡 �����ϰ� �����ϰ� �غ��Ѵ�.
	2. Act: Object�� �ۿ��� ���Ѵ�.
	3. Assert: ����ϴ� �ٸ� �ܾ��Ѵ�.

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
Test�� ��������, �� Test�� � scenario �� Test �ϴ��� ���θ� �� �� ����.
	=> �� Test�� � scenario �� Test�ϴ��� Test �̸����� ǥ���ؾ� �Ѵ�.
	e.g. Test����Լ�_scenario_��밪
	c.f. Junit5 - Test runner���� ǥ���Ǵ� Test name�� �ٲ��ֱ⵵ ��.

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
	1. Test function�� seperated test�� �Ұ����ϴ�.
		: Test function������ ���ǹ��̳� �ݺ����� ����� ���ؾ� �Ѵ�.
		=> �����̳� �ݺ��� �ʿ��ϴ�. ������ "Test Utility Method"�� ���� ����ؾ� �Ѵ�.
	2. ����ϴ� �ٸ� �ܾ��ϱ� ���ؼ��� xUnit Test Framework�� �����ϴ� �ܾ� �Լ��� ����ϸ� �ȴ�. 
		=> gtest �ܾ� ���� ��ũ��
	3. ������ ������ ��Ȯ�ϰ� ǥ���ؾ� �Ѵ�.
		ASSERT_EQ(expected, actual)
	*/
	ASSERT_EQ(calc->display(), 4) << "When adding 2+2";
}