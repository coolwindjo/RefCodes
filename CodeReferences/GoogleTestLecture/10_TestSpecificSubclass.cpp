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
OOP ��� => {�ڽ�} is a {�θ�}
	Shape
Circle Rectangle

Test Specific Subclass
	- �ǵ�: SUT�� private ���¿� �����ؾ� �ϴ� �ڵ带 ��� �ϸ�
		Test �����ϰ� �� �� �ִ°�?

	- �Ѱ�: C#, C++ => �θ��� ����� �ݵ�� virtual �Լ��� �����Ǿ�� �Ѵ�.
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
		Engine::start();	// �θ��� �Լ��� ���� ȣ��
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


// �ڵ����� �õ��� �ɾ��� ��, ������ �������θ� �����ϰ� �ʹ�.
TEST_F(CarTest, CheckEngineStarted)
{
	Engine engine;
	Car car(&engine);

	car.start();

	// ���� ����� ����.
}

TEST_F(CarTest, CheckEngineStarted_TestSpecificSubclass)
{
	TestEngine engine;
	Car car(&engine);

	car.start();

	ASSERT_TRUE(engine.isStart());
}
