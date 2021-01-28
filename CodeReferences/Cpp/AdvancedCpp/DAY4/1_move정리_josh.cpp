// move 정리

// Class 사용자
// ==> Algorithm 만들 때, std::move()를 사용 할 수 있다고 기억해주세요.
// Class 제작자
// 1. 복사 생성자와 move 생성자를 만들지 않는 것은 가장 좋습니다.

// 2. move 생성자를 만들어야 한다면,
//  A. 모든 Member를 move로 옮기세요.
//  B. 되도록이면 예외 없이 만들고 noexcept를 붙이세요.

// 생성자와 setter를 만들때,
// ==> move를 지원하게 만드세요!
// ==>  A. const T& Version과 T&& Version으로 2개 만들거나,
//      B. forwarding reference 사용