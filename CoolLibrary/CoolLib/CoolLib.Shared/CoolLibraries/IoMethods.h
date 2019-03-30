#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

class CIoMethods
{
public:
	CIoMethods(void);
	~CIoMethods(void);
	// Read and tokenize integers from given input stream and store them into given integer-list.
	int32_t GetIntegerListFromStream(ifstream* pifStream, int32_t **ppnIntegerList, int32_t nMaxLineLen);
	// Read and tokenize floating numbers from given input stream and store them into given integer-list.
	int32_t GetFloatListFromStream(ifstream* pifStream, float** ppFloatList, int32_t nMaxLineLen);
	// Read a line and store strings in char* array by tokenizing character sequences.
	int32_t GetStringListFromStream(ifstream* pifStream, string** ppstrList, int32_t nMaxLineLen);
	// Read a line and store strings in char* array by tokenizing character sequences with the given delimiter.
	int32_t GetStringListFromStream(ifstream* pifStream, string** ppstrList, int32_t nMaxLineLen, char* delimiter);
	// Get the number of lines and the maximum number of characters on a line.
	int32_t GetLineLengthAndNumOfLines(ifstream* pifStream, int32_t* numLines, int32_t* lineLen);
	// Get the number of lines and the maximum number of strings on a line.
	int32_t GetLineLengthAndNumOfStringsAndLines(ifstream* pifStream, int32_t* numLines, int32_t* maxNumStrings, int32_t* lineLen);
};
