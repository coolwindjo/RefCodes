// C++ STL���� �ݺ��ڸ� ����ϱ� ���ؼ��� �ݵ�� �����ؾ� �մϴ�.

// �ݺ��� ���� (iterator category)
//  : �ڷᱸ���� ���¿� ���� ���������� �����ϴ� ������ �����ε��� ���°� �ٸ���.
// 1. �Է� �ݺ���            =*p, ++
// 2. ��� �ݺ���            *p=, ++
// 3. ������ �ݺ���       �����, ++             => slist
// 4. ����� �ݺ���       �����, ++, --         => list
// 5. �������� �ݺ���  �����, ++, --, +, - []    => ���ӵ� �޸�(RandomAccessIterator)

//  list<>      - ���� ���� ����Ʈ
//  vector<>    - �迭        [] 

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