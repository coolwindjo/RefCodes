// 3_TestFixture_3.cpp
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
	: public 멤버 함수 - Create()
		private 멤버 함수 - create()
	=> go
	Create() => public
	create() -> private

Fixture

Fixture 설치 방법 3 - Implicit Setup => 가장 좋은 방법!
	: 여러 Test에서 같은 Test Fixture를 Setup()/TearDown() 함수에서 생성한다.
	=> xUnit Test Framework
	장점: Test code 중복을 제거하고, 꼭 필요하지 않은 상호작용 Code를
		Capsule화 할 수 있다.
	단점: Fixture Set up code가 Test function 밖에 존재하기 때문에 
		Test function 만으로 code를 이해하기 어려울 수 있다.

	1. Test function이 실행되는 과정
	2. 4단계 Test Pattern

	Junit4 - Android Studio (Test Runner - multi thread)
	Junit4, gtest

	'신선한 Fixture 전략'
	CalculatorTest* testcase = new CalculatorTest;
	testcase->SetUp()
	testcase->test1()
	delete testcase;

	CalculatorTest* testcase = new CalculatorTest;
	testcase->SetUp()
	testcase->test2()
*/
#include "gtest\gtest.h"

// google test - test case class 만드는 법
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
Test 구성 방법
	: xUnit Test Pattern - 4단계 Test(Four-phase Test)
	1단계: Test의 Fixture 를 설치하거나 실제 결과를 관찰하기 위해 
		필요한 것을 집어넣는 작업을 한다.
	2단계: SUT와 상호작용한다.
	3단계: 기대 결과를 확인한다.
	4단계: Test Fixture를 해체하여, Test 시작 상태로 되돌려 놓는다.
		=> 신선한 Fixture 전략
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
