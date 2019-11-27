#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

class IoMethods
{
public:
	IoMethods(void);
	~IoMethods(void);
	// Read and tokenize integers from given input stream and store them into given integer-list.
	int tokenizeIntegersByLine(ifstream* inputStream, int* integerList, int maxLineLen);
	// Read and tokenize floating numbers from given input stream and store them into given integer-list.
	int tokenizeFloatsByLine(ifstream* inputStream, float* floatList, int maxLineLen);
	// Read a line and store strings in char* array by tokenizing character sequences.
	int readStringsByLine(ifstream* inputStream, string* strList, int maxLineLen);
	// Read a line and store strings in char* array by tokenizing character sequences with the given delimiter.
	int readStringsByLine(ifstream* inputStream, string* strList, int maxLineLen, char* delimiter);
	// Get the number of lines and the maximum number of characters on a line.
	int getLineLengthAndNumOfLines(ifstream* inputStream, int* numLines, int* lineLen);
	// Get the number of lines and the maximum number of strings on a line.
	int getLineLengthAndNumOfStringsAndLines(ifstream* inputStream, int* numLines
		, int* maxNumStrings, int* lineLen);
};
