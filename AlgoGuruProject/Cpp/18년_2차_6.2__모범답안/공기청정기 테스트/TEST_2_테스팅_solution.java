import device.AirPurifier;
import device.ParticleSensor;
import device.TestUtils;

// 테스트 대상은 아래 주석과 같이 구현되어 있다. 
// 필요한 경우 아래 주석의 내용을 참고하여 LedTest class에 테스트 입력과 테스트 코드를 작성하시오. 
// NOTE: 테스트 대상 코드는 빌드에 이미 포함되어 있으니 아래 주석을 해제하여 사용하지 마시오.

/**
 * ParticleSensor.java
 * 현재 센서에서 감지한 미세먼지 측정값을 반환하는 인터페이스
 *
package device;

public interface ParticleSensor {
 	**
	 * @return 현재 센서에서 감지한 미세먼지 측정값
	 *
	int getcurrentPM();
}
*/

/**
 * AirPurifier.java
 * 공기 청정기를 제어 (테스트 대상)
 * 
package device;

...

public class AirPurifier {
	...
	private ParticleSensor sensor;
	private boolean turboMode = false;
	private int totalLoad = 0;
	
	public AirPurifier(ParticleSensor sensor) {
		this.sensor = sensor;
		...
	}

	**
	 * 바람 세기와 누적 부하량 계산하여 결정한 바람 세기를 반환 (테스트 대상)
	 *
	public WindStrength determineWindStrength() {
		int pm = sensor.getCurrentPM();

		PolutionLevel polutionLevel = mapToPolutionLevel(pm); // 미세먼지량에_따른_오염도
		WindStrength result = mapToWindStrength(polutionLevel); // 오염도에_따른_바람세기
	
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
}
*/


public class AirPurifierTest {
	
	/* [작성 내용] */
	/* 1. 테스트 케이스를 아래 배열에 추가하시오 개수는 8개 고정. 배열의 이름은 수정 불가함 */
	/* 2. 테스트 케이스 배열 구조 : { 미세먼지측정값1, ..., 미세먼지측정값8 } */
	/* 예를 들어, { 101, 101, 100, 50, 30, 51, 75, 100 }는 */
	/* 미세먼지측정값이 101, 101, 100, 50, 30, 51, 75, 100 순으로 감지됨을 의미한다. */
	
	public int[] testInputSample = { 101, 101, 100, 50, 30, 51, 75, 100 };
	public int[] testInput_1_1 = {30, 50, 60, 110, 60, 110, 60, 110};
	public int[] testInput_1_2 = {30, 50, 60, 60, 110, 110, 60, 40};
	public int[] testInput_1_3 = {30, 110, 50, 50, 110, 110, 60, 110};
	
	public void test_2_1() {
		// TODO: 항목 2-1. 
		// 미세 먼지 단계가 (매우 나쁨, 매우 나쁨, 나쁨, 보통, 나쁨, 나쁨, 나쁨) 순으로 7개가 감지되는 경우를 재현하는 코드를 작성하라.
		AirPurifier device = new AirPurifier(new ParticleSensor() {
			
			private int count = 0;
			private int[] fakePM = {110, 130, 60, 40, 60, 60, 60};

			@Override
			public int getcurrentPM() {
				// TODO Auto-generated method stub
				return fakePM[count++];
			}
		});
		
		for (int i = 0; i < 7; ++i)
			device.determineWindStrength();
	}

	public void test_2_2() {
		// TODO: 항목 2-2. 
		// 세 먼지 단계가 (매우 나쁨, 나쁨, 나쁨, 매우 나쁨, 나쁨, 좋음, 나쁨, 매우 나쁨, 나쁨, 매우 나쁨, 나쁨) 순으로 11개가 감지되는 경우를 재현하는 코드를 작성하라.
		AirPurifier device = new AirPurifier(new ParticleSensor() {
			
			private int count = 0;
			private int[] fakePM = {110, 60, 60, 110, 60, 10, 60, 140, 60, 160, 60};

			@Override
			public int getcurrentPM() {
				// TODO Auto-generated method stub
				return fakePM[count++];
			}
		});
		
		for (int i = 0; i < 11; ++i)
			device.determineWindStrength();
	}

	// 참고용으로 실행하고 싶은 코드가 있다면 아래 main()에 작성하여 활용할 수 있다.
	// main 함수의 코드는 채점과 관련이 없다.
	public static void main(String[] args) {
		 //printTestResult는  testInput의 내용을 테스트 입력으로 수행한 결과를 화면에 출력해준다.
		AirPurifierTest runner = new AirPurifierTest();
		TestUtils.printTestResult(runner.testInputSample);
		TestUtils.printTestResult(runner.testInput_1_1);
		TestUtils.printTestResult(runner.testInput_1_2);
		TestUtils.printTestResult(runner.testInput_1_3);
		
		runner.test_2_1();
		runner.test_2_2();
	}
}
