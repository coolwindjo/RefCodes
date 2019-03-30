#include "8_Extract_Class.h"

using namespace std;


string TelephoneNumber::GetTelephoneNumber()
{
	return "(" + GetAreaCode() + ") " + GetNumber();
}

string TelephoneNumber::GetAreaCode()
{
	return m_strAreaCode;
}

void TelephoneNumber::SetAreaCode(string arg)
{
	m_strAreaCode = arg;
}

string TelephoneNumber::GetNumber()
{
	return m_strNumber;
}

void TelephoneNumber::SetNumber(string arg)
{
	m_strNumber = arg;
}


string Person::GetName()
{
	return name_;
}

string Person::GetTelephoneNumber()
{
	return m_oOfficeTelephone.GetTelephoneNumber();
}

string Person::GetOfficeAreaCode()
{
	return m_oOfficeTelephone.GetAreaCode();
}

void Person::SetOfficeAreaCode(string arg)
{
	m_oOfficeTelephone.SetAreaCode(arg);
}

string Person::GetOfficeNumber()
{
	return m_oOfficeTelephone.GetNumber();
}

void Person::SetOfficeNumber(string arg)
{
	m_oOfficeTelephone.SetNumber(arg);
}
