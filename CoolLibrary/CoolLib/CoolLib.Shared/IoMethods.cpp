#include "CoolLibraries\IoMethods.h"

#define TRUE 1
#define FALSE 0

CIoMethods::CIoMethods(void)
{
}

CIoMethods::~CIoMethods(void)
{
}

// Read and tokenize integers from given input stream and store them into given integer-list.
int32_t CIoMethods::GetIntegerListFromStream(ifstream* pifStream, int32_t **ppnIntegerList, int32_t nMaxLineLen)
{
	char* line = new char[nMaxLineLen + 1];
	char* pToken = NULL;
	char* pSeparator = " ,\t\n";
	char* nextToken = NULL;

	int32_t i = 0;
	if (pifStream->getline(line, nMaxLineLen + 1)) {
		// Tokenize the line.
		if ((pToken = strtok_s(line, pSeparator, &nextToken)) == NULL) {
			cerr << "Error: Failed to tokenize";
			delete[] line;
			line = NULL;
			return -1;
		}
		// Convert into integer item value.
		uint16_t nonInteger = FALSE;
		string str = pToken;
		for (int32_t j = 0; j<static_cast<int>(str.size()); j++)
			if (!isdigit(str.at(j)) && (j != 0))
				nonInteger = TRUE;
		if (!nonInteger)
			(*ppnIntegerList)[i] = atoi(str.c_str());
		else
			(*ppnIntegerList)[i] = 0;
		i++;
		while ((pToken = strtok_s(NULL, pSeparator, &nextToken)) != NULL) {
			nonInteger = FALSE;
			str = pToken;
			for (int32_t j = 0; j<static_cast<int>(str.size()); j++)
				if (!isdigit(str.at(j)) && (j != 0))
					nonInteger = TRUE;
			if (!nonInteger)
				(*ppnIntegerList)[i] = atoi(str.c_str());
			else
				(*ppnIntegerList)[i] = 0;
			i++;
		}
	}
	delete[] line;
	line = NULL;
	return i;
}

// Read and tokenize floating numbers from given input stream and store them into given integer-list.
int32_t CIoMethods::GetFloatListFromStream(ifstream* pifStream, float** ppFloatList, int32_t nMaxLineLen)
{
	char* line = new char[nMaxLineLen + 1];
	char* pToken = NULL;
	char* pSeparator = " ,\t\n[]";
	char* nextToken = NULL;

	int32_t i = 0;
	if (pifStream->getline(line, nMaxLineLen + 1)) {
		// Tokenize the line.
		if ((pToken = strtok_s(line, pSeparator, &nextToken)) == NULL) {
			cerr << "Error: Failed to tokenize";
			delete[] line;
			line = NULL;
			return -1;
		}
		// Convert into integer item value.
		uint16_t nonFloat = FALSE;
		string str = pToken;
		for (int32_t j = 0; j<static_cast<int>(str.size()); j++)
			if (!isdigit(str.at(j)) && (str.at(j) != '.') && (j != 0)) {
				nonFloat = TRUE;
				break;
			}
		if (!nonFloat) {
			(*ppFloatList)[i] = static_cast<float>(atof(str.c_str()));
			i++;
		}
		while ((pToken = strtok_s(NULL, pSeparator, &nextToken)) != NULL) {
			nonFloat = FALSE;
			str = pToken;
			for (int32_t j = 0; j<static_cast<int>(str.size()); j++)
				if (!isdigit(str.at(j)) && (str.at(j) != '.') && (j != 0)) {
					nonFloat = TRUE;
					break;
				}
			if (!nonFloat) {
				(*ppFloatList)[i] = static_cast<float>(atof(str.c_str()));
				i++;
			}
		}
	}
	delete[] line;
	line = NULL;
	return i;
}

// Read a line and store strings in char* array by tokenizing character sequences.
int32_t CIoMethods::GetStringListFromStream(ifstream* pifStream, string** ppstrList, int32_t nMaxLineLen)
{
	int32_t strCount = 0;
	char* line = new char[nMaxLineLen + 1];
	char* pToken = NULL;
	char* pSeparator = " ,\t\n";
	char* nextToken = NULL;

	if (pifStream->getline(line, nMaxLineLen + 1)) {
		// Tokenize the line.
		if ((pToken = strtok_s(line, pSeparator, &nextToken)) == NULL) {
			cerr << "Error: Failed to tokenize";
			delete[] line;
			line = NULL;
			return -1;
		}
		string str;
		str = pToken;
		// Store item value.
		(*ppstrList)[strCount++] = str;
		while ((pToken = strtok_s(NULL, pSeparator, &nextToken)) != NULL) {
			str = pToken;
			// Store item value.
			(*ppstrList)[strCount++] = str;
		}
	}
	delete[] line;
	line = NULL;
	return strCount;
}

// Read a line and store strings in char* array by tokenizing character sequences with the given delimiter.
int32_t CIoMethods::GetStringListFromStream(ifstream* pifStream, string** ppstrList, int32_t nMaxLineLen, char* delimiter)
{
	int32_t strCount = 0;
	char* line = new char[nMaxLineLen + 1];
	char* pToken = NULL;
	char* nextToken = NULL;

	if (pifStream->getline(line, nMaxLineLen + 1)) {
		// Tokenize the line.
		if ((pToken = strtok_s(line, delimiter, &nextToken)) == NULL) {
			cerr << "Error: Failed to tokenize";
			delete[] line;
			line = NULL;
			return -1;
		}
		string str;
		str = pToken;
		// Store item value.
		(*ppstrList)[strCount++] = str;
		while ((pToken = strtok_s(NULL, delimiter, &nextToken)) != NULL) {
			str = pToken;
			// Store item value.
			(*ppstrList)[strCount++] = str;
		}
	}
	delete[] line;
	line = NULL;
	return strCount;
}

// Get the number of lines and the maximum number of characters on a line.
int32_t CIoMethods::GetLineLengthAndNumOfLines(ifstream* pifStream, int32_t* numLines, int32_t* lineLen)
{
	int32_t charCount = 0;
	int32_t nMaxLineLen = 0;
	int32_t lineCount = 0;
	char tmpChar;

	while (pifStream->get(tmpChar)) {
		if (tmpChar == '\n') {
			if (nMaxLineLen < charCount) {
				nMaxLineLen = charCount;
			}
			lineCount++;
			charCount = 0;
		}
		else
			charCount++;
	}
	if (nMaxLineLen != 0)
		*lineLen = nMaxLineLen;
	if (lineCount != 0)
		*numLines = lineCount;
	else
		cerr << "Error: Empty file.";

	pifStream->clear();
	pifStream->seekg(0);

	return lineCount;
}


// Get the number of lines and the maximum number of characters and strings on a line.
int32_t CIoMethods::GetLineLengthAndNumOfStringsAndLines(ifstream* pifStream, int32_t* numLines, int32_t* maxNumStrings, int32_t* lineLen)
{
	int32_t strCount = 0;
	int32_t charCount = 0;
	int32_t nMaxLineLen = 0;
	int32_t lineCount = 0;
	char tmpChar;

	while (pifStream->get(tmpChar)) {
		if (tmpChar == '\n') {
			if (nMaxLineLen < charCount) {
				nMaxLineLen = charCount;
			}
			lineCount++;
			charCount = 0;
		}
		else
			charCount++;
	}
	if (lineCount != 0)
		*numLines = lineCount;
	else
		cerr << "Error: Empty file.";

	char* line = NULL;
	if (nMaxLineLen != 0) {
		*lineLen = nMaxLineLen;
		line = new char[nMaxLineLen + 1];
	}
	else
		cerr << "Error: file includes only '\n's.";

	int32_t maxNumStrs = 0;
	char* pToken = NULL;
	char* pSeparator = " ,\t\n";
	char* nextToken = NULL;

	pifStream->clear();
	pifStream->seekg(0);

	while (pifStream->getline(line, nMaxLineLen + 1)) {
		// Tokenize the line.
		if ((pToken = strtok_s(line, pSeparator, &nextToken)) == NULL) {
			cerr << "Error: Failed to tokenize";
			delete[] line;
			line = NULL;
			return -1;
		}
		strCount++;
		while ((pToken = strtok_s(NULL, pSeparator, &nextToken)) != NULL) {
			strCount++;
		}
		if (maxNumStrs < strCount) {
			maxNumStrs = strCount;
		}
		strCount = 0;
	}

	*maxNumStrings = maxNumStrs;

	delete[] line;
	line = NULL;
	pifStream->clear();
	pifStream->seekg(0);

	return lineCount;
}
