int main()
{
    int n = 10;

    // 다음 중 Error를 모두 고르세요.
    auto a1 = n;    // OK
    auto a2 = 10;   // OK

    auto& a3 = n;   // OK
    auto& a4 = 10;  // Error

    // 핵심. auto는 항상 T와 유사합니다.
    // auto&& 는 결국 T&&의 의미 입니다.
    // T&& arg = 함수 인자
    // auto&& a = 우변
    auto&& a5 = n;  // auto: int&   auto&&: int& &&     int& a5 = n;    => forwarding reference!!
    auto&& a6 = 10; // auto: int   auto&&: int&&        int& a6 = 10;

    // 핵심. auto&&는 "forwarding reference" 입니다.
    return 0;
}