#include <iostream>

using namespace std;

template<typename T>
void printN(const T& c) { cout << T::N << endl; }

/// Couple primary template
template<typename T, typename U>
struct Couple
{
	T v1;
	U v2;
	static constexpr int N = 2;
};

template<typename T, typename U, typename V>
struct Couple<T, Couple<U, V>>
{
	T 			 v1;
	Couple<U, V> v2;
	static constexpr int N = Couple<U, V>::N + 1;
};

template<typename T, typename U, typename V>
struct Couple<Couple<T, U>, V>
{
	Couple<T, U> v1;
	T 			 v2;
	static constexpr int N = Couple<T, U>::N + 1;
};

template<typename T, typename U, typename V, typename W>
struct Couple<Couple<T, U>, Couple<V, W>>
{
	Couple<T, U> v1;
	Couple<V, W> v2;
	static constexpr int N = Couple<T, U>::N + Couple<V, W>::N;
};

struct Null {};	// Empty class

template<	typename P1,
			typename P2,
			typename P3 = Null,
			typename P4 = Null,
			typename P5 = Null>
class xTuple : public Couple<P1, xTuple<P2, P3, P4, P5, Null>>
{
public:
	static constexpr int N = xTuple<P2, P3, P4, P5, Null>::N + 1;
};

template<	typename P1,
			typename P2>
class xTuple<P1, P2, Null, Null, Null> : public Couple<P1, P2>
{
public:
	static constexpr int N = Couple<P1, P2>::N;
};

int main()
{
	Couple<int, double> c2;
	Couple<int, Couple<int, int>> c3;
	Couple<Couple<int, int>, int> c3_2;
	Couple<int, Couple<int, Couple<int, int>>> c4;
	Couple<Couple<int, int>, Couple<int, int>> c4_2;
	printN(c2);
	printN(c3);
	printN(c3_2);
	printN(c4);
	printN(c4_2);

	//										Couple<double, int>
	//							Couple<s,	xTuple<d, i, N, N, N>>
	//				Couple<c,	xTuple<s, d, i, N, N>>
	// Couple<int,	xTuple<char, short, double, int, Null>>
	xTuple<int, char, short, double, int> t5;
	xTuple<int, char, short> t3;	///< 2 ~ 5 사이를 보관
	printN(t5);
	printN(t3);

	system("pause");
	return 0;
}