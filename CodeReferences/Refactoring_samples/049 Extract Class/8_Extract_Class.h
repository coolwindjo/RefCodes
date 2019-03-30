#include <string>

using namespace std;

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
