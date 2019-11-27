#include <string>
#include "sample1.h"

using namespace std;

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
