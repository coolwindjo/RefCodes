#include <string>

using namespace std;


class TelephoneNumber
{
public:
	string GetTelephoneNumber();

	string GetAreaCode();
	void SetAreaCode(string arg);

	string GetNumber();
	void SetNumber(string arg);

private:
	string m_strAreaCode;
	string m_strNumber;

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
	TelephoneNumber m_oOfficeTelephone;
};
