#include "Practices.h"

#if 1
class CPractice : public IProbSolv
{
    int m_N;
public:
    CPractice(const int N)
        : m_N(N)
    {}
    ~CPractice(){}
private:
    void _Solve(){
        cout << _Test() <<endl;
    }
    int _Test(){
        return 0;
    }
};

#endif

class CIterator : public IProbSolv
{
public:
    CIterator()
    {}
    ~CIterator(){}
private:
    void _Solve(){
        // An iterator is a general concept:
        //   just like "numbers" include int, float, unsigned short, and other similar types,
        //   so do "iterators" include std::vector<T>::const_iterator, std::istream_iterator<T>, std::map<K,V>::iterator or T*.
        // An iterator, at its core, is something which allows you to iterate over a sequence (++it and/or it++ to advance to the next element),
        //   to represent a sequence or subsequence (as begin and end values),
        //   and to access the elements of that sequence (*it, either write-only, read-only, or read-write).
        // Other properties may be added, such as the ability to move backwards (--it, in a bidirectional iterator)
        //   or the ability to skip several values (it + 5, in a random-access iterator).
        // Pointers are bidirectional random-access iterators,
        //   with an extra property: there is, for every type, a special pointer value called the null pointer (which does not have an associated sequence or element).
        // Comparing two pointers together is safe as long as they are within the same sequence or one of them is the null pointer. 
        cout << _TestRawPointer() <<endl;
        cout << _TestVectorPointer() <<endl;
        cout << _TestIterator() <<endl;
    }
    int _TestRawPointer(){
        vi viArr = {10, 11, 12};
        int* p = &viArr[0];
        p++;
        p--;
        p+=2;
        // while(p != viArr.end()){
        //     p++;
        // }
        // The raw pointer type, int*, 
        // tells you very little about what p is,
        // except that it stores the address of an int.
        return *p;
    }

    int _TestVectorPointer(){
        vi viArr = {10, 11, 12};
        vi::pointer p = viArr.data();
        p++;
        p--;
        p+=2;
        // while(p != viArr.end()){
        //     p++;
        // }
        return *p;
    }

    int _TestIterator(){
        vi viArr = {10, 11, 12};
        vi::iterator i = viArr.begin();
        // i++;
        // i--;
        // i+=2;
        while(i != viArr.end()){
            i++;
        }
        i--;
        // vector<int>::iterator tells you everything you need to know.
        // It explicitly states that the object is an iterator
        // and that iterator is used to point at elements in a vector<int>.
        // This also has the benefit of being more easily maintainable
        // if you ever happen to change the container type.
        
        // Iterators are a generalization of pointers,
        //   abstracting from their requirements in a way that allows a C++ program
        //   to work with different data structures in a uniform manner.
        // Iterators act as intermediaries between containers and generic algorithms.
        // Instead of operating on specific data types,
        //   algorithms are defined to operate on a range specified by a type of iterator.
        // Any data structure that satisfies the requirements of the iterator
        //   may then be operated on by the algorithm.
        // There are five types or categories of iterator,
        //   each with its own set of requirements and resulting functionality:
        // Random access: elements accessed in any order, may store and retrieve values,
        //   provided by vector, deque, string, and array.
        // - Bidirectional: forward and backward moving, may store and retrieve values,
        //     provided by list, set, multiset, map, and multimap.
        // -- Forward: forward moving, may store and retrieve values.
        // --- Output: forward moving, may store but not retrieve values,
        //       provided by ostream and inserter.
        // --- Input: forward moving, may retrieve but not store values,
        //       provided by istream.
        // Iterators that have greater requirements and so more powerful access to elements
        //   may be used in place of iterators with fewer requirements.
        // For example, if a forward iterator is called for, then a random-access iterator may used instead. 

        return *i;
    }

};

class CGeneralGCD : public IProbSolv
{
    int m_nNum;
    int* m_arnVal;
public:
    CGeneralGCD(const int num, int arr[])
        : m_nNum(num)
        , m_arnVal(arr)
    {}
    ~CGeneralGCD(){}
private:
    void _Solve(){
        cout << generalizedGCD(m_nNum, m_arnVal) <<endl;
    }

    int gcd(const int a, const int b){
        if (b == 0)
            return a;
        return gcd(b, (a%b));
    }

    int generalizedGCD(int num, int* arr)
    {
        // WRITE YOUR CODE HERE  
        int ans = arr[0];
        for(int i=1; i<num; i++){
            ans = gcd(arr[i], ans);
        }
        return ans;
    }
    
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    CIterator oIter;
    oIter.Solve();

    int arr[5] = {2,4,6,8,10};
    CGeneralGCD oGenGCD(5, arr);
    oGenGCD.Solve();

    return 0;
}
