// 7_TimeTest.cpp
#include <Windows.h>

/*
비기능 Test
	=> JUnit4에서는 지원하는 기능
*/
#include <stdio.h>
#include <time.h>
#include "gtest\gtest.h"

/*
CRTP : Curiously Recurring Template Pattern
	: 다양한 활용이 가능한데, 부모의 Static Member Variable 을 분리하는 기법.
*/
template <typename T, int N>
class TimeCriticalTest : public ::testing::Test
{
protected:
	time_t startTime;
	static const int PIVOT = N;

	virtual void SetUp() 
	{
		startTime = time(0); 
	}

	virtual void TearDown()
	{
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_TRUE(duration < PIVOT) << "Time exceeded : " << duration;
	}
};

class Time2SecTest : public TimeCriticalTest<Time2SecTest, 2>
{

};

class Time2SecTest_2 : public TimeCriticalTest<Time2SecTest_2, 2>
{

};

// Fails if it took over than 2 seconds.
TEST_F(Time2SecTest, sample)
{
	Sleep(1000 * 3);

}