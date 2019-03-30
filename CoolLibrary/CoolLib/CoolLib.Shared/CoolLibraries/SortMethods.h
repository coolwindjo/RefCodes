#pragma once

template <class T>
class CSortMethods
{
public:
	CSortMethods(void);
	~CSortMethods(void);
	// Quicksort with random pivot value.
	void RandomizedQuicksort(T a[], int begin, int end);
	int _RandomizedPartition(T a[], int begin, int end);
	int _Random(int p, int q);
	void _Swap(T* m, T* n);
	int _PartitionInQuick(T a[], int begin, int end);
	// Heap sort.
	void MinHeapSort(T a[], int size);
	void _BuildMinHeap(T a[], int size);
	void _MinHeapify(T a[], int begin, int size);
	//void buildPtrMinHeap(T a[], int size);
	//void ptrMinHeapify(T a[], int begin, int size);
	void PtrSwap(T* m, T* n);
	T* copy_array(T* first, T* last, T* dest);
	void MaxHeapSort(T a[], int size);	// More efficient.
	void _BuildMaxHeap(T a[], int size);
	void _MaxHeapify(T a[], int begin, int size);
};