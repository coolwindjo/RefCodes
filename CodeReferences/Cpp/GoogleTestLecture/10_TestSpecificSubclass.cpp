// 10_TestSpecificClass.cpp
#include <stdio.h>

class Engine
{
public:
	Engine();
	~Engine();

	virtual void start()
	{
		printf("Start engine\n");
	}
private:

};

Engine::Engine()
{
}

Engine::~Engine()
{
}

class Car
{
public:
	Car(Engine* p);
	~Car();

	void start()
	{
		engine->start();
	}

private:
	Engine* engine;
};

Car::Car(Engine* p)
	: engine(p)
{
}

Car::~Car()
{
}

///////////////////////////////////////////////////////////////////////
#include "gtest\gtest.h"

class CarTest	: public ::testing::Test
{
public:
	CarTest();
	~CarTest();

private:


};

CarTest::CarTest()
{
}

CarTest::~CarTest()
{
}

/*
OOP 상속 => {자식} is a {부모}
	Shape
Circle Rectangle

Test Specific Subclass
	- 의도: SUT의 private 상태에 접근해야 하는 코드를 어떻게 하면
		Test 가능하게 할 수 있는가?

	- 한계: C#, C++ => 부모의 기능이 반드시 virtual 함수로 제공되어야 한다.
*/

class TestEngine	: public Engine 
{
public:
	TestEngine();
	~TestEngine();

	bool isStart()
	{
		return _isStart;
	}
	virtual void start() override
	{
		Engine::start();	// 부모의 함수를 직접 호출
		_isStart = true;
	}
private:
	bool _isStart;

};

TestEngine::TestEngine()
	: _isStart(false)
{
}

TestEngine::~TestEngine()
{
}


// 자동차의 시동을 걸었을 때, 엔진의 구동여부를 검증하고 싶다.
TEST_F(CarTest, CheckEngineStarted)
{
	Engine engine;
	Car car(&engine);

	car.start();

	// 검증 방법이 없다.
}

TEST_F(CarTest, CheckEngineStarted_TestSpecificSubclass)
{
	TestEngine engine;
	Car car(&engine);

	car.start();

	ASSERT_TRUE(engine.isStart());
}
