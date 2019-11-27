#include "testclass.h"

int main(int argc, char* argv[])
{
	if (argc != 1) {
		cout <<		"Usage: " << argv[0] << 
						" Do Nothing\n";
		exit(EXIT_FAILURE);
	}

	// Start tests.
	TestClass test;
	test.filterDataIntoMats();

	return 0;
}