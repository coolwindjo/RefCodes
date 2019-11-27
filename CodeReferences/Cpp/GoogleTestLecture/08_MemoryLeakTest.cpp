// 8_MemoryLeakTest.cpp
#include "gtest\gtest.h"
#define LEAK_TEST

class Image
{
public:
#ifdef LEAK_TEST
	static int allocObjectCount;

	void* operator new(size_t sz)
	{
		++allocObjectCount;
		return malloc(sz);
	}

	void operator delete(void* p, size_t)
	{
		--allocObjectCount;
		free(p);
	}
#endif	// #ifdef LEAK_TEST
};

#ifdef LEAK_TEST
int Image::allocObjectCount = 0;
#endif	// #ifdef LEAK_TEST

class ImageTest	: public ::testing::Test
{
protected:
	int allocCount;

	virtual void SetUp()
	{
		allocCount = Image::allocObjectCount;
	}

	virtual void TearDown()
	{
		int diff = Image::allocObjectCount - allocCount;
		EXPECT_EQ(diff, 0) << "Leak! - " << diff;
	}
};

void foo()
{
	// operator new()
	Image* image = new Image;
	delete image;
}

TEST_F(ImageTest, sample)
{
	foo();
	// ...
}