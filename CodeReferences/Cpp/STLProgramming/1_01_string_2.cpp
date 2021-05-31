#include <iostream>
#include <string.h>
#include <string>

using namespace std;

int main()
{
	string s1 = "hello";
	char s2[10];

	/*/
	strcpy(s2, s1)	// error! string => const char *
	/*/
	strcpy(s2, s1.c_str());	
	//*/
	cout << s2 <<endl;
	strcpy(s2, s1.data());	// s1.data(): c++11 이전에는 NULL로 끝난다는 보장이 없었음
	cout << s2 <<endl;

	string s3 = "3.4";

	double d = stod(s3);	// stod, stof, stold, stoi, stol, stoll, stoul, stoull
	cout << d <<endl;

	string s4 = to_string(5.4);	// to_string, to_wstring
	cout << s4 <<endl;

	return 0;
}