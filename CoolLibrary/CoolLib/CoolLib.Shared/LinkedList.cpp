#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "CoolLibraries\LinkedList.h"

using namespace std;

CLinkedListImpl::CLinkedListImpl(void)
	: m_poNodePos(NULL)
	, m_poLastNode(NULL)
	, m_poRecyclingNodeList(NULL)
	, m_nCount(0)
	, m_bIsSorted(RETURN_TRUE)
{
}

CLinkedListImpl::~CLinkedListImpl(void)
{
    DeleteList();
	if (m_poRecyclingNodeList != NULL) 
    {
        void* pDataOut = NULL;
        ListNode* poPreNode = NULL;
        ListNode* pTargetNode = NULL;

		// Delete all nodes in the Available Space List.
        pTargetNode = m_poRecyclingNodeList;
        while (pTargetNode != NULL)
        {
			pDataOut = pTargetNode->pvData;
			if (pDataOut != NULL)
			{
				delete pDataOut;
				pDataOut = NULL;
			}

            poPreNode = pTargetNode;
            pTargetNode = pTargetNode->poNextNode;

            delete poPreNode;
			poPreNode = NULL;
		}
        m_poRecyclingNodeList = NULL;
	}
}

uint16_t CLinkedListImpl::IsEmpty()
{
    return (m_nCount == 0);
}

void CLinkedListImpl::PrintList(ostream* fout)
{
    ListNode* poPreNode = NULL;
    if (m_poLastNode != NULL) {
        ListNode* pTargetNode = m_poLastNode->poNextNode;
        *fout << "List : ";
        do {
            poPreNode = pTargetNode;
            pTargetNode = pTargetNode->poNextNode;

            print_node(fout, poPreNode);

        } while (pTargetNode != m_poLastNode->poNextNode);
        *fout << endl;
    }
    else
        *fout << "Empty List\n";
}

/// Adds a node containing data to the list and make it sorted list if m_bIsSorted==TRUE.
int32_t CLinkedListImpl::AddNode(void* pvDataIn)
{
    ListNode* poPreNode = NULL;
    if (search_data(pvDataIn, &poPreNode) == RETURN_TRUE)
    {
        cout << "The data value already exists.\n";
        return -1;
    }
    return insert_data(poPreNode, pvDataIn);
}

/// Insert data pointer just after the last data in the list.
int32_t CLinkedListImpl::Enqueue(void* pvDataIn)
{
    m_bIsSorted = RETURN_FALSE;
    return insert_data(m_poLastNode, pvDataIn);
}

/// Insert data pointer at the beginning in the list.
int32_t CLinkedListImpl::PushStack(void* pvDataIn)
{
    return Enqueue(pvDataIn);
}


/// Removes data from the list.
int32_t CLinkedListImpl::RemoveNode(void* pvKeyData)
{
    if (IsEmpty())
    {
        cout << "List is empty\n";
        return 0;
    }

    void* pDataOut = NULL;
    ListNode* poPreNode = NULL;
    int32_t nNodeCount = -1;
    if (search_data(pvKeyData, &poPreNode) == RETURN_TRUE)
    {
        if ((nNodeCount = delete_node(poPreNode->poNextNode, &pDataOut)) < 0)
        {
            cerr << "Error: Failed to delete\n";
            return -1;
        }
    }

    return nNodeCount;
}

/// Retrieve the first data and erase the node.
void* CLinkedListImpl::Dequeue(void)
{
    void* pvDataOut = GetFirst();
    if (pvDataOut != NULL)
    {
        if (RemoveNode(pvDataOut) < 0)
        {
            cerr << "Error: Failed to delete\n";
            return NULL;
        }
    }
    return pvDataOut;
}

/// Pops the item on the top of the stack.
void* CLinkedListImpl::PopStack(void)
{
    void* pDataOut = GetLast();
    if (pDataOut != NULL)
    {
        if (RemoveNode(pDataOut) < 0)
        {
            cerr << "Error: Failed to delete\n";
            return NULL;
        }
    }
    return pDataOut;
}

/// Available Space List - Erase the circular list pointed to by given list pointer.
uint16_t CLinkedListImpl::DeleteList(void)
{
    if (m_poLastNode != NULL) 
    {
        if (IsEmpty() == RETURN_FALSE)
        {
            ListNode* poFirstNode = NULL;

            // Get the first node.
            poFirstNode = m_poLastNode->poNextNode;

            // Put the first node of the Recycleing Node List 
            // after the last node of the current list.
            m_poLastNode->poNextNode = m_poRecyclingNodeList;

            // Set the head pointer of the Recycleing Node List 
            // on the first node of the current list.
            m_poRecyclingNodeList = poFirstNode;

            m_poLastNode = NULL;
            m_poNodePos = NULL;
            m_nCount = 0;
            m_bIsSorted = RETURN_TRUE;

            return RETURN_TRUE;
        }
    }
    return RETURN_FALSE;
}


/// Retrieve the first data.
/// Return 0 for success, -1 for error.
void* CLinkedListImpl::GetFirst(void)
{
    if (IsEmpty()) {
        return NULL;
    }
    else {
        m_poNodePos = m_poLastNode->poNextNode;
        return m_poNodePos->pvData;
    }
}

/// Retrieve the last data.
/// Return 0 for success, -1 for error.
void* CLinkedListImpl::GetLast(void)
{
    if (IsEmpty()) {
        return NULL;
    }
    else {
        m_poNodePos = m_poLastNode;
        return m_poNodePos->pvData;
    }
}

/// Retrieve the data of the next node of current position.
/// Return 0 for success, 1 for last node, -1 for error.
void* CLinkedListImpl::GetNext(void)
{
    if (IsEmpty() || (m_poNodePos == NULL)) {
        return NULL;
    }
    else {
        m_poNodePos = m_poNodePos->poNextNode;
        return m_poNodePos->pvData;
    }
}

/// Retrieve the data of the node after given number of propagation
/// from the first. Return 0 for success, 1 for overflow, -1 for error.
void* CLinkedListImpl::GetData(int32_t nCountFromFirst)
{
    if (IsEmpty() || (nCountFromFirst > m_nCount))
    {
        return NULL;
    }
    else 
    {
        m_poNodePos = m_poLastNode->poNextNode;
        for (int32_t i = 0; i < nCountFromFirst; i++)
        {
            m_poNodePos = m_poNodePos->poNextNode;
        }
        return m_poNodePos->pvData;
    }
}

/// Set current postion with the node of given value.
uint16_t CLinkedListImpl::SetPostion(void* pvKeyData)
{
    ListNode* poPreNode = NULL;
    uint16_t bIsPresent = RETURN_FALSE;
    if ((bIsPresent = search_data(pvKeyData, &poPreNode)) == RETURN_TRUE) {
        if (poPreNode != NULL)
        {
            m_poNodePos = poPreNode->poNextNode;
        }
        else
        {
            // Current position is the very first of the list.
            m_poNodePos = m_poLastNode->poNextNode;
        }
    }
    return bIsPresent;
}


/// Modify the contents of the node that contains given key data.
uint16_t CLinkedListImpl::ModifyNode(void* pvKeyData, void* pvNewData)
{
	void* pvData = NULL;

    // Needed to define operator= for data.
    if ((pvData = retrieve_data(pvKeyData)) != NULL)
    {
        // Delete the old data of the node.
        delete pvData;

        copy_data(pvNewData, &pvData);

        m_bIsSorted = RETURN_FALSE;
        return RETURN_TRUE;
	}
    else
    {
        cerr << "Error: given data does not exist.\n";
        return RETURN_FALSE;
    }
}


int32_t CLinkedListImpl::CopyWholeList(CLinkedListImpl* poCopiedList)
{
	if (m_poLastNode != NULL && !IsEmpty()) {
		if (m_nCount != copy_list(m_poLastNode->poNextNode, m_poLastNode, poCopiedList)) {
			cerr << "Error: Wrong copy occured\n";
			return -1;
		}
	}
	else {
		cerr << "Error: The list has no item\n";
		return -1;
	}
	return 0;
}

/// Inverting Circular Linked list.
uint16_t CLinkedListImpl::InvertList(void)
{
	int32_t count = 0;
	if (m_poLastNode != NULL) 
    {
		// Initialization.
		ListNode* lead = m_poLastNode->poNextNode;
		ListNode* middle = m_poLastNode;
		ListNode* trail = NULL;

		// Redesignate the first node as last one to finish properly.
		m_poLastNode = m_poLastNode->poNextNode;
		do
        {
			// Proceeding by shift.
			trail = middle;
			middle = lead;
			lead = lead->poNextNode;
			// Change the direction of the link of middle node.
			middle->poNextNode = trail;
			count++;
		} while (lead != m_poLastNode);

        if (count == m_nCount)
        {
            return RETURN_TRUE;
        }
	}
	return RETURN_FALSE;
}

/// Concatenating Circular Linked list and delete listLatter.
void CLinkedListImpl::ConcatenateList(CLinkedListImpl* poRightList)
{
	if (m_poLastNode != NULL && poRightList->m_poLastNode != NULL) {
		ListNode* tmp = m_poLastNode->poNextNode;
		m_poLastNode->poNextNode = poRightList->m_poLastNode->poNextNode;
		poRightList->m_poLastNode->poNextNode = tmp;
		m_poLastNode = poRightList->m_poLastNode;
		m_nCount += poRightList->m_nCount;
		// Delete poRightList.
		poRightList->~CLinkedListImpl();
	}
}



/// Searches list and passes back address of 
/// the logical predecessor of node containing target.
/// Return NULL if the list does not have the data or target node is the first node.
uint16_t CLinkedListImpl::search_data(void* pvKeyData, ListNode** ppoPreNode)
{
#define COMPARE(DATA)   (compare(pvKeyData, (DATA)))

    if (IsEmpty())
    {
        *ppoPreNode = NULL;
        return RETURN_FALSE;
    }

    if (m_bIsSorted)
    {
        // In case of sorted list, it is a test for argument > last nod in the list.
        if (COMPARE(m_poLastNode->pvData) > 0)
        {
            // Set predecessor node with the last one.
            *ppoPreNode = m_poLastNode;
            return RETURN_FALSE;
        }
        if (COMPARE(m_poLastNode->poNextNode->pvData) < 0)
        {
            // Set predecessor node with the NULL pointer.
            *ppoPreNode = NULL;
            return RETURN_FALSE;
        }

        // Search from the beginning.
        *ppoPreNode = m_poLastNode;
        ListNode* pTargetNode = m_poLastNode->poNextNode;
        for (int32_t i = 0; i < m_nCount; i++)
        {
            if (COMPARE(pTargetNode->pvData) > 0)
            {
                *ppoPreNode = pTargetNode;
                pTargetNode = pTargetNode->poNextNode;
            }
            else if (COMPARE(pTargetNode->pvData) == 0)
            {
                return RETURN_TRUE;
            }
            else // COMPARE(*pTargetNode->pvData) < 0
            {
                return RETURN_FALSE;
            }
        }
        *ppoPreNode = m_poLastNode;
        return RETURN_FALSE;
    } // if (sorted) 

      // Search from the beginning.
    *ppoPreNode = m_poLastNode;
    ListNode* pTargetNode = m_poLastNode->poNextNode;
    for (int32_t i = 0; i < m_nCount; i++)
    {
        if (COMPARE(pTargetNode->pvData) == 0)
        {
            return RETURN_TRUE;
        }

        if (pTargetNode == m_poLastNode)
        {
            // Set predecessor node with the last one.
            break;
        }

        *ppoPreNode = pTargetNode;
        pTargetNode = pTargetNode->poNextNode;
    }
    *ppoPreNode = m_poLastNode;
    return RETURN_FALSE;
}

/// Inserts data pointer into a new node.
int32_t CLinkedListImpl::insert_data(ListNode* poPreNode, void* pvDataIn)
{
	if (pvDataIn == NULL) 
    {
		cerr << "Error: Invalid data pointer.\n";
		return -1;
	}

    // Prepare a node to carry the input data.
	ListNode* poNewNode = NULL;
    if ((poNewNode = new_node()) == NULL)
    {
        cerr << "Error: failed to memory allocation.\n";
        return -1;
    }

    // Insert the input data.
    copy_data(pvDataIn, &(poNewNode->pvData));
	poNewNode->poNextNode = poNewNode;

    if (IsEmpty())
    {
        // Adding to the empty list. Set last position to the new node.
        m_poLastNode = poNewNode;
    }
    else if (poPreNode == NULL)
    {
        // Adding at front.
        poNewNode->poNextNode = m_poLastNode->poNextNode;
        m_poLastNode->poNextNode = poNewNode;
    }
    else
    {
        // Adding in middle or at end.
        poNewNode->poNextNode = poPreNode->poNextNode;
        poPreNode->poNextNode = poNewNode;

        // Check for adding new node at the end of the list.
        if (poPreNode == m_poLastNode)
        {
            m_poLastNode = poNewNode;
        }
    }

    m_nCount++;

    return m_nCount;
}

/// Deletes the target node from the list and retrieve the pointer to data.
int32_t CLinkedListImpl::delete_node(ListNode* pTargetNode, void** ppvDataOut)
{
    if (pTargetNode == NULL)
    {
        cerr << "Error: Invalid target node.\n";
        return -1;
    }

    if (IsEmpty())
    {
        cerr << "Error: The List is empty.\n";
        return -1;
    }
    
    // Delete the datum
    *ppvDataOut = pTargetNode->pvData;

    ListNode* poPreNode = NULL;
    if (search_data(pTargetNode->pvData, &poPreNode)) 
    {
        poPreNode->poNextNode = pTargetNode->poNextNode;

        // Test for deleting last node.
        if (pTargetNode == m_poLastNode)
        {
            m_poLastNode = poPreNode;
        }

        // Test for deleting current position.
        if (pTargetNode == m_poNodePos) 
        {
            m_poNodePos = poPreNode;
        } 

        m_nCount--;
 
        // Temporarily store the deleted node to the Recycling Node List.
        return_node(pTargetNode);

        return m_nCount;
    } // if (search_data(pTargetNode->pvData, &poPreNode)) 
    else
    {
        return -1;
    }
}

/// If key data is in the list, then retrives data pointer, otherwise, returns NULL.
void* CLinkedListImpl::retrieve_data(void* pvKeyData)
{
    void* pvDataOut = NULL;
    ListNode* poPreNode = NULL;
    if (search_data(pvKeyData, &poPreNode) == RETURN_TRUE)
    {
        if (poPreNode != NULL)
        {
            if (poPreNode->poNextNode != NULL)
            {
                pvDataOut = poPreNode->poNextNode->pvData;
            }
        }
    }
    return pvDataOut;
}


uint16_t CLinkedListImpl::swap_nodes(ListNode* poPreNodeOfFormer, ListNode* poPreNodeOfLatter)
{
    if (poPreNodeOfFormer == NULL || poPreNodeOfLatter == NULL)
    {
        cerr << "Error: Invalid nodes for swapping\n";
        return RETURN_FALSE;
    }

    ListNode* poFormer = poPreNodeOfFormer->poNextNode;
    ListNode* poLatter = poPreNodeOfLatter->poNextNode;

    // Removing poFormer.
    poPreNodeOfFormer->poNextNode = poFormer->poNextNode;

    // Insert poFormer into ex-positionof the poLatter. (1)
    poFormer->poNextNode = poLatter->poNextNode;

    if (poFormer == poPreNodeOfLatter)
    {
        // If the previous node of the poLatter was poFormer,
        // simply connet the poLatter to poFormer.
        poLatter->poNextNode = poFormer;
    }
    else
    {
        // Insert poLatter into ex-positionof the poFormer.
        poLatter->poNextNode = poPreNodeOfFormer->poNextNode;
        poPreNodeOfFormer->poNextNode = poLatter;

        // Insert poFormer into ex-positionof the poLatter. (2)
        poPreNodeOfLatter->poNextNode = poFormer;
    }

    return RETURN_TRUE;
}

/// Copy the nodes from the first to the last in the original list.
int32_t CLinkedListImpl::copy_list(ListNode* poFirst, ListNode* poLast, CLinkedListImpl* poDest)
{
    if (poFirst == NULL || poLast == NULL || poDest == NULL)
    {
        cerr << "Error: Invalid source or destination for copy\n";
        return -1;
    }

    int32_t nCount = 0;
    void* pvData = NULL;
    while ((poFirst != NULL) && (poFirst != poLast))
    {
        copy_data(poFirst->pvData, &pvData);
        if (poDest->Enqueue(pvData) >= 0)
        {
            nCount++;
        }
        else
        {
            cerr << "Error: Can't enqueue\n";
            return -1;
        }
        poFirst = poFirst->poNextNode;
    }
    return nCount;
}


/// Available Space List - Provide a node for use.
typename CLinkedListImpl::ListNode* CLinkedListImpl::new_node(void* pvDataIn)
{
    ListNode* poNewNode = NULL;
    if (m_poRecyclingNodeList != NULL)
    {
        // Get the first node of the recycling node list.
        poNewNode = m_poRecyclingNodeList;
        m_poRecyclingNodeList = m_poRecyclingNodeList->poNextNode;

        // If the data in the node is valid.
        if (poNewNode->pvData != NULL)
        {
            // Delete the old data of the node.
            delete poNewNode->pvData; 
            poNewNode->pvData = NULL;
        }

        poNewNode->pvData = pvDataIn;
    }
    else
    {
        // No available node to reuse.
        poNewNode = new ListNode(pvDataIn, NULL);
    }

    return poNewNode;
}

/// Available Space List - Return a node to the available list.
void CLinkedListImpl::return_node(ListNode* poNode)
{
	if (poNode != NULL) {
		poNode->poNextNode = m_poRecyclingNodeList;
		m_poRecyclingNodeList = poNode;
	}
}

