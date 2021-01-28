#include <iostream>
#include <vector>

// STL의 vector의 구현을 생각해봅시다.
template<typename T> class vector
{
    T* buff;
    int size;
public:
    vector(int sz) : size(sz)
    {
        buff = new T[size];
    }
    T& operator[](int idx) { return buff[idx]; }
};

// vector<bool> 은 특수화 되어 있습니다.
template<> class vector<bool>
{
    int* buff;
    int size;
public:
    vector(int sz) : size(sz)
    {
        buff = new int[(size/32) + 1];
    }

    // 아래 Code가 "Temporary proxy" 라는 이름을 가진 기술
    class BitProxy
    {
    private:
        int* buff;
        int idx;
    public:
        BitProxy(int* p, int n) : buff(p), idx(n) {}
        ~BitProxy() {}

        BitProxy& operator=(bool b)
        {
            std::cout<< buff << "주소의 " << idx << "-Index번째 Bit를 " << b << "로 채운다." <<std::endl;
            return *this;
        }

    };
    
    // 아래 함수 Return type을 어떻게 해야 할까요?
    BitProxy& operator[](int idx) { return BitProxy(buff[idx]); }
};


int main()
{
    std::vector<bool> v = {1,1,1,1,1};

    v[0] = 0

    return 0;
}