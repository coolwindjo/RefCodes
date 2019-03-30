#pragma once
#include <iostream>

#define TRUE 1
#define FALSE 0

using namespace std;

template <class T>
class CMatrix
{
public:
	CMatrix(int32_t rows, int32_t cols);
	~CMatrix(void);
	CMatrix& operator*=(CMatrix& latterMatrix)
	{
		if (m_nCols == latterMatrix.m_nRows) {
			if (m_ppMatrix != NULL) {
				// Transpose the latter Matrix.
				if (latterMatrix.Transpose() == TRUE) 
    {
					// Initiate the result matrix.
					T** tmpMat = new T*[m_nRows];
					for (int32_t i = 0; i<m_nRows; i++) {
						tmpMat[i] = new T[latterMatrix.m_nRows];
						for (int32_t j = 0; j<latterMatrix.m_nRows; j++)
							tmpMat[i][j] = 0;
					}
					// Multiply every respective elements from each matrix.
					for (int32_t i=0; i<m_nRows; i++) 
						for (int32_t j=0; j<latterMatrix.m_nRows; j++)
							for (int32_t k=0; k<m_nCols; k++)
								tmpMat[i][j] += m_ppMatrix[i][k]*latterMatrix.m_ppMatrix[j][k];
					// Delete old matrix.
					for (int32_t i=0; i<m_nRows; i++) {
						delete [] m_ppMatrix[i];
						m_ppMatrix[i] = NULL;
					}
					delete [] m_ppMatrix;
					m_ppMatrix = NULL;
					// Assign new matrix.
					m_ppMatrix = tmpMat;
					m_nCols = latterMatrix.m_nRows;
     if (latterMatrix.Transpose() == FALSE)
     {
      cerr << "Error: Latter matrix is unexpectedly changed.\n";
     }
				} // if (latterMatrix.Transpose()==TRUE) {
			} // if (m_ppMatrix != NULL) {
		} // if (m_nCols == latterMatrix.m_nRows) {
		else 
			cerr << "Error: Cannot multiply the two matrices.\n";
		return *this;
	}
	
	// Copy latter matrix to it.
	CMatrix& operator= (const CMatrix& latterMatrix)
	{
		if (this != &latterMatrix) {
			if (m_ppMatrix != NULL) {
				// Empty existing matrix.
				for (int32_t i=0; i<m_nRows; i++) {
					if (m_ppMatrix[i])
					{
						delete[] m_ppMatrix[i];
						m_ppMatrix[i] = NULL;
					}
				}
				delete[] m_ppMatrix;
				m_ppMatrix = NULL;
			} // if (m_ppMatrix != NULL) {
			// Generate Temporary Matrix.
			T** tmpMat = new T*[latterMatrix.m_nRows];
			for (int32_t i=0; i<latterMatrix.m_nRows; i++) {
				tmpMat[i] = new T[latterMatrix.m_nCols];
				for (int32_t j=0; j<latterMatrix.m_nCols; j++)
					tmpMat[i][j] = latterMatrix.m_ppMatrix[i][j];
			}

			// Assign new matrix.
			m_ppMatrix = tmpMat;
			m_nRows	= latterMatrix.m_nRows;
			m_nCols		= latterMatrix.m_nCols;
		}
		return *this;
	}
	virtual void PrintMat(ostream* fout);
	// Fill the content of the Matrix.
	virtual int32_t FillMatrix(void) { return 0; }
	// Fill the content of the Matrix with random integers.
	int32_t FillMatrix(T minVal, T maxVal, double zeroRatio);
	// Transpose the matrix.
	uint16_t Transpose(void);
	T GetValue(int32_t i, int32_t j);
	uint16_t SetValue(int32_t i, int32_t j, T value);
	void GetNumRowsAndCols(int32_t* nRows, int32_t* nCols);

private:
	T** m_ppMatrix;
	int32_t m_nRows;
	int32_t m_nCols;
};
