// C++ STL에서 반복자를 사용하기 위해서는 반드시 이해해야 합니다.

// 반복자 종류 (iterator category)
//  : 자료구조의 형태에 따라서 내부적으로 지원하는 연산자 오버로딩의 형태가 다르다.
// 1. 입력 반복자            =*p, ++
// 2. 출력 반복자            *p=, ++
// 3. 전진형 반복자       입출력, ++             => slist
// 4. 양방향 반복자       입출력, ++, --         => list
// 5. 임의접근 반복자  입출력, ++, --, +, - []    => 연속된 메모리(RandomAccessIterator)

//  list<>      - 이중 연결 리스트
//  vector<>    - 배열        [] 

#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <algorithm>
using namespace std;

int main()
{
    //vector<int> v;
    list<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    //vector<int>::iterator p = find(v.begin(), v.end(), 20);
    auto p1 = find(v.begin(), v.end(), 20);
    cout << *p1 << endl;


    array<int, 5> arr;
    arr.assign(10);
    arr.assign(20);
    arr.assign(30);

    //auto p2 = find(arr.begin(), arr.end(), 20);
    //cout << p2 << endl;????????????????????????????????????


    // List<Integer> s =new ArrayList<>();
    // 
    int x[10] = { 1,3,5,7,9,2,4,6,8,10 };
    sort(x, x + 10);

    system("pause");
    return 0;
}