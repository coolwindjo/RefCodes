#include "8_Extract_Class.h"
#include "gtest/gtest.h"
#include <string>
#include <iostream>

using namespace std;

TEST(PersonTelephoneTC, TelephoneNumTest)
{
	Person p;
	int len = 0;
	p.SetOfficeAreaCode("032");
	p.SetOfficeNumber("723-0947");
	EXPECT_STREQ("(032) 723-0947", p.GetTelephoneNumber().c_str());
	EXPECT_EQ(14, len = p.GetTelephoneNumber().length());
	cout << "Length: "<< len << "  Num: " << p.GetTelephoneNumber() <<endl;
}
