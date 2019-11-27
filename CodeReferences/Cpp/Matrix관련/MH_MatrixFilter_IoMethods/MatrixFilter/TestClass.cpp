#include "TestClass.h"

TestClass::TestClass(void)
: count_(0)
{
}

TestClass::~TestClass(void)
{
}

// For Mobile Harbor Project
int TestClass::readVectorMatrixFromFile(void)
{
	IoMethods iom;
	ifstream fin;

	fin.open( "LANE1-3DLMS_Left-08-00000005-022927-14.3DS_XY.TXT" );
	if (fin.fail()){
		cout << "Input file openning failed" <<endl;
		exit(EXIT_FAILURE);
	}

	int nFrame = ROW;
	int nData = COL;
	int maxLen = 0;

	iom.getLineLengthAndNumOfStringsAndLines( &fin, &nFrame, &nData, &maxLen );

	int nF;
	cout <<"Number of Frames?\n>";
	cin >> nF;
	if (nF >1 && nF < 1000)
		nFrame = nF;

	CMatrix<int>* matX;
	matX = new CMatrix<int>(nFrame, nData);
	CMatrix<int>* matZ;
	matZ = new CMatrix<int>(nFrame, nData);

	int intLine[COL*2+2];

	int numTerms = 0;
	int tmp;
	int frameNo = 0;
	while (tmp = iom.tokenizeIntegersByLine( &fin, intLine, maxLen)) {
		int dataNo=0;
		for (int j=1; j<tmp+1; j++) {
			if (j%2 == 1)
				matX->setValue(frameNo,dataNo, intLine[j-1]);
			else if (j%2 == 0) {
				matZ->setValue(frameNo,dataNo, intLine[j-1]);
				dataNo++;
			}
		}
		numTerms += tmp;
		frameNo++;
	}

	fin.close();

	ofstream foutX, foutZ;
	foutX.open( "matrix_X.txt" );
	if (foutX.fail()){
		cout << "Output file opening failed" <<endl;
		exit(EXIT_FAILURE);
	}
	foutZ.open( "matrix_Z.txt" );
	if (foutZ.fail()){
		cout << "Output file opening failed" <<endl;
		exit(EXIT_FAILURE);
	}

	matX->printMat(&foutX);
	matZ->printMat(&foutZ);

	foutX.close();
	foutZ.close();
	return 0;
}


// Read x, y, z values from a file and make three matrices for each value.
int TestClass::filterDataIntoMats(void)
{
	IoMethods iom;
	ifstream fin;

	fin.open( "./test12-22/etcar1.txt" );
	if (fin.fail()){
		cout << "Input file openning failed" <<endl;
		exit(EXIT_FAILURE);
	}

	int nFrame = 0;
	int nData = 0;
	int maxLen = 0;

	cout << "Load a file..." <<endl;

	if (iom.getLineLengthAndNumOfStringsAndLines( &fin, &nFrame
		, &nData, &maxLen  ) == 0)
		return -1;

	int nD;
	cout <<"Number of Data? \n>";
	cin >> nD;
	if (nD >1 && nD < 1000)
		nData = nD;

	CMatrix<float>* matX;
	matX = new CMatrix<float>(nFrame, 1);
	CMatrix<float>* matY;
	matY = new CMatrix<float>(nFrame, 1);
	CMatrix<float>* matZ;
	matZ = new CMatrix<float>(nFrame, 1);

	float* floatLine = new float[nData*2+2];

	int numTerms = 0;
	int tmp;
	int frameNo = 0;
	while (tmp = iom.tokenizeFloatsByLine( &fin, floatLine, maxLen)) {
		int tmp = nData;
		for (int j=1; j<tmp+1; j++) {
			if (j%3 == 1)
				matX->setValue(frameNo,0, floatLine[j-1]);
			else if (j%3 == 2) 
				matY->setValue(frameNo,0, floatLine[j-1]);
			else if (j%3 == 0) 
				matZ->setValue(frameNo,0, floatLine[j-1]);
		}
		numTerms += tmp;
		frameNo++;
	}

	fin.close();

	ofstream foutX, foutY, foutZ;
	foutX.open( "list_X.txt" );
	if (foutX.fail()){
		cout << "Output file opening failed" <<endl;
		exit(EXIT_FAILURE);
	}
	foutY.open( "list_Y.txt" );
	if (foutY.fail()){
		cout << "Output file opening failed" <<endl;
		exit(EXIT_FAILURE);
	}
	foutZ.open( "list_Z.txt" );
	if (foutZ.fail()){
		cout << "Output file opening failed" <<endl;
		exit(EXIT_FAILURE);
	}

	matX->printMat(&foutX);
	matY->printMat(&foutY);
	matZ->printMat(&foutZ);

	foutX.close();
	foutY.close();
	foutZ.close();
	return 0;
}
