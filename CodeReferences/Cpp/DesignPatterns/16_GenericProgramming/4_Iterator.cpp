// 반복자 (Iterator): GoF's Design Pattern
// 의도: Container의 내부 구조에 상관 없이 요소를 열거할 수 있는 패턴

// vector<int>::iterator p = v.begin();
//  - generic interface
//  - 일반적 프로그래밍(Algorithm)
//      장점: 모든 것이 static binding 기반의 함수 이므로 inline화 가능하다.
//          성능이 좋다.
//      단점: 내부의 모든 약속이 코드로 드러나지 않기 때문에,문제가 발생했을 경우,
//          문제의 원인을 찾기 어렵다.

// Iterator<Integer> p = arr.iterator();
//  장점: interface 코드를 통해 약속되므로, 쉽게 사용 가능하다.
//  단점: virtual function 기반으로 동작하기 때문에, 성능 저하가 있다.
//      모든 Collection이 동일한 method를 제공해야 하므로 중복이 발생한다.

// Java - Collections -> sort, find ....

// C++진영의 다형성
// 실행 시간 다형성
// 장점: 여러 동물을 전달해도, 함수는 한개이다.
// 단점: 가상 함수 기반. 느리다.
//void foo(Animal* p) { p->cry(); }

// 컴파일 시간 다형성
// 단점: 여러 동물을 보내면 foo()는 여러개 생성된다. 코드 메모리 부하가 있다.
// 장점: 인라인화 가능하다. 빠르다.
//template <typename T>
//void foo(T& p) { p.cry(); }
