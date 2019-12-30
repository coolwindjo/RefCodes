
/* [작성 내용] */
/* 1. 테스트 케이스를 아래 배열에 추가하시오 개수는 8개 고정. 배열의 이름은 수정 불가함 */
/* 2. 테스트 케이스 배열 구조 : { 미세먼지측정값1, ..., 미세먼지측정값8 } */
/* 예를 들어, { 101, 101, 100, 50, 30, 51, 75, 100 }는 */
/* 미세먼지측정값이 101, 101, 100, 50, 30, 51, 75, 100 순으로 감지됨을 의미한다. */
int testInput_example[8] = { 101, 101, 100, 50, 30, 51, 75, 100 };

int testInput_1_1[8] = { 30, 50, 60, 110, 60, 110, 60, 110/*[FIXME]*/, }; // TODO: 항목 1-1 테스트 입력을 추가하시오.
int testInput_1_2[8] = { 30, 50, 60, 60, 110, 110, 60, 40/*[FIXME]*/, }; // TODO: 항목 1-2 테스트 입력을 추가하시오.
int testInput_1_3[8] = { 30, 110, 50, 50, 110, 110, 60, 110/*[FIXME]*/, }; // TODO: 항목 1-3 테스트 입력을 추가하시오.




#include "./lib/AirPurifier.h"

/*
 * 아래는 테스트 대상인 AirPurifier class와 관련 interface 코드이다.
 * 구현 참고용이므로 본 주석을 풀어서 아래 코드를 사용해서는 안된다.  (AirPurifier.h에 포함된 내용임)
 * 아래 주석을 해제하여 사용하는 경우 정상적으로 동작하지 않는다.

class Sensor
{
public:
	/*
	 *  현재 센서에서 감지한 미세먼지 측정값을 반환하는 인터페이스
	 *
	virtual int getCurrentPM() = 0;
};

class AirPurifier
{
public:
	AirPurifier(Sensor& sensor) : sensor_(sensor) { ... }

	/*
	 * 바람 세기와 누적 부하량 계산하여 결정한 바람 세기를 반환 (테스트 대상)
	 *
	int determineWindStrength()
	{
		int pm = sensor_.getCurrentPM();

		int polutionLevel = mapToPolutionLevel(pm); // 미세먼지량에_따른_오염도
		int result = mapToWindStrength(polutionLevel); // 오염도에_따른_바람세기
	
		if (isTurboModeBeginCondition(polutionLevel))
			turboMode_ = true;
		else if (isTurboModeEndCondition(polutionLevel))
			turboMode_ = false;
		
		if (turboMode_)
			result = TURBO_MODE;
	
		totalLoad_ += getLoadOf(result); // 바람 세기에 따른 부하량을 계산하여 누적
		
		return result;
	}

	...

private:
	Sensor& sensor_;
	int totalLoad_;
	bool turboMode_;
	...
};
*/



class FakeSensor : public Sensor
{
	int* fakePM;
	int count = 0;
public:
	FakeSensor(int* input) : fakePM(input) {}

	int getCurrentPM() {
		return fakePM[count++];
	}
};

void test_2_1()
{
	// TODO: 항목 2-1. 
	// 미세 먼지 단계가 (매우 나쁨, 매우 나쁨, 나쁨, 보통, 나쁨, 나쁨, 나쁨) 순으로 7개가 감지되는 경우를 재현하는 코드를 작성하라.
	int fakeInputs[] = {111, 111, 70, 40, 70, 70, 70};
	FakeSensor fakeSensor(fakeInputs);
	AirPurifier device(fakeSensor);

	for (int i = 0; i < 7; ++i)
		device.determineWindStrength();
}

void test_2_2()
{
	// TODO: 항목 2-2. 
	// 세 먼지 단계가 (매우 나쁨, 나쁨, 나쁨, 매우 나쁨, 나쁨, 좋음, 나쁨, 매우 나쁨, 나쁨, 매우 나쁨, 나쁨) 순으로 11개가 감지되는 경우를 재현하는 코드를 작성하라.
	int fakeInputs[] = { 111, 70, 70, 110, 70, 10, 70, 170, 70, 110, 70 };
	//int fakeInputs[] = { 111, 70, 70, 70, 110, 10, 70, 170, 70, 110, 70 };  // 이제 정답 처리되는 문제가 있었음
	FakeSensor fakeSensor(fakeInputs);
	AirPurifier device(fakeSensor);

	for (int i = 0; i < 11; ++i)
		device.determineWindStrength();
}


/* main 함수는 작성한 테스트 케이스 검증용임 */
/* 필요에 따라서 마음대로 변경하어도 무방함 */
/* main 함수는 채점과 무관함 */


int main()
{
	printTestResults();  // testInput에 기록한 테스트 입력으로 실행한 결과를 출력해준다. (수험자 확인용)

	test_2_1();

	test_2_2();

	return 0;
}