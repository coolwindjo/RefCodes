// 3_TestFixture_3.cpp
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
	void calculatorulate() {}

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
# google C++
	: public ��� �Լ� - Create()
		private ��� �Լ� - create()
	=> go
	Create() => public
	create() -> private

Fixture

Fixture ��ġ ��� 3 - Implicit Setup => ���� ���� ���!
	: ���� Test���� ���� Test Fixture�� Setup()/TearDown() �Լ����� �����Ѵ�.
	=> xUnit Test Framework
	����: Test code �ߺ��� �����ϰ�, �� �ʿ����� ���� ��ȣ�ۿ� Code��
		Capsuleȭ �� �� �ִ�.
	����: Fixture Set up code�� Test function �ۿ� �����ϱ� ������ 
		Test function ������ code�� �����ϱ� ����� �� �ִ�.

	1. Test function�� ����Ǵ� ����
	2. 4�ܰ� Test Pattern

	Junit4 - Android Studio (Test Runner - multi thread)
	Junit4, gtest

	'�ż��� Fixture ����'
	CalculatorTest* testcase = new CalculatorTest;
	testcase->SetUp()
	testcase->test1()
	delete testcase;

	CalculatorTest* testcase = new CalculatorTest;
	testcase->SetUp()
	testcase->test2()
*/
#include "gtest\gtest.h"

// google test - test case class ����� ��
class CalculatorTest : public ::testing::Test
{
public:
	CalculatorTest() 
	{
		printf("CalculatorTest()\n");
	}

protected:
	Calculator* calculator;
	virtual void SetUp()
	{
		printf("SetUp() \n");
		calculator = new Calculator;
	}

	// Implicit fixture deletion function
	virtual void TearDown()
	{
		printf("TearDown() \n");
		delete calculator;
	}
};

/*
Test ���� ���
	: xUnit Test Pattern - 4�ܰ� Test(Four-phase Test)
	1�ܰ�: Test�� Fixture �� ��ġ�ϰų� ���� ����� �����ϱ� ���� 
		�ʿ��� ���� ����ִ� �۾��� �Ѵ�.
	2�ܰ�: SUT�� ��ȣ�ۿ��Ѵ�.
	3�ܰ�: ��� ����� Ȯ���Ѵ�.
	4�ܰ�: Test Fixture�� ��ü�Ͽ�, Test ���� ���·� �ǵ��� ���´�.
		=> �ż��� Fixture ����
*/

TEST_F(CalculatorTest, display_AddingTwoPlusTwo_ReturnsFour)
{
	// Arrange - not really
	printf("test1\n");

	// Act
	calculator->enter(2);
	calculator->pressPlus();
	calculator->enter(2);
	calculator->pressEqual();

	// Assert
	ASSERT_EQ(4, calculator->display()) << "When adding 2+2";
}

TEST_F(CalculatorTest, display_AddingTwoMinusTwo_ReturnsZero)
{
	// Arrange - not really
	printf("test2\n");

	// Act
	calculator->enter(2);
	calculator->pressMinus();
	calculator->enter(2);
	calculator->pressEqual();

	// Assert
	ASSERT_EQ(0, calculator->display()) << "When adding 2-2";
}
