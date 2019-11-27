// 1_GenericProgramming
#include <iostream>
using namespace std;

// 일반적 프로그래밍
// C++ 라이브러리를 이해하기 위해서는 일반화를 이해 해야 합니다.
// C++ - OOP + 일반화(Generic)

const int kMaxLen = 100000;
// C의 문자열 함수
char* xstrchr(char* s, char c)
{
    for (int i = 0; 
    (*s != '\0') && (*s != c) 
        && (i < kMaxLen); ++i)
    {
        ++s;
    }
    return *s == c ? s : NULL;
}

// 1. 검색 구간의 일반화 : 부분 문자열 검색 가능하게 하자.
// [first, last) - 반개 구간
char* xstrchr(char* first, char* last, char value)
{
    for (int i = 0; 
    (first != last) && (*first != value) 
        && (i < kMaxLen); ++i)
    {
        ++first;
    }
    
    //return first == last ? NULL : first;
    return first;
}

// 2. 검색 대상 타입의 일반화 - template 도입
// 문제점 1)
// - 구간의 type과 찾는 요소의 type이 연관되어 있다.
/* <- '/'
template <typename T>
T* xfind(T* first, T* last, T value)
/*/
template <typename T1, typename T2>
T1* xfind(T1* first, T1* last, T2 value)
//*/
{
    while (first != last && *first != value)
        ++first;

    return first;
}

// 문제점 2)
//  - T* 라고 하면 Normal pointer만 사용할 수 있다. 
//    Smart Pointer를 사용할 수 없다. => Iterator!!

#include <vector>
#include <algorithm>  // find

int main()
{
    // 문제점 2)
    int x[] = { 1, 2, 3 };
    cout << *find(x, x + 3, 3) << endl;

    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    cout << *find(v.begin(), v.end(), 30) << endl;
    

    // 문제점 1)
    int y[] = { 1, 2, 3, 4, 5 };
    int* p3 = xfind(x, x + 5, 3);
    if (p3 != x + 5)
    {
        cout << *p3 << endl;
    }

    //          f      l
    char s[] = "abcdefg";

    // 1. 검색 구간의 일반화 : 부분 문자열 검색 가능하게 하자.
    char* p2 = xstrchr(s, s + 7, 'c');
    if (p2 != NULL)
        cout << *p2 << endl;

    // C의 문자열 함수
    char* p1 = xstrchr(s, 'c');
    if (p1 != NULL)
        cout << *p1 << endl;

    char* p = strchr(s, 'c');
    if (p != NULL)
        cout << *p << endl;

    system("pause");
    return 0;
}
