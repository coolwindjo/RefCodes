#pragma once
#include "IoMethods.h"
#include "CMatrix.h"

const int  MAX_TERMS = 5000;
const int COL = 529;
const int ROW = 929;

class TestClass
{
private:
	int count_;
public:
	TestClass(void);
	~TestClass(void);
	// For Mobile Harbor Project
	int readVectorMatrixFromFile(void);
	// Read x, y, z values from a file and make three matrices for each value.
	int filterDataIntoMats(void);
};