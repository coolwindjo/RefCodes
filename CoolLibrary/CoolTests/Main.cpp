#pragma once
#include <iostream>

#include "CoolLib.h"
#include "CoolTests.h"

using namespace std;

int32_t main(int32_t argc, char* argv[])
{
	// Usage Notice
	if (argc != 1) {
		cout << "Usage: " << argv[0] << " Do Nothing\n";
		exit(EXIT_FAILURE);
	}

	// Store file names.
	string programName;
	programName = argv[0];
	if (programName.rfind(".") == string::npos)
		programName += ".exe";
	// In others words...
    //	strncpy_s(programName, sizeof(programName), argv[0], MAX_FILENAME_LEN);
	//	if ( strchr(programName, '.') == NULL )
	//		strncat_s(programName, sizeof(programName), ".exe", 5);

	// Using Cool Library.
	CoolLib::CCoolLib cool;
	CoolTests test;

	cool.Timer.TimerOn("Tests");

    test.LinkedListTest();

 //   test.ArrayManipulation();
	//test.ThrdBSTTest();
	//test.MatrixTest();
	//int32_t** mat = test.genIntMatrix(20, 10, 133, 1134, 0.3);
	//test.printIntMatrix(mat, 20, 10);
	//if (test.delIntMatrix(mat, 10))
	//	cout << "Good deletion!" << endl;
	//test.StackNQueue();
	//test.SortingMethods();

	cool.Timer.TimerOff();

	system("PAUSE");

	return 0;
}
