#pragma once
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

template <class T>
class CMatrix
{
public:
	CMatrix(int rows, int cols);
	~CMatrix(void);
	CMatrix& operator*=(CMatrix& latterMatrix)
	{
		if (_Cols == latterMatrix._Rows) {
			if (_Matrix != NULL) {
				T** tmpMat = new T*[_Rows];
				for (int i=0; i<_Rows; i++) {
					tmpMat[i] = new T[latterMatrix._Cols];
					for (int j=0; j<latterMatrix._Cols; j++)
						tmpMat[i][j] = 0;
				}
				if (latterMatrix.transpose()==true) {
					for (int i=0; i<_Rows; i++) 
						for (int j=0; j<latterMatrix._Rows; j++)
							for (int k=0; k<_Cols; k++)
								tmpMat[i][j] += _Matrix[i][k]*latterMatrix._Matrix[j][k];
					// Delete old matrix.
					for (int i=0; i<_Rows; i++) {
						delete [] _Matrix[i];
					}
					delete [] _Matrix;
					// Assign new matrix.
					_Matrix = tmpMat;
					_Cols = latterMatrix._Rows;
					if (latterMatrix.transpose()==false)
						cerr << "Error: Latter matrix is unexpectedly changed.\n";
				} // if (latterMatrix.transpose()==true) {
			} // if (_Matrix != NULL) {
		} // if (_Cols == latterMatrix._Rows) {
		else 
			cerr << "Error: Cannot multiply the two matrices.\n";
		return *this;
	}
	CMatrix& operator<< (const CMatrix& latterMatrix)
	{
		if (this != &latterMatrix) {
			if (_Matrix != NULL) {
				for (int i=0; i<_Rows; i++) {
					if (_Matrix[i])
						delete [] _Matrix[i];
				}
				delete [] _Matrix;
				T** tmpMat = new T*[_Rows];
				for (int i=0; i<_Rows; i++) {
					tmpMat[i] = new T[latterMatrix._Cols];
					for (int j=0; j<latterMatrix._Cols; j++)
						tmpMat[i][j] = 0;
				}
				for (int i=0; i<_Rows; i++) 
					for (int j=0; j<_Cols; j++)
						tmpMat[i][j] = latterMatrix._Matrix[i][j];
				// Assign new matrix.
				_Matrix = tmpMat;
			} // if (_Matrix != NULL) {
			_Rows	= latterMatrix._Rows;
			_Cols		= latterMatrix._Cols;
		}
		return *this;
	}
	virtual void printMat(ostream* fout);
	// Fill the content of the Matrix.
	virtual int fillMatrix(void){return 0;}
	// Fill the content of the Matrix with random integers.
	int fillMatrix(T minVal, T maxVal, double zeroRatio);
	// Transpose the matrix.
	bool transpose(void);
	T getValue(int i, int j);
	bool setValue(int i, int j, T value);
protected:
	T** _Matrix;
	int _Rows;
	int _Cols;
};

template <class T>
CMatrix<T>::CMatrix(int rows, int cols)
: _Matrix(NULL)
{
	_Rows	= rows;
	_Cols		= cols;
	_Matrix = new T*[_Rows];
	for (int i=0; i<_Rows; i++) {
		_Matrix[i] = new T[_Cols];
		for (int j=0; j<_Cols; j++)
			_Matrix[i][j] = NULL;
	}
}

template <class T>
CMatrix<T>::~CMatrix(void)
{
	if (_Matrix) {
		for (int i=0; i<_Rows; i++) {
			if (_Matrix[i])
				delete [] _Matrix[i];
		}
		delete [] _Matrix;
		_Matrix = NULL;
	}
}

template <class T>
void CMatrix<T>::printMat(ostream* fout)
{
	if (_Matrix) {
//		fout->setf(ios::left);
//		*fout << setw(6)<< " MAT";
//		fout->unsetf(ios::left);
//		for ( int j=0; j<_Cols; j++) {
//			*fout << setw(2) << "[";
//			*fout << setw(3) << j+1;
//			fout->setf(ios::left);
//			*fout << setw(2) << "]";
//			fout->unsetf(ios::left);
//		}
//		*fout << endl;
//		fout->setf(ios::fixed);
//		fout->setf(ios::showpoint);
//		fout->precision(2);
		for (int i=0; i<_Rows; i++) {
//			*fout << setw(1) << "[";
//			*fout << setw(3) << i+1;
//			fout->setf(ios::left);
//			*fout << setw(2) << "]";
//			fout->unsetf(ios::left);
			for ( int j=0; j<_Cols; j++) {
				*fout << setw(6) << _Matrix[i][j] <<" ";
			}
			*fout << endl;
		}
	}
}

// Fill the content of the Matrix with random integers.
template <class T>
int CMatrix<T>::fillMatrix(T minVal, T maxVal, double zeroRatio)
{
	int count=0;
	if ((minVal<maxVal)&&(zeroRatio>=0)&&(zeroRatio<=1)) {
		double denominator = (1/(static_cast<double>(1)-zeroRatio));
		// Random integer generations.
		srand( static_cast<unsigned int>(time(NULL)) );
		for (int i=0; i<_Rows; i++) {
			T val=0;
			for (int j=0; j<_Cols; j++) {
				val = static_cast<T>( 
					minVal + 
					static_cast<double>(rand())
					/(static_cast<double>(RAND_MAX)+static_cast<double>(1))
					*(maxVal-minVal+1)
					*denominator
					);
				if (val <= maxVal) {
					_Matrix[i][j] = val;
					count++;
				}
				else
					_Matrix[i][j] = 0;
			}
		}
		return count;
	}
	else {
		cerr << "Error: Invalid Parameters." <<endl;
		return -1;
	}
}

// Transpose the matrix.
template <class T>
bool CMatrix<T>::transpose(void)
{
	if (_Matrix != NULL) {
		T** tmpMat = new T*[_Cols];
		for (int i=0; i<_Cols; i++) {
			tmpMat[i] = new T[_Rows];
			for (int j=0; j<_Rows; j++)
				tmpMat[i][j] = 0;
		}
		// Transpose.
		for (int i=0; i<_Rows; i++) 
			for (int j=0; j<_Cols; j++)
				tmpMat[j][i] = _Matrix[i][j];
		// Delete old matrix.
		for (int i=0; i<_Rows; i++) {
			delete [] _Matrix[i];
		}
		delete [] _Matrix;
		// Assign new matrix.
		_Matrix = tmpMat;
		int tmp = _Rows;
		_Rows = _Cols;
		_Cols = tmp;
		return true;
	}
	return false;
}

template <class T>
T CMatrix<T>::getValue(int i, int j)
{
	return _Matrix[i][j];
}

template <class T>
bool CMatrix<T>::setValue(int i, int j, T value)
{
	if ((i>=0)&&(i<_Rows)&&(j>=0)&&(j<_Cols)) {
		_Matrix[i][j] = value;
		return true;
	}
	return false;
}

