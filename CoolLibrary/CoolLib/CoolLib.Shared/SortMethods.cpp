#include <cmath>

#include "CoolLibraries\SortMethods.h"

template<class T>
CSortMethods<T>::CSortMethods(void)
{
}

template<class T>
CSortMethods<T>::~CSortMethods(void)
{
}

// Quicksort with random pivot value.
template<class T>
void CSortMethods<T>::RandomizedQuicksort(T a[], int begin, int end)
{
	int pivot;

	if (begin<end)
	{
		pivot = _RandomizedPartition(a, begin, end);
		RandomizedQuicksort(a, begin, pivot - 1);
		RandomizedQuicksort(a, pivot + 1, end);
	}
}

template<class T>
int CSortMethods<T>::_RandomizedPartition(T a[], int begin, int end)
{
	int pivot;

	pivot = _Random(begin, end);
	_Swap(a + pivot, a + end);
	return _PartitionInQuick(a, begin, end);
}

template<class T>
int CSortMethods<T>::_Random(int p, int q)
{
	int r;
	r = p + (int)((q - p + 1)*rand() / (RAND_MAX + 1.0));
	return r;
}

template<class T>
void CSortMethods<T>::_Swap(T* m, T* n)
{
	T tmp;
	tmp = *m;
	*m = *n;
	*n = tmp;
}

template<class T>
int CSortMethods<T>::_PartitionInQuick(T a[], int begin, int end)
{
	T	pivotVal = a[end];
	int i = begin - 1;

	for (int j = begin; j <= end - 1; j++)
	{
		if (a[j] <= pivotVal)
		{
			i++;
			_Swap(a + i, a + j);
		}
	}
	_Swap(a + (i + 1), a + end);
	return i + 1;
}

// Heap sort.
template<class T>
void CSortMethods<T>::MinHeapSort(T a[], int size)
{
	T* newA;
	newA = new T[size];

	_BuildMinHeap(a, size);
	newA[0] = a[0];

	for (int i = 1; i<size; i++) {
		_Swap(a, a + (size - i));
		_MinHeapify(a, 0, (size - i));
		newA[i] = a[0];
	}
	if (!newA) {
		delete[] newA;
		newA = NULL;
		exit(EXIT_FAILURE);
	}
	else {
		copy_array(newA, newA + size, a);
		delete[] newA;
		newA = NULL;
	}
}

template<class T>
void CSortMethods<T>::_BuildMinHeap(T a[], int size)
{
	int i;
	i = (int)floor((double)(size - 1) / 2);
	for (; i >= 0; i--)
		_MinHeapify(a, i, size);
}

template<class T>
void CSortMethods<T>::_MinHeapify(T a[], int begin, int size)
{
	int lSub, rSub;
	int smallest;

	/*assume that the binary trees rooted at both subtrees are min -heaps*/
	lSub = begin * 2 + 1;
	rSub = begin * 2 + 2;

	// Check whether left node is out of bound.
	if (lSub < size) {
		/*find the largest node*/
		if (a[begin] > a[lSub])
			smallest = lSub;
		else
			smallest = begin;
		if (rSub < size) {	//check whether right node is out of bound
			if (a[smallest] > a[rSub])
				smallest = rSub;
		}
		/*swap the largest node with the begin node and call _MaxHeapify recursively*/
		if (smallest != begin)	//check whether left node is out of bound
		{
			_Swap(a + begin, a + smallest);
			_MinHeapify(a, smallest, size);
		}
	}
}

//template<class T>
//void CSortMethods<T>::buildPtrMinHeap(T a[], int size)
//{
//	int i;
//	i = (int)floor((double)(size - 1) / 2);
//	for (; i >= 0; i--)
//		ptrMinHeapify(a, i, size);
//}

//template<class T>
//void CSortMethods<T>::ptrMinHeapify(T a[], int begin, int size)
//{
//	int lSub, rSub;
//	int smallest;
//
//	/*assume that the binary trees rooted at both subtrees are min -heaps*/
//	lSub = begin * 2 + 1;
//	rSub = begin * 2 + 2;
//
//	// Check whether left node is out of bound.
//	if (lSub < size) {
//		/*find the largest node*/
//		if (*(a[begin]) > *(a[lSub]))
//			smallest = lSub;
//		else
//			smallest = begin;
//		if (rSub < size) {	//check whether right node is out of bound
//			if (*(a[smallest]) > *(a[rSub]))	//check whether right node is out of bound
//				smallest = rSub;
//		}
//		/*swap the largest node with the begin node and call _MaxHeapify recursively*/
//		if (smallest != begin)	//check whether left node is out of bound
//		{
//			PtrSwap(a + begin, a + smallest);
//			_MinHeapify(a, smallest, size);
//		}
//	}
//}

template<class T>
void CSortMethods<T>::PtrSwap(T* m, T* n)
{
	T tmp;
	tmp = *m;
	*m = *n;
	*n = tmp;
}

template<class T>
T* CSortMethods<T>::copy_array(T* first, T* last, T* dest)
{
	while (first != last) {
		*dest++ = *first++;
	}
	return dest;
}

template<class T>
void CSortMethods<T>::MaxHeapSort(T a[], int size)
{
	_BuildMaxHeap(a, size);

	for (int i = size - 1; i>0; i--) {
		_Swap(a + 0, a + i);
		_MaxHeapify(a, 0, i);
	}
}

template<class T>
void CSortMethods<T>::_BuildMaxHeap(T a[], int size)
{
	int i;
	i = (int)floor((double)(size - 1) / 2);
	for (; i >= 0; i--)
		_MaxHeapify(a, i, size);
}

template<class T>
void CSortMethods<T>::_MaxHeapify(T a[], int begin, int size)
{
	int lSub, rSub;
	int largest;

	/*assume that the binary trees rooted at both subtrees are min -heaps*/
	lSub = begin * 2 + 1;
	rSub = begin * 2 + 2;

	// Check whether left node is out of bound.
	if (lSub < size) {
		/*find the largest node*/
		if (a[begin] < a[lSub])
			largest = lSub;
		else
			largest = begin;
		if (rSub < size) {	//check whether right node is out of bound
			if (a[largest] < a[rSub])
				largest = rSub;
		}
		/*swap the largest node with the begin node and call _MaxHeapify recursively*/
		if (largest != begin)
		{
			_Swap(a + begin, a + largest);
			_MaxHeapify(a, largest, size);
		}
	}
}

template class CSortMethods<int>;
template class CSortMethods<float>;
