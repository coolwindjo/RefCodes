int x = 10;
int foo()  { return x; } // x의 값(10)을 리턴
int& goo() { return x; } // x의 메모리 정보 반환..

// lvalue : 등호의 양쪽에 올수 있다.(lvalue 는 rvalue 로 암시적 변환된다.)
//			값과 이름이 있고
//			단일 문장을 벗어나서도 사용할수 있다.
//			주소 연산자로 주소를 구할수 있다.
//			참조를 반환하는 함수

// rvalue : 등호의 오른쪽에만 올수 있는것.
//			값만 있고, 이름이 없다.
//			단일 문장에서만 사용가능.	
//			주소 연산자로 주소를 구할수 없다.
//			값을 반환하는 함수 
//			임시객체, 리터럴(10, 3.4)
int main()
{
	int v1 = 10, v2 = 10;  // mov v2주소, 10
	
	v1 = 20;	// v1 : lvalue    20 : rvalue 
	10 = v1;
	v2 = v1;

	int* p1 = &v1;
	int* p2 = &10; 

	foo() = 20; // error.. 10 = 20
	goo() = 20; // ok..

	const int c = 10;
	c = 20;				// c는 rvalue 일까요 ? lvalue 일까요 ?
						// c 는 immutable lvalue 입니다.

	// 모든 rvalue 는 상수이다.?? = 아니다.!!!
	//							문법상 왼쪽에 올수 없다..!
	Point(1, 2).x = 10;// error
	Point(1, 2).set(1, 2); //ok
}









