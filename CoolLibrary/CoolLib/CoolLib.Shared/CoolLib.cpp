///
/// CoolLib.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
///

#include "pch.h"

#include "CoolLibraries\CoolLib.h"

CoolLib::CCoolLib::CCoolLib()
	: m_poIO(NULL)
	, m_poSort(NULL)
	, m_poArr(NULL)
	, m_poLink(NULL)
	, m_poBst(NULL)
{

}

CoolLib::CCoolLib::~CCoolLib()
{
	if (m_poIO != NULL)
	{
		delete m_poIO;
		m_poIO = NULL;
	}
	if (m_poSort != NULL)
	{
		delete m_poSort;
		m_poSort = NULL;
	}
	if (m_poArr != NULL)
	{
		delete m_poArr;
		m_poArr = NULL;
	}
	if (m_poLink != NULL)
	{
		delete m_poLink;
		m_poLink = NULL;
	}
	if (m_poBst != NULL)
	{
		delete m_poBst;
		m_poBst = NULL;
	}
}

// Matrix calculations.
void CoolLib::CCoolLib::MAT_FillMatrix(CMatrix<int>* poMat, int32_t nMinVal, int32_t nMaxVal, double dZeroRatio)
{
	poMat->FillMatrix(nMinVal, nMaxVal, dZeroRatio);
}
void CoolLib::CCoolLib::MAT_PrintMatrix(CMatrix<int>* poMat, ostream* fout)
{
	poMat->PrintMat(fout);
}
void CoolLib::CCoolLib::MAT_Transpose(CMatrix<int>* poMat)
{
	poMat->Transpose();
}
void CoolLib::CCoolLib::MAT_MultAssign(CMatrix<int>* poMat, CMatrix<int>* poMultiplerMat)
{
	*poMat *= *poMultiplerMat;
}


// Input / Output Methods.
int32_t CoolLib::CCoolLib::IOM_GetIntegerListFromStream(ifstream* pifStream, int32_t **ppnIntegerList, int32_t nMaxLineLen)
{
	return m_poIO->GetIntegerListFromStream(pifStream, ppnIntegerList, nMaxLineLen);
}
int32_t CoolLib::CCoolLib::IOM_GetStringListFromStream(ifstream* pifStream, string **ppstrList, int32_t nMaxLineLen)
{
	return m_poIO->GetStringListFromStream(pifStream, ppstrList, nMaxLineLen);
}

// Sorting Methods.
void CoolLib::CCoolLib::SRT_MaxHeapSort(int32_t a[], int32_t size)
{
	m_poSort->MaxHeapSort(a, size);
}
void CoolLib::CCoolLib::SRT_MinHeapSort(int32_t a[], int32_t size)
{
	m_poSort->MinHeapSort(a, size);
}

// Simple Array.
void CoolLib::CCoolLib::ARR_PrintArray(void)
{
	m_poArr->PrintArray();
}
int32_t CoolLib::CCoolLib::ARR_EnterEntry(int32_t* pnData)
{
	return m_poArr->EnterEntry(pnData);
}
int32_t CoolLib::CCoolLib::ARR_Enqueue(int32_t* pnData)
{
    return m_poArr->Enqueue(pnData);
}
int32_t CoolLib::CCoolLib::ARR_PushStack(int32_t* pnData)
{
    return m_poArr->PushStack(pnData);
}
int32_t CoolLib::CCoolLib::ARR_RemoveEntry(const int32_t& nKeyData)
{
	return m_poArr->RemoveEntry(nKeyData);
}
int32_t* CoolLib::CCoolLib::ARR_Dequeue(void)
{
    return m_poArr->Dequeue();
}
int32_t* CoolLib::CCoolLib::ARR_PopStack(void)
{
    return m_poArr->PopStack();
}
int32_t* CoolLib::CCoolLib::ARR_StackTop(void)
{
    return m_poArr->StackTop();
}
uint16_t CoolLib::CCoolLib::ARR_ModifyEntry(const int32_t& nKeyData, int32_t* pnNewData)
{
	return m_poArr->ModifyEntry(nKeyData, pnNewData);
}

// Linked List.
void CoolLib::CCoolLib::LNK_PrintList(ostream* fout)
{
	m_poLink->PrintList(fout);
}
// Insert data pointer just after the last data in the list.
int32_t CoolLib::CCoolLib::LNK_Enqueue(int32_t nData)
{
	return 	m_poLink->Enqueue(nData);
}
// Insert data pointer at the beginning in the list.
int32_t CoolLib::CCoolLib::LNK_PushStack(int32_t nData)
{
	return 	m_poLink->PushStack(nData);
}
// Adds a node containing data to the list and make it bSorted list if bSorted==TRUE.
int32_t CoolLib::CCoolLib::LNK_AddNode(int32_t nData)
{
	return 	m_poLink->AddNode(nData);
}
// Modify the contents of the node that contains given key data.
uint16_t CoolLib::CCoolLib::LNK_ModifyNode(const int32_t& nKeyData, const int32_t& nNewData)
{
	return 	m_poLink->ModifyNode(nKeyData, nNewData);
}
// Retrieve the first data and erase the node.
int32_t CoolLib::CCoolLib::LNK_Dequeue(void)
{
	return 	m_poLink->Dequeue();
}
// Removes data from the list.
int32_t CoolLib::CCoolLib::LNK_RemoveNode(const int32_t& nKeyData)
{
	return 	m_poLink->RemoveNode(nKeyData);
}
// Available Space List - Erase the circular list pointed to by given list pointer.
uint16_t CoolLib::CCoolLib::LNK_DeleteList(void)
{
	return 	m_poLink->DeleteList();
}
// Inverting Circular Linked list.
uint16_t CoolLib::CCoolLib::LNK_InvertList(void)
{
	return 	m_poLink->InvertList();
}

// Binary Searching Tree.
void CoolLib::CCoolLib::BST_PrintTree(ostream* fout)
{
	m_poBst->PrintTree(fout);
}
// Adds a node containing data to the tree.
int32_t CoolLib::CCoolLib::BST_AddNode(int32_t* pnData)
{
	return m_poBst->AddNode(pnData);
}
// Removes data from the tree.
int32_t CoolLib::CCoolLib::BST_RemoveNode(const int32_t& nKeyData)
{
	return m_poBst->RemoveNode(nKeyData);
}
// Do operation with each node while in-order traversing around the whole tree.
void CoolLib::CCoolLib::BST_InorderTraverse(ostream* fout, int32_t operation)
{
	m_poBst->InorderTraverse(fout, operation);
}
// Do operation with each node while iterative in-order traversal..
void CoolLib::CCoolLib::BST_IterInorderTraverse(ostream* fout, int32_t operation)
{
	m_poBst->IterInorderTraverse(fout, operation);
}
// Do operation with each node while level-order traversing around the whole tree.
void CoolLib::CCoolLib::BST_LevelOrderTraverse(ostream* fout, int32_t operation)
{
	m_poBst->LevelOrderTraverse(fout, operation);
}
// Return existence value.
uint16_t CoolLib::CCoolLib::BSTsearch_dataNode(const int32_t& nKeyData)
{
	return m_poBst->SearchNode(nKeyData);
}