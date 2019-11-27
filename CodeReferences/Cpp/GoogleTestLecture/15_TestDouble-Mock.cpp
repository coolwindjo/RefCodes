// 15_TestDouble-Mock.cpp
#include <iostream>

using namespace std;

struct IMP3
{
	virtual void play() = 0;
	virtual ~IMP3() {}
};


class iPod	: public IMP3
{
public:
	iPod();
	~iPod();
	void play() override
	{
		cout << "Play mp3 with iPod" << endl;
	}

private:

};

iPod::iPod()
{
}

iPod::~iPod()
{
}

class Person
{
public:
	Person();
	~Person();

	void playMP3(IMP3* mp3)
	{
		// ...
		mp3->play();
	}
private:

};

Person::Person()
{
}

Person::~Person()
{
}

/////////////////////////////////////////////////////////////////////
// Person 의 playMP3() -> mp3->play() 검증

/*
Mock Object
	: 함수를 호출하였을 때, 발생하는 부작용을 관찰할 수 없어
	Test 안된 Requirement 가 있다면 Mock Object 를 사용한다.
	=> 행위 기반 Test

Mock Object 는 직접 구현해서 사용하는 것이 아니라
 => Mock Framework
	1. Google Mock (The only choice)
	2. jMock, easyMock, Mockito

Google Mock
	jMock, EasyMock, Hamcraest(비교 표현의 확장 Library)
	assertThat(is(), true())
	assertTrue(...)

Test 접근 방식
	1) 상태 검증 - 상태 기반 Test
		: Test 에 검증해야 할 상태가 있을 때, 어떻게 Test 할 것 인가?
			=> SUT 를 실행 후, 상태를 보고 이를 기대값과 비교한다.
	2) 동작 검증 - 행위 기반 Test
		: Test 에 검증해야 할 상태가 없을 때, 어떻게 Test 할 것인가?
			=> 함수의 Return 값이 없거나, 리턴값을 확인하는 것만으로는
				예상대로 동작했음을 보증하기 어려울 때 사용한다.

Google Mock
	1. Static Library Project
	2. src 추가
		gmock-all.cc
		gtest-all.cc
		gmock_main.cc
	3. include path
		$GTEST/googlemock
		$GTEST/googlemock/include
		$GTEST/googletest
		$GTEST/googletest/include

Test Project
	1. include path
		$GTEST/googlemock/include
		$GTEST/googletest/include
	2. gmock Static Library 의 참조
		
Test Double 목적
	목적: 격리 => 원하는 부분을 Test 하고자 한다.
	1) 비결정적 요소를 제어
		시간, Network, File system
	2) 만들어지지 않은 모듈의 의존하는 객체를 Test
	3) 느린 Test
		SUite Fixture => Shared Fixture 문제
	4) 숨겨진 정보를 확인
	5) 행위 기반 검증

Test Double 종류 - xUnit Test Pattern 내용 기반으로 정리 (3,4번은 논란여지)
	1. Stub: 원하는 결과를 제어
	2. Fake object: 진짜 객체가 사용하기 어렵거나, 속도 개선 용도
	3. Test Spy: 접근 불가능한 내부 정보 확인
	4. Mock Object: 행위 기반 Test
*/
#include "gtest\gtest.h"
#include "gmock\gmock.h"

// int -> int
// void play() -> void()

class Mock	: public iPod
{
public:
	Mock();
	~Mock();

	// MOCK_METHOD{인자갯수} (함수이름, 함수타입)
	MOCK_METHOD0(play, void());

private:

};

Mock::Mock()
{
}

Mock::~Mock()
{
}

TEST(PersonTest, playMusic)
{
	Person person;
	/*
	Mock 이 Deleted 될 때, Test 가 실행되므로,
		=> Local object 로 만드는 것이 좋다.
	*/
	Mock mock;

	// 행위 기반 검증 요소를 설정한다.
	EXPECT_CALL(mock, play());

	// Act - the last
	person.playMP3(&mock);
}