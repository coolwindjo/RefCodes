// 4_�Լ�������

#include <iostream>
using namespace std;

// inline ġȯ�� �ϸ� ���ɸ鿡�� ���̵� => ������ Function pointer�� �����ϸ� ġȯ �ȵ�
bool cmp1(int a, int b)
//inline bool cmp1(int a, int b)
{
    return a > b;
}
bool cmp2(int a, int b)
//inline bool cmp2(int a, int b)
{
    return a < b;
}

// ������ �ʴ� ��ü �˰��򿡼� ���ؾ� �ϴ� ��å �ڵ�� �и��Ǿ�� �Ѵ�.
// => �Ϲ� �Լ� ������ ���ϴ� ���� �Լ� ����(Function Pointer)�� �̾Ƴ��� �ȴ�.
void sort(int* x, int n, bool (*cmp)(int, int))
{
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; j++)
            //if (x[i] > x[j])
            if (cmp(x[i], x[j]))
                swap(x[i], x[j]);
}

int main()
{
    int x[10] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
    //sort(x, 10, cmp2);
    sort(x, 10, cmp1);

    for (int i = 0; i < 10; ++i)
        cout << x[i] << endl;

    system("pause");
    return 0;
}