#pragma once
class CoolTests
{
public:
	CoolTests();
	~CoolTests();

    void MatrixTest(void);
    // Generate an Integer Matrix.
	int** genIntMatrix(int rows, int cols, int minVal, int maxVal, double zeroRatio);
	// Delete given Integer Matrix.
	bool delIntMatrix(int** mat, int rows);
	// Print given Integer Matrix.
	void printIntMatrix(int** mat, int rows, int cols);

    // Test general array manipulation.
    int ArrayManipulation(void);
    int LinkedListTest(void);
	int SortingMethods(void);
    // Test Stack and Queue arrays.
    int StackNQueue(void);
    // Test for IO Methods.
	void ReadStringsFromFile(void);
	void ThrdBSTTest(void);
};

