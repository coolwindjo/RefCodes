#include <iostream>
#include <string.h>
#include <algorithm>	// find()

using namespace std;


#if 0
template<typename T>
T* efind(T* first, T* last, const T value)	// error on 5 for double typed argument
#else
template<typename T1, typename T2>
T1 efind(T1 first, T1 last, const T2 value)
#endif
{
	while (first != last) {
		if (value == *first) {
			break;
		}
		first++;
	}
	return first; // (first == last)? nullptr : first;
}

int main()
{
#if 0
	char s[] = "abcdefg";
			//  01234

	char* p = efind(s, s+4, 'c');
						// half open range
#endif
	double x[10] = {1,2,3,4,5,6,7,8,9,10};

	/*/
	double* p = efind(x, x+10, 5);	// error on 5 for double typed argument
	/*/
	double* p = find(x, x+10, 5);
	//*/

#if 0
	if (nullptr == p) {
#else
	if (x+10 == p) {
#endif
		cout << "failed" <<endl;
	}
	else {
		cout << "success : " << *p <<endl;
	}

	return 0;
}
