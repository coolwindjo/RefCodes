#include<stdio.h>
#include "heap.h"
/*----------------------------------------------------------------------------------
  Function name : main
----------------------------------------------------------------------------------*/
int main()
{
	//int ary[9] = {1,2,3,4,5,6,7,8,9};
	//int ary[20] = {13,3,20,5,11,17,6,7,19,9,15,10,4,12,1,14,16,8,18,2};
	int ary[20] = {1,2,3,4,4,3,2,1,1,1,2,2,3,3,4,4,4,3,2,1};
	int i;
	int size = sizeof(ary)/sizeof(ary[0]);
	Heap heap;
	int getData;
	BOOL res;
	createHeap(&heap, size);
	for(i=0; i<size; ++i)
		heap.heap[i+1] = ary[i];
	heap.count = size;

	for(i=heap.hSize/2; i>=1; --i)  /* 상향식 힙 생성, 모든 내부 노드에 대해 하향작업 */
		downHeap(&heap, i);

	printf("print heap  : ");
	printHeap(&heap);

	printf("delete heap : ");
	for(i=0; i<size; ++i){
		res=deleteDownHeap(&heap, &getData);
		if(res==TRUE)
			printf("%3d", getData);
		else
			printf(" delete heap 실패 ");
	}
	printf("\n\n");
	destroyHeap(&heap);
	getchar();
	return 0;
}
