#include "sample1.h"
#include "gtest/gtest.h"

TEST(ReplaceParameterWithExplicitMethods, createEmployee)
{
	EXPECT_EQ(VISUALSTUDIO, createEmployee(ENGINEER));
	EXPECT_EQ(EXCEL, createEmployee(SALESMAN));
	EXPECT_EQ(POWERPOINT, createEmployee(MANAGER));
}
