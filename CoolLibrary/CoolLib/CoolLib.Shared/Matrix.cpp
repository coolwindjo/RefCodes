#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "CoolLibraries\Matrix.h"

template <class T>
CMatrix<T>::CMatrix(int32_t rows, int32_t cols)
	: m_ppMatrix(NULL)
{
	m_nRows = rows;
	m_nCols = cols;
	m_ppMatrix = new T*[m_nRows];
	for (int32_t i = 0; i<m_nRows; i++) {
		m_ppMatrix[i] = new T[m_nCols];
		for (int32_t j = 0; j<m_nCols; j++)
			m_ppMatrix[i][j] = NULL;
	}
}

template <class T>
CMatrix<T>::~CMatrix(void)
{
	if (m_ppMatrix) {
		for (int32_t i = 0; i<m_nRows; i++) {
			if (m_ppMatrix[i])
			{
				delete[] m_ppMatrix[i];
				m_ppMatrix[i] = NULL;
			}
		}
		delete[] m_ppMatrix;
		m_ppMatrix = NULL;
	}
}

template <class T>
void CMatrix<T>::PrintMat(ostream* fout)
{
	if (m_ppMatrix) {
		fout->setf(ios::left);
		*fout << setw(6) << " MAT";
		fout->unsetf(ios::left);
		for (int32_t j = 0; j<m_nCols; j++) {
			*fout << setw(2) << "[";
			*fout << setw(3) << j + 1;
			fout->setf(ios::left);
			*fout << setw(2) << "]";
			fout->unsetf(ios::left);
		}
		*fout << endl;
		fout->setf(ios::fixed);
		fout->setf(ios::showpoint);
		fout->precision(3);
		for (int32_t i = 0; i<m_nRows; i++) {
			*fout << setw(1) << "[";
			*fout << setw(3) << i + 1;
			fout->setf(ios::left);
			*fout << setw(2) << "]";
			fout->unsetf(ios::left);
			for (int32_t j = 0; j<m_nCols; j++) {
				*fout << setw(6) << m_ppMatrix[i][j] << " ";
			}
			*fout << endl;
		}
	}
}

// Fill the content of the Matrix with random integers.
template <class T>
int32_t CMatrix<T>::FillMatrix(T minVal, T maxVal, double zeroRatio)
{
	int32_t count = 0;
	if ((minVal<maxVal) && (zeroRatio >= 0) && (zeroRatio <= 1)) {
		double denominator = (1 / (static_cast<double>(1) - zeroRatio));
		// Random integer generations.
		srand(static_cast<unsigned int>(time(NULL)));
		for (int32_t i = 0; i<m_nRows; i++) {
			T val = 0;
			for (int32_t j = 0; j<m_nCols; j++) {
				val = static_cast<T>(
					minVal +
					static_cast<double>(rand())
					/ (static_cast<double>(RAND_MAX) + static_cast<double>(1))
					*(maxVal - minVal + 1)
					*denominator
					);
				if (val <= maxVal) {
					m_ppMatrix[i][j] = val;
					count++;
				}
				else
					m_ppMatrix[i][j] = 0;
			}
		}
		return count;
	}
	else {
		cerr << "Error: Invalid Parameters." << endl;
		return -1;
	}
}

// Transpose the matrix.
template <class T>
uint16_t CMatrix<T>::Transpose(void)
{
	if (m_ppMatrix != NULL) {
		T** tmpMat = new T*[m_nCols];
		for (int32_t i = 0; i<m_nCols; i++) {
			tmpMat[i] = new T[m_nRows];
			for (int32_t j = 0; j<m_nRows; j++)
				tmpMat[i][j] = 0;
		}
		// Transpose.
		for (int32_t i = 0; i<m_nRows; i++)
			for (int32_t j = 0; j<m_nCols; j++)
				tmpMat[j][i] = m_ppMatrix[i][j];
		// Delete old matrix.
		for (int32_t i = 0; i<m_nRows; i++) {
			delete[] m_ppMatrix[i];
			m_ppMatrix[i] = NULL;
		}
		delete[] m_ppMatrix;
		m_ppMatrix = NULL;
		// Assign new matrix.
		m_ppMatrix = tmpMat;
		int32_t tmp = m_nRows;
		m_nRows = m_nCols;
		m_nCols = tmp;
		return TRUE;
	}
	return FALSE;
}

template <class T>
T CMatrix<T>::GetValue(int32_t i, int32_t j)
{
	return m_ppMatrix[i][j];
}

template <class T>
uint16_t CMatrix<T>::SetValue(int32_t i, int32_t j, T value)
{
	if ((i >= 0) && (i<m_nRows) && (j >= 0) && (j<m_nCols)) {
		m_ppMatrix[i][j] = value;
		return TRUE;
	}
	return FALSE;
}

template <class T>
void CMatrix<T>::GetNumRowsAndCols(int32_t* nRows, int32_t* nCols)
{
	*nRows = m_nRows;
	*nCols = m_nCols;
}

template class CMatrix<int>;
template class CMatrix<float>;
