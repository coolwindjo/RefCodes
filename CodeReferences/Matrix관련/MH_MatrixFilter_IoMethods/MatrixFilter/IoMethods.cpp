#include "IoMethods.h"

IoMethods::IoMethods(void)
{
}

IoMethods::~IoMethods(void)
{
}

// Read and tokenize integers from given input stream and store them into given integer-list.
int IoMethods::tokenizeIntegersByLine(ifstream* inputStream, int* integerList, int maxLineLen)
{
	char* line = new char[maxLineLen];
	char* pToken = NULL;
	char* pSeparator = " ,\t\n";
	char* nextToken = NULL;

	int i=0;
	if (inputStream->getline( line, maxLineLen) != NULL) {
		// Tokenize the line.
		if ((pToken = strtok_s( line, pSeparator, &nextToken )) == NULL) {
			delete [] line;
			return -1;
		}
		// Convert into integer item value.
		bool nonInteger = false;
		string str = pToken;
		for (int j=0; j<static_cast<int>(str.size()); j++)
			if (!isdigit(str.at(j)) && (j!=0))
				nonInteger = true;
		if (!nonInteger)
			integerList[i] = atoi( str.c_str() );
		else
			integerList[i] = 0;
		i++;
		while ( (pToken = strtok_s( NULL, pSeparator, &nextToken )) != NULL ) {
			nonInteger = false;
			str = pToken;
			for (int j=0; j<static_cast<int>(str.size()); j++)
				if (!isdigit(str.at(j)) && (j!=0))
					nonInteger = true;
			if (!nonInteger)
				integerList[i] = atoi( str.c_str() );
			else
				integerList[i] = 0;
			i++;
		}
	}
	delete [] line;
	return i;
}

// Read and tokenize floating numbers from given input stream and store them into given integer-list.
int IoMethods::tokenizeFloatsByLine(ifstream* inputStream, float* floatList, int maxLineLen)
{
	char* line = new char[maxLineLen];
	char* pToken = NULL;
	char* pSeparator = " ,\t\n[]";
	char* nextToken = NULL;

	int i=0;
	if (inputStream->getline( line, maxLineLen) != NULL) {
		// Tokenize the line.
		if ((pToken = strtok_s( line, pSeparator, &nextToken )) == NULL) {
			delete [] line;
			return -1;
		}
		// Convert into integer item value.
		bool nonFloat = false;
		string str = pToken;
		for (int j=0; j<static_cast<int>(str.size()); j++)
			if (!isdigit(str.at(j))&&(str.at(j) != '.')&& (j!=0)) {
				nonFloat = true;
				break;
			}
		if (!nonFloat) {
			floatList[i] = static_cast<float>(atof( str.c_str() ));
			i++;
		}
		while ( (pToken = strtok_s( NULL, pSeparator, &nextToken )) != NULL ) {
			nonFloat = false;
			str = pToken;
			for (int j=0; j<static_cast<int>(str.size()); j++)
				if (!isdigit(str.at(j))&&(str.at(j) != '.')&& (j!=0)) {
					nonFloat = true;
					break;
				}
			if (!nonFloat) {
				floatList[i] = static_cast<float>(atof( str.c_str() ));
				i++;
			}
		}
	}
	delete [] line;
	return i;
}

// Read a line and store strings in char* array by tokenizing character sequences.
int IoMethods::readStringsByLine(ifstream* inputStream, string* strList, int maxLineLen)
{
	int strCount = 0;
	char* line	= new char[maxLineLen];
	char* pToken = NULL;
	char* pSeparator = " ,\t\n";
	char* nextToken = NULL;

	if (inputStream->getline( line, maxLineLen) != NULL) {
		// Tokenize the line.
		if ((pToken = strtok_s( line, pSeparator, &nextToken )) == NULL) {
			cerr << "Error: Failed to tokenize";
			delete [] line;
			return -1;
		}
		string str;
		str = pToken;
		// Store item value.
		strList[strCount++] = str;
		while ( (pToken = strtok_s( NULL, pSeparator, &nextToken )) != NULL ) {
			str = pToken;
			// Store item value.
			strList[strCount++] = str;
		}
	}
	delete [] line;
	return strCount;
}

// Read a line and store strings in char* array by tokenizing character sequences with the given delimiter.
int IoMethods::readStringsByLine(ifstream* inputStream, string* strList, int maxLineLen, char* delimiter)
{
	int strCount = 0;
	char* line	= new char[maxLineLen];
	char* pToken = NULL;
	char* nextToken = NULL;

	if (inputStream->getline( line, maxLineLen) != NULL) {
		// Tokenize the line.
		if ((pToken = strtok_s( line, delimiter, &nextToken )) == NULL) {
			cerr << "Error: Failed to tokenize";
			delete [] line;
			return -1;
		}
		string str;
		str = pToken;
		// Store item value.
		strList[strCount++] = str;
		while ( (pToken = strtok_s( NULL, delimiter, &nextToken )) != NULL ) {
			str = pToken;
			// Store item value.
			strList[strCount++] = str;
		}
	}
	delete [] line;
	return strCount;
}

// Get the number of lines and the maximum number of characters on a line.
int IoMethods::getLineLengthAndNumOfLines(ifstream* inputStream, int* numLines, int* lineLen)
{
	int charCount = 0;
	int maxLineLen = 0;
	int lineCount = 0;
	char tmpChar;

	while (inputStream->get( tmpChar ) != NULL) {
		if (tmpChar == '\n') {
			if (maxLineLen < charCount) {
				maxLineLen = charCount;
				charCount = 0;
			}
			lineCount++;
		}
		else
			charCount++;
	}
	if (maxLineLen != 0)
		*lineLen = maxLineLen;
	if (lineCount != 0)
		*numLines = lineCount;
	else
		cerr << "Error: Empty file.";

	inputStream->clear();
	inputStream->seekg( 0 );

	return lineCount;
}


// Get the number of lines and the maximum number of characters and strings on a line.
int IoMethods::getLineLengthAndNumOfStringsAndLines(ifstream* inputStream, int* numLines
	, int* maxNumStrings, int* lineLen)
{
	int strCount = 0;
	int charCount = 0;
	int maxLineLen = 0;
	int lineCount = 0;
	char tmpChar;

	while (inputStream->get( tmpChar ) != NULL) {
		if (tmpChar == '\n') {
			if (maxLineLen < charCount) {
				maxLineLen = charCount;
				charCount = 0;
			}
			lineCount++;
		}
		else
			charCount++;
	}
	if (lineCount != 0)
		*numLines = lineCount;
	else
		cerr << "Error: Empty file.";

	char* line = NULL;
	if (maxLineLen != 0) {
		*lineLen = maxLineLen;
		 line	= new char[maxLineLen];
	}
	else
		cerr << "Error: file includes only '\n's.";
	char* pToken = NULL;
	char* pSeparator = " ,\t\n";
	char* nextToken = NULL;

	while (inputStream->getline( line, maxLineLen) != NULL) {
		// Tokenize the line.
		if ((pToken = strtok_s( line, pSeparator, &nextToken )) == NULL) {
			cerr << "Error: Failed to tokenize";
			delete [] line;
			return -1;
		}
		strCount++;
		while ( (pToken = strtok_s( NULL, pSeparator, &nextToken )) != NULL ) {
			strCount++;
		}
	}
	delete [] line;
	inputStream->clear();
	inputStream->seekg( 0 );

	return lineCount;
}
