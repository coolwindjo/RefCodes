#include <iostream>
#include <fstream>

#include "CoolLib.h"

using namespace std;

#define CHECK_CREDIT(x) \
		((x) >= 5)&&((x) <= 1000)
#define CHECK_PRICE(x) \
		((x) >= 1)&&((x) <= 1000)
#define CHECK_NUM_CASES(x) \
		((x) == 10)||((x) == 50)
#define CHECK_NUM_ITEMS(x,y) \
		((x) >= 3)&&((x) <= (((y)==10)?100:2000))

int main()
{
	ifstream fin;
	fin.open("A-small-practice.in");
	if (fin.fail())
	{
		cerr << "Error: file open error." << endl;
		exit(EXIT_FAILURE);
	}

	// TO DO
	int nCases;

	fin >> nCases;
	if (!CHECK_NUM_CASES(nCases))
	{
		cerr << "Error: invalid case number value." << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < nCases; i++)
	{
		int nCredits, nItems;

		fin >> nCredits;
		if (!CHECK_CREDIT(nCredits))
		{
			cerr << "Error: invalid credit value." << endl;
			exit(EXIT_FAILURE);
		}

		fin >> nItems;
		if (!CHECK_NUM_ITEMS(nItems, nCases))
		{
			cerr << "Error: invalid item number value." << endl;
			exit(EXIT_FAILURE);
		}
		int *pnPrices = new int[nItems];
		for (int j = 0; j < nItems; j++)
		{
			fin >> pnPrices[j];
		}

		CoolLib::CCoolLib cool;
		cool.SRT_Create();



		delete[] pnPrices;
	}

	// FINISH
	fin.close();
	return 0;
}