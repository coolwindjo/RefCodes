#include "../../ProbSolvStart.h"

typedef struct {
	int * heap;
	int hSize;
	int count;  /* number of integers in the heap*/
} Heap;

int CreateHeap(Heap *hPtr, int size);
void DestroyHeap(Heap *hPtr);
int InsertUpHeap(Heap *hPtr, int inData);
int DeleteDownHeap(Heap * hPtr, int * getData);
void DownHeap(Heap *hPtr, int position);
void PrintHeap(const Heap * hPtr);
int IsHeapEmpty(Heap *hPtr);
int IsHeapFull(Heap *hPtr);

/*----------------------------------------------------------------------------------
  Function name : main
----------------------------------------------------------------------------------*/
int main()
{
	//int ary[9] = {1,2,3,4,5,6,7,8,9};
	int ary[20] = { 13,3,20,5,11,17,6,7,19,9,15,10,4,12,1,14,16,8,18,2 };
	//int ary[20] = { 1,2,3,4,4,3,2,1,1,1,2,2,3,3,4,4,4,3,2,1 };
	int i;
	int size = sizeof(ary) / sizeof(ary[0]);
	Heap heap;
	int getData;
	int res;

	CreateHeap(&heap, size);
	for (i = 0; i < size; ++i)
		heap.heap[i + 1] = ary[i];
	heap.count = size;

	PrintHeap(&heap);

	for (i = heap.hSize / 2; i >= 1; --i)
	{
		DownHeap(&heap, i);
		//printf("Start from %3d", i);

	}
	printf("\nprint heap  : ");
	PrintHeap(&heap);


	printf("delete heap : ");
	for (i = 0; i < size; ++i) {
		res = DeleteDownHeap(&heap, &getData);
		if (res == 1)
		{
			printf("%3d", getData);

			//PrintHeap(&heap);
		}
		else
			printf("Failed to delete heap\n");
	}
	printf("\n\n");
	DestroyHeap(&heap);
	getchar();
	return 0;
}


#include <limits.h>

int CreateHeap(Heap *hPtr, int size)
{
	if (hPtr == nullptr)
	{
		return 0;
	}

	hPtr->hSize = size;
	hPtr->heap = new int[hPtr->hSize + 1];
	memset(hPtr->heap, 0, sizeof(int)*(hPtr->hSize + 1));
	hPtr->heap[0] = INT_MAX;
	hPtr->count = 0;

	return 1;
}

void PrintHeap(const Heap * hPtr)
{
	if (hPtr == nullptr)
	{
		return;
	}

	cout << endl;

	int pow2 = 2;
	for (int i = 0; i < hPtr->count; i++)
	{
		cout << hPtr->heap[i + 1] << " ";
		if ((i + 1) == (pow2 - 1))
		{
			cout << endl;
			pow2 *= 2;
		}
	}

	cout << endl;

	return;
}

void DestroyHeap(Heap *hPtr)
{
	if (hPtr == nullptr)
	{
		return;
	}

	delete[] hPtr->heap;
	hPtr->heap = nullptr;
	hPtr->count = 0;
	hPtr->hSize = 0;

	return;
}

int InsertUpHeap(Heap * hPtr, int inData)
{
	return 0;
}

int DeleteDownHeap(Heap * hPtr, int * getData)
{
	if (hPtr == nullptr)
	{
		return 0;
	}

	if (IsHeapEmpty(hPtr))
	{
		return 0;
	}

	*getData = hPtr->heap[1];
	hPtr->heap[1] = hPtr->heap[hPtr->count];
	hPtr->heap[hPtr->count] = INT_MIN;
	hPtr->count--;

	DownHeap(hPtr, 1);

	return 1;
}

void DownHeap(Heap *hPtr, int position)
{
	if (hPtr == nullptr)
	{
		return;
	}

	int curPos = position;
	const int downValue = hPtr->heap[curPos];
	const int lastInnerNode = (hPtr->count >> 1);
	for (int i = 0;
		(i < hPtr->hSize)
		&& (curPos <= lastInnerNode);
		++i)
	{
		const int leftChild = curPos * 2;
		const int rightChild = curPos * 2 + 1;

		int biggerChild = leftChild;
		if (hPtr->heap[rightChild] > hPtr->heap[leftChild])
		{
			biggerChild = rightChild;
		}

		if (downValue >= hPtr->heap[biggerChild])
		{
			break;
		}

		hPtr->heap[curPos] = hPtr->heap[biggerChild];

		curPos = biggerChild;
	}
	hPtr->heap[curPos] = downValue;

	return;
}

int IsHeapEmpty(Heap *hPtr)
{
	if (hPtr == nullptr)
	{
		return 0;
	}

	if (hPtr->count == 0)
	{
		return 1;
	}

	return 0;
}

int IsHeapFull(Heap *hPtr)
{
	if (hPtr == nullptr)
	{
		return 0;
	}

	if (hPtr->count == (hPtr->hSize))
	{
		return 1;
	}

	return 0;
}
