
/* [작성 내용] */
/* 1. 테스트 케이스를 아래 배열에 추가하시오 개수는 8개 고정. 배열의 이름은 수정 불가함 */
/* 2. 테스트 케이스 배열 구조 : { 미세먼지측정값1, ..., 미세먼지측정값8 } */
/* 예를 들어, { 101, 101, 100, 50, 30, 51, 75, 100 }는 */
/* 미세먼지측정값이 101, 101, 100, 50, 30, 51, 75, 100 순으로 감지됨을 의미한다. */
int testInput_example[8] = { 101, 101, 100, 50, 30, 51, 75, 100 };

int testInput_1_1[8] = { 30, 50, 60, 110, 60, 110, 60, 110/*[FIXME]*/, }; // TODO: 항목 1-1 테스트 입력을 추가하시오.
int testInput_1_2[8] = { 30, 50, 60, 60, 110, 110, 60, 40/*[FIXME]*/, }; // TODO: 항목 1-2 테스트 입력을 추가하시오.
int testInput_1_3[8] = { 30, 110, 50, 50, 110, 110, 60, 110/*[FIXME]*/, }; // TODO: 항목 1-3 테스트 입력을 추가하시오.




#include "./lib/device.h"
/* device.h에는 대략적으로 아래와 같이 구현된 함수의 정의가 있다.
 * 구현 참고용이므로 본 주석을 풀어서 아래 코드를 사용해서는 안된다.  (device.h에 포함된 내용임)
 * 아래 주석을 해제하여 사용하는 경우 정상적으로 동작하지 않는다.


/*
 *  현재 센서에서 감지한 미세먼지 측정값을 반환하는 인터페이스
 *
int getCurrentPM(); 

/*
 * 바람 세기와 누적 부하량 계산하여 결정한 바람 세기를 반환 (테스트 대상)
 *
int determineWindStrength()
{
	int pm = getCurrentPM(); //미세먼지측정값은 getCurrentPM()함수를 호출해서 얻는다.
	
	int polutionLevel = mapToPolutionLevel(pm); // 미세먼지량에_따른_오염도
	int result = mapToWindStrength(polutionLevel); // 오염도에_따른_바람세기

	if (isTurboModeBeginCondition(polutionLevel))
		turboMode = TRUE;
	else if (isTurboModeEndCondition(polutionLevel))
		turboMode = FALSE;
		
	if (turboMode)
		result = TURBO_MODE;
	
	totalLoad += getLoadOf(result); // 바람 세기에 따른 부하량을 계산하여 누적
	
	return result;
}
*/



int count = 0;
int* fakeDust;

int getCurrentPM()
{
	// TODO: 원하는 미세먼지측정값을 전달할 수 있도록 fake/stub을 구현하시오.

	return fakeDust[count++]; // FIXME: 필요한 코드로 대체하시오.
}


void test_2_1()
{
	// TODO: 항목 2-1. 
	// 미세 먼지 단계가 (매우 나쁨, 매우 나쁨, 나쁨, 보통, 나쁨, 나쁨, 나쁨) 순으로 7개가 감지되는 경우를 재현하는 코드를 작성하라.
	int input[] = { 110, 110, 60, 40, 60, 60, 60 };
	fakeDust = input;
	count = 0;
	for (int i = 0; i < 7; ++i)
		determineWindStrength();
}

void test_2_2()
{
	// TODO: 항목 2-2. 
	// 세 먼지 단계가 (매우 나쁨, 나쁨, 나쁨, 매우 나쁨, 나쁨, 좋음, 나쁨, 매우 나쁨, 나쁨, 매우 나쁨, 나쁨) 순으로 11개가 감지되는 경우를 재현하는 코드를 작성하라.
	int input[] = { 110, 60, 60, 110, 60, 20, 60, 110, 60, 110, 60 };
	//int input[] = { 111, 70, 70, 70, 110, 10, 70, 170, 70, 110, 70 };  // 이제 정답 처리되는 문제가 있었음
	fakeDust = input;
	count = 0;
	for (int i = 0; i < 11; ++i)
		determineWindStrength();
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