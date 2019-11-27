// 1_GenericProgramming
#include <iostream>
using namespace std;

// �Ϲ��� ���α׷���
// C++ ���̺귯���� �����ϱ� ���ؼ��� �Ϲ�ȭ�� ���� �ؾ� �մϴ�.
// C++ - OOP + �Ϲ�ȭ(Generic)

const int kMaxLen = 100000;
// C�� ���ڿ� �Լ�
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

// 1. �˻� ������ �Ϲ�ȭ : �κ� ���ڿ� �˻� �����ϰ� ����.
// [first, last) - �ݰ� ����
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

// 2. �˻� ��� Ÿ���� �Ϲ�ȭ - template ����
// ������ 1)
// - ������ type�� ã�� ����� type�� �����Ǿ� �ִ�.
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

// ������ 2)
//  - T* ��� �ϸ� Normal pointer�� ����� �� �ִ�. 
//    Smart Pointer�� ����� �� ����. => Iterator!!

#include <vector>
#include <algorithm>  // find

int main()
{
    // ������ 2)
    int x[] = { 1, 2, 3 };
    cout << *find(x, x + 3, 3) << endl;

    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    cout << *find(v.begin(), v.end(), 30) << endl;
    

    // ������ 1)
    int y[] = { 1, 2, 3, 4, 5 };
    int* p3 = xfind(x, x + 5, 3);
    if (p3 != x + 5)
    {
        cout << *p3 << endl;
    }

    //          f      l
    char s[] = "abcdefg";

    // 1. �˻� ������ �Ϲ�ȭ : �κ� ���ڿ� �˻� �����ϰ� ����.
    char* p2 = xstrchr(s, s + 7, 'c');
    if (p2 != NULL)
        cout << *p2 << endl;

    // C�� ���ڿ� �Լ�
    char* p1 = xstrchr(s, 'c');
    if (p1 != NULL)
        cout << *p1 << endl;

    char* p = strchr(s, 'c');
    if (p != NULL)
        cout << *p << endl;

    system("pause");
    return 0;
}
