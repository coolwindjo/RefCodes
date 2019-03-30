#include <string>

using namespace std;

class TelephoneNumber {
public:
	string GetTelephoneNumber();
	string GetNumber();
	void SetNumber(string number);
	string GetAreaCode();
	void SetAreaCode(string area_code);

private:
	string number_;
	string area_code_;
};

class Person {
public:
	string GetName();
	string GetTelephoneNumber();
	string GetOfficeAreaCode();
	void SetOfficeAreaCode(string arg);
	string GetOfficeNumber();
	void SetOfficeNumber(string arg);

private:
	string name_;
	string office_area_code_;
	string office_number_;
};
