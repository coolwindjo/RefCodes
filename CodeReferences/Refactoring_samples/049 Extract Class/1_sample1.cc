#include <string>
#include "sample1.h"

using namespace std;

string TelephoneNumber::GetTelephoneNumber()
{
	return "(" + area_code_ + ") " + number_;
}

string TelephoneNumber::GetNumber()
{
	return number_;
}

void TelephoneNumber::SetNumber(string number)
{
	number_ = number;
}

string TelephoneNumber::GetAreaCode()
{
	return area_code_;
}

void TelephoneNumber::SetAreaCode(string area_code)
{
	area_code_ = area_code;
}

string Person::GetName()
{
	return name_;
}

string Person::GetTelephoneNumber()
{
	return "(" + office_area_code_ + ") " + office_number_;
}

string Person::GetOfficeAreaCode()
{
	return office_area_code_;
}

void Person::SetOfficeAreaCode(string arg)
{
	office_area_code_ = arg;
}

string Person::GetOfficeNumber()
{
	return office_number_;
}

void Person::SetOfficeNumber(string arg)
{
	office_number_ = arg;
}
