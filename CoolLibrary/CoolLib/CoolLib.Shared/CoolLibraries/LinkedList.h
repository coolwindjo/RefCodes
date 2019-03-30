#pragma once
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <functional>   // less<>, greater<>

using namespace std;

#define RETURN_TRUE 1
#define RETURN_FALSE 0

class CLinkedListImpl {
public:
    CLinkedListImpl();
    virtual ~CLinkedListImpl();
    
    /// Check whether the list is empty or not.
    uint16_t IsEmpty();

    void PrintList(ostream* fout);
    
    // Data getters
    /// Retrieve the first data.
    /// Return 0 for success, -1 for error.
    void* GetFirst();
    /// Retrieve the last data.
    /// Return 0 for success, -1 for error.
    void* GetLast();
    /// Retrieve the data of the next node of current position.
    /// Return 0 for success, 1 for last node, -1 for error.
    void* GetNext();
    /// Set current postion with the node of given value.
    uint16_t SetPostion(void* pvKeyData);
    /// Retrieve the data of the node after given number of propagation 
    /// from the first. Return 0 for success, 1 for overflow, -1 for error.
    void* GetData(int32_t nCountFromFirst);

    // Data in & out / modification
    /// Adds a node containing data to the list and make it sorted list if m_bIsSorted==TRUE.
    int32_t AddNode(void* pvDataIn);
    /// Insert data pointer just after the last data in the list.
    int32_t Enqueue(void* pvDataIn);
    /// Insert data pointer at the beginning in the list.
    int32_t PushStack(void* pvDataIn);
    
    /// Removes data from the list.
    int32_t RemoveNode(void* pvKeyData);
    /// Retrieve the first data and make it invalid.
    void* Dequeue();
    /// Pops the item on the top of the stack.
    void* PopStack();
    /// Available Space List - Erase the circular list pointed to by given list pointer.
    uint16_t DeleteList();

    /// Modify the contents of the node that contains given key data.
    uint16_t ModifyNode(void* pvKeyData, void* pvNewData);
    /// Inverting Circular Linked list.
    uint16_t InvertList(void);
    /// Concatenating Circular Linked list and delete poRightList.
    void ConcatenateList(CLinkedListImpl* poRightList);

    int32_t CopyWholeList(CLinkedListImpl* poCopiedList);

protected:
    struct ListNode {
        ListNode(void* pD, ListNode* pN)
            : pvData(pD)
            , poNextNode(pN)
        {}

        void*   pvData;
        ListNode*	poNextNode;
    };
    
    virtual void print_node(ostream* fout, ListNode* poPreNode) = 0;
    /// Define data comparison function.
 
    int32_t compare(void* pvArg1, void* pvArg2)
    {
        int32_t nResult = 0;
        if (pvArg1 < pvArg2)
            nResult = -1;
        else if (pvArg1 > pvArg2)
            nResult = 1;
        return nResult;
    }


    /// Searches list and passes back address of 
    /// the logical predecessor of node containing target.
    /// Return NULL if the list does not have the data or target node is the first node.
    uint16_t search_data(void* pvKeyData, ListNode** ppoPreNode);
    /// Inserts data pointer into a new node.
    int32_t insert_data(ListNode* poPreNode, void* pvDataIn);
    /// Deletes the target node from the list and retrieve the pointer to data.
    int32_t delete_node(ListNode* pTargetNode, void** ppvDataOut);
    /// If key data is in the list, then retrives data pointer, otherwise, returns NULL.
    void* retrieve_data(void* pvKeyData);
   
    uint16_t swap_nodes(ListNode* poFormer, ListNode* poLatter);
    /// Copy the nodes from the first to the last in the original list.
    int32_t copy_list(ListNode* poFirst, ListNode* poLast, CLinkedListImpl* poDest);
    virtual uint16_t copy_data(void* pFrom, void** ppTo) = 0;

    /// Available Space List - Provide a node for use.
    ListNode* new_node(void* pvDataIn = NULL);
    /// Available Space List - Return a node to the available list.
    void return_node(ListNode* pNode);

private:
    /// Current position node for traverse.
    ListNode* m_poNodePos;
    /// The last node pointer in the list.
    ListNode* m_poLastNode;
    /// The number of nodes in the list.
    int32_t m_nCount;
    /// If the array has been sorted, searching time can be reduced.
    uint16_t m_bIsSorted;
    /// Temporarily store memory of returning nodes.
    ListNode* m_poRecyclingNodeList;
};


template <class T>
class CLinkedList : private CLinkedListImpl {
public:
    CLinkedList(void) {}
    virtual ~CLinkedList(void) {}

    inline void PrintList(ostream* fout)
    {
        CLinkedListImpl::PrintList(fout);
    }
    
    /// Define data comparison function.
    ///virtual int32_t CompareT(const T& arg1, const T& arg2);
    virtual T* CopyDataT(const T& tFrom);

    /// Adds a node containing data to the list and make it sorted list if sorted==TRUE.
    inline int32_t AddNode(const T& tDataIn);
    /// Insert data pointer just after the last data in the list.
    inline int32_t Enqueue(const T& tDataIn);
	/// Insert data pointer at the beginning in the list.
    inline int32_t PushStack(const T& tDataIn);
	
    /// Removes data from the list.
    inline int32_t RemoveNode(const T& pvKeyData);
    /// Retrieve the first data and make it invalid.
    inline const T& Dequeue(void);
    /// Pops the item on the top of the stack.
    inline const T& PopStack(void);
    /// Available Space List - Erase the circular list pointed to by given list pointer.
    inline uint16_t DeleteList(void);

    /// Retrieve the first data.
    /// Return 0 for success, -1 for error.
    inline const T& GetFirst(void) {}
    /// Retrieve the last data.
    /// Return 0 for success, -1 for error.
    inline const T&  GetLast(void) {}
    /// Retrieve the data of the next node of current position.
    /// Return 0 for success, 1 for last node, -1 for error.
    inline const T&  GetNext(void) {}
    /// Retrieve the data of the node after given number of propagation 
    /// from the first. Return 0 for success, 1 for overflow, -1 for error.
    inline const T& GetData(int32_t nCountFromFirst) {}
 
    /// Set current postion with the node of given value.
    inline uint16_t SetPostion(const T& tKeyData);

    /// Modify the contents of the node that contains given key data.
    inline uint16_t ModifyNode(const T& tKeyData, const T& tNewData);
    inline int32_t CopyWholeList(CLinkedList* poCopiedList);
    /// Inverting Circular Linked list.
    inline uint16_t InvertList(void);
	/// Concatenating Circular Linked list and delete poRightList.
    inline void ConcatenateList(CLinkedList* poRightList);

private:
    virtual void print_node(ostream* fout, ListNode* poPreNode)
    {
        *fout << setw(1) << "[";
        *fout << setw(3) << *static_cast<T*>(poPreNode->pvData);
        fout->setf(ios::left);
        *fout << setw(2) << "]";
        fout->unsetf(ios::left);
    }

    //// Define data comparison function.

    //int32_t compare(const T& arg1, void* pvArg2)
    //{
    //    return CompareT(*static_cast<T*>(pvArg1), *static_cast<T*>(pvArg2));
    //}

    void CopyDataT1(const T& tFrom, T* pvTo) 
    {
        pvTo = new T;
        *pvTo = tFrom;
    }

    virtual uint16_t copy_data(void* pFrom, void** ppTo)
    {
        /*
        CopyDataT1(*static_cast<T*>(pFrom), static_cast<T*>(*ppTo));
        /*/
        *ppTo = CopyDataT(*static_cast<T*>(pFrom));
        //*/
        return 0;
    }

};

//// Define data comparison function.
//template <typename T>
//int32_t CLinkedList<T>::CompareT(const T& arg1, const T& arg2)
//{
//    int32_t nResult = 0;
//    if (arg1 < arg2)
//        nResult = -1;
//    else if (arg1 > arg2)
//        nResult = 1;
//    return nResult;
//}

template <typename T>
T* CLinkedList<T>::CopyDataT(const T& tFrom)
{
    T* pTo = new T;
    *pTo = tFrom;
    return pTo;
}

/// Adds a node containing data to the list and make it sorted list if sorted==TRUE.
template <typename T>
int32_t CLinkedList<T>::AddNode(const T& tDataIn)
{
    return CLinkedListImpl::AddNode(const_cast<T*>(&tDataIn));
}

/// Insert data pointer just after the last data in the list.
template <typename T>
int32_t CLinkedList<T>::Enqueue(const T& tDataIn)
{
    return CLinkedListImpl::Enqueue(const_cast<T*>(&tDataIn));
}

/// Insert data pointer at the beginning in the list.
template <typename T>
int32_t CLinkedList<T>::PushStack(const T& tDataIn)
{
    return CLinkedListImpl::PushStack(const_cast<T*>(&tDataIn));
}

/// Removes data from the list.
template <typename T>
int32_t CLinkedList<T>::RemoveNode(const T& tKeyData)
{
    return CLinkedListImpl::RemoveNode(const_cast<T*>(&tKeyData));
}

/// Retrieve the first data and make it invalid.
template <typename T>
const T& CLinkedList<T>::Dequeue(void)
{
    return *static_cast<T*>(CLinkedListImpl::Dequeue());
}

/// Pops the item on the top of the stack.
template <typename T>
const T& CLinkedList<T>::PopStack(void)
{
    return *static_cast<T*>(CLinkedListImpl::PopStack());
}

/// Available Space List - Erase the circular list pointed to by given list pointer.
template <typename T>
uint16_t CLinkedList<T>::DeleteList(void)
{
    return CLinkedListImpl::DeleteList();
}

/// Set current postion with the node of given value.
template <typename T>
uint16_t CLinkedList<T>::SetPostion(const T& tKeyData)
{
    return CLinkedListImpl::SetPostion(tKeyData);
}

/// Modify the contents of the node that contains given key data.
template <typename T>
uint16_t CLinkedList<T>::ModifyNode(const T& tKeyData, const T& tNewData)
{
    return CLinkedListImpl::ModifyNode(const_cast<T*>(&tKeyData), const_cast<T*>(&tNewData));
}

template <typename T>
int32_t CLinkedList<T>::CopyWholeList(CLinkedList<T>* poCopiedList)
{
    return CLinkedListImpl::CopyWholeList(poCopiedList);
}

/// Inverting Circular Linked list.
template <typename T>
uint16_t CLinkedList<T>::InvertList(void)
{
    return CLinkedListImpl::InvertList();
}

/// Concatenating Circular Linked list and delete poRightList.
template <typename T>
void CLinkedList<T>::ConcatenateList(CLinkedList<T>* poRightList)
{
    return CLinkedListImpl::ConcatenateList(poCopiedList);
}
