#include "sample1.h"
#include "gtest/gtest.h"

TEST(RemoveControlFlag, checkSecurity)
{
	char* people1[] = {"Kim", "Lee", "Park"};
	EXPECT_EQ(0, checkSecurity(people1, 3));

	char* people2[] = {"Kim", "John", "Lee"};
	EXPECT_EQ(1, checkSecurity(people2, 3));
}
