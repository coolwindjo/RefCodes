#include "sample1.h"
#include "gtest/gtest.h"

TEST(SeparateQueryFromModifier, foundMiscreant)
{
	char* people[] = {"Kim", "Lee", "John"};
	EXPECT_EQ(4, checkSecurity(people, 3));
}
