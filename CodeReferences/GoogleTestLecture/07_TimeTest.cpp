// 7_TimeTest.cpp
#include <Windows.h>

/*
���� Test
	=> JUnit4������ �����ϴ� ���
*/
#include <stdio.h>
#include <time.h>
#include "gtest\gtest.h"

/*
CRTP : Curiously Recurring Template Pattern
	: �پ��� Ȱ���� �����ѵ�, �θ��� Static Member Variable �� �и��ϴ� ���.
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