#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "CoolLibraries\DynamicArray.h"
#include "CoolLibraries\SortMethods.h"
#include "CoolLibraries\ThreadedBst.h"

#define VALIDITY(INDEX) (m_poEntryArray[(INDEX)].m_bIsValid == TRUE)
#define TRUE 1
#define FALSE 0

using namespace std;

const int32_t kInitMaxSize = 8;
const int32_t kMaxSizeLimit = 4096;

template <class T>
CDynamicArray<T>::CDynamicArray(void)
	: m_bIsSorted(TRUE)
	, m_bIsExtendable(TRUE)
	, m_nCount(0)
    , m_nFront(-1)
    , m_nRear(-1)
{
	m_nMaxSize = kInitMaxSize;
	// Head structure created. Now allocate array.
	m_poEntryArray = new Entry[m_nMaxSize];
	for (int32_t i = 0; i<m_nMaxSize; i++) {
		m_poEntryArray[i].m_bIsValid = FALSE;
		m_poEntryArray[i].m_pData = NULL;
	}
}

template <class T>
CDynamicArray<T>::CDynamicArray(const int32_t nMaxSize, const uint16_t bIsExtendable)
	: m_bIsSorted(TRUE)
	, m_nCount(0)
    , m_nFront(-1)
    , m_nRear(-1)
{
	m_bIsExtendable = bIsExtendable;
	m_nMaxSize = kInitMaxSize;
	// Head structure created. Now allocate array.
	m_poEntryArray = new Entry[m_nMaxSize];
	for (int32_t i = 0; i<m_nMaxSize; i++) {
		m_poEntryArray[i].m_bIsValid = FALSE;
		m_poEntryArray[i].m_pData = NULL;
	}
}

template <class T>
CDynamicArray<T>::~CDynamicArray(void)
{
    if (m_nFront > 0)
    {
        shift_down_array(m_nFront, m_nFront);
    }
	delete_array(m_poEntryArray, m_nCount);
}

template <class T>
CDynamicArray<T>& CDynamicArray<T>::operator=(const CDynamicArray& poRightNode)
{
	if (this != &poRightNode) {
		if (this->m_poEntryArray != NULL)
		{
			this->m_nCount = poRightNode.m_nCount;
			this->m_nMaxSize = poRightNode.m_nMaxSize;
            this->m_nFront = poRightNode.m_nFront;
            this->m_nRear = poRightNode.m_nRear;
            this->m_bIsSorted = poRightNode.m_bIsSorted;
			this->m_bIsExtendable = poRightNode.m_bIsExtendable;

			this->delete_array(this->m_poEntryArray, this->m_nMaxSize);
			this->m_poEntryArray = new Entry[poRightNode.m_nMaxSize];
			this->copy_array(	poRightNode.m_poEntryArray, 
								poRightNode.m_poEntryArray + poRightNode.m_nMaxSize,
								this->m_poEntryArray);
		}
	}
	return *this;
}


template <class T>
void CDynamicArray<T>::PrintArray(void)
{
	T* pData = NULL;
	cout << "Array : ";
	// Print from the beginning.
	for (int32_t nPos = m_nFront; nPos <= m_nRear; nPos++) {
		if (VALIDITY(nPos)) {
			pData = m_poEntryArray[nPos].m_pData;
			cout << setw(1) << "[";
			cout << setw(3) << *pData;
			cout.setf(ios::left);
			cout << setw(2) << "]";
			cout.unsetf(ios::left);
		}
	}
	cout << endl;
}

// Default compare function for integers.
template <class T>
int32_t CDynamicArray<T>::Compare(const T& arg1, const T& arg2)
{
	int32_t nResult = 0;
	if (arg1 < arg2)
		nResult = -1;
	else if (arg1 > arg2)
		nResult = 1;
	return nResult;
}

template <class T>
uint16_t CDynamicArray<T>::IsEmpty(void)
{
	return (m_nCount == 0);
}

template <class T>
uint16_t CDynamicArray<T>::IsFull(void)
{
	return (m_nCount >= m_nMaxSize);
}


// Double the size of the array.
template <class T>
int32_t CDynamicArray<T>::DoubleArray(void)
{
    // Allocate an array with twice the capacity.
    Entry* poNewArray = new Entry[2 * m_nMaxSize];
    for (int32_t i = 0; i < 2 * m_nMaxSize; i++)
    {
		poNewArray[i].m_bIsValid = FALSE;
		poNewArray[i].m_pData = NULL;
	}

	// Copy from_EntryArray to poNewArray.
	int32_t nCopyCount = 0;
	if ((nCopyCount = copy_array(m_poEntryArray, m_poEntryArray + m_nMaxSize, poNewArray)) < 0)
	{
		delete_array(poNewArray, nCopyCount);
		cerr << "Error: Couldn't copy to poNewArray\n";
		return -1;
	}

	delete_array(m_poEntryArray, nCopyCount);
	m_poEntryArray = poNewArray;
	m_nMaxSize *= 2;

	return m_nMaxSize;
}


// Input data to the entry.
template <class T>
int32_t CDynamicArray<T>::EnterEntry(T* pDataIn)
{
	int32_t nFoundIndex = -1;
	if (search_data(*pDataIn, &nFoundIndex) == TRUE) 
    {
		cout << "The data value already exists.\n";
		return -1;
	}
	return insert_data(nFoundIndex, pDataIn);
}

// Insert data pointer just after the last data in the array.
template <class T>
int32_t CDynamicArray<T>::Enqueue(T* pDataIn)
{
	m_bIsSorted = FALSE;
	return insert_data(m_nRear + 1, pDataIn);
}

// Pushes an item onto the stack.
template <class T>
int32_t CDynamicArray<T>::PushStack(T* pDataIn)
{
    m_bIsSorted = FALSE;
    return insert_data(m_nRear + 1, pDataIn);
}

// Removes data from the array.
template <class T>
int32_t CDynamicArray<T>::RemoveEntry(const T& tKeyData)
{
    if (IsEmpty())
    {
        cout << "Array is empty\n";
        return 0;
    }

	T* pDataOut = NULL;
    int32_t nEntryCount = -1;
	int32_t nFoundIndex = -1;
	if (search_data(tKeyData, &nFoundIndex) == TRUE)
    {
		if ((nEntryCount = delete_data(nFoundIndex, &pDataOut)) >= 0)
		{
            delete pDataOut;
            pDataOut = NULL;
        }
	}
	return nEntryCount;
}

// Retrieve the first data and make it invalid.
template <class T>
T* CDynamicArray<T>::Dequeue(void)
{
	T* pDataOut = NULL;
	if (delete_data(m_nFront, &pDataOut) < 0)
	{
		cerr << "Error: deletion faild.\n";
		return NULL;
	}
	return pDataOut;
}

// Pops the item on the top of the stack.
template <class T>
T* CDynamicArray<T>::PopStack(void)
{
    T* pDataOut = NULL;
    if (delete_data(m_nRear, &pDataOut) < 0)
    {
        cerr << "Error: deletion faild.\n";
        return NULL;
    }
    return pDataOut;
}

// Retrieves the data from the top of the stack without changing the stack.
template <class T>
T* CDynamicArray<T>::StackTop(void)
{
    T* pDataOut = NULL;
    if ((pDataOut = GetData(m_nRear)) == NULL)
    {
        cerr << "Error: deletion faild.\n";
        return NULL;
    }
    return pDataOut;
}


// Get value of given index.
template <class T>
T* CDynamicArray<T>::GetData(const int32_t nIndex)
{
    T* pDataOut = NULL;
    if (m_poEntryArray[nIndex].m_bIsValid)
        pDataOut = m_poEntryArray[nIndex].m_pData;
    return pDataOut;
}


// Modify the contents of the entry that contains given key data.
template <class T>
uint16_t CDynamicArray<T>::ModifyEntry(const T& tKeyData, T* pNewData)
{
	T* pData = NULL;

	// Needed to define operator= for data.
	if ((pData = retrieve_data(tKeyData)) != NULL) {
		*pData = *pNewData;
		m_bIsSorted = FALSE;
		return TRUE;
	}
	else
	{
		cerr << "Error: given data does not exist.\n";
		return FALSE;
	}
}

// Sort the array according to the "Compare()" function.
template <class T>
uint16_t CDynamicArray<T>::SortArray(void)
{

    return FALSE;
}


// Searches array for the key data and
template <class T>
uint16_t CDynamicArray<T>::search_data(const T& tKeyData, int32_t *pnResultPos)
{
#define COMPARE(INDEX) \
        (Compare(tKeyData, *m_poEntryArray[(INDEX)].m_pData) )

	if (IsEmpty())
	{
		*pnResultPos = 0;
		return FALSE;
	}

	if (m_bIsSorted)
	{
		// In case of the sorted list, firstly compared with
		if (VALIDITY(m_nFront))
		{
			if (COMPARE(m_nFront) < 0)
			{
				*pnResultPos = m_nFront;
				return FALSE;
			}
		}
		if (VALIDITY(m_nRear))
		{
			if (COMPARE(m_nRear) > 0)
			{
				*pnResultPos = m_nRear + 1;
				return FALSE;
			}
		}

		// Search from the beginning.
		for (int32_t nPos = m_nFront; nPos <= m_nRear; nPos++)
		{
			if (VALIDITY(nPos)) {
				if (COMPARE(nPos) > 0)
				{
					continue;
				}
				else if (COMPARE(nPos) == 0)
				{
					*pnResultPos = nPos;
					return TRUE;
				}
				else // (COMPARE(nPos) < 0)
				{
					*pnResultPos = nPos;
					return FALSE;
				}
			}
		}
		*pnResultPos = m_nRear + 1;
		return FALSE;
	}

	// Search from the beginning.
	for (int32_t nPos = m_nFront; nPos <= m_nRear; nPos++)
	{
		if (VALIDITY(nPos)) {
			if (COMPARE(nPos) == 0)
			{
				*pnResultPos = nPos;
				return TRUE;
			}
		}
	}
	*pnResultPos = m_nRear + 1;
	return FALSE;
}


// Inserts data into designated index entry.
template <class T>
int32_t CDynamicArray<T>::insert_data(const int32_t nIndex, T* pDataIn)
{
	if ((nIndex < 0) || (pDataIn == NULL)) {
		cerr << "Error: Invalid index or data pointer.\n";
		return -1;
	}

	while ((nIndex >= m_nMaxSize) && (m_nMaxSize < kMaxSizeLimit)) 
    {
		if (m_bIsExtendable)
        {
			if (DoubleArray() == -1)
            {
				cerr << "Error: Failed to double the array.\n";
				return -1;
			}
		}
		else 
        {
			cerr << "Error: Index value is out of bound.\n";
			return -1;
		}
	}

	// Check whether entry of given index is available or not.
    if (m_poEntryArray[nIndex].m_bIsValid == TRUE)
    {	// Insert data in the middle of the array and shift up all entries after this index.
        shift_up_array(nIndex);
    }

    // Insert data.
    m_poEntryArray[nIndex].m_pData = pDataIn;
    m_poEntryArray[nIndex].m_bIsValid = TRUE;

    if (IsEmpty())
    {
        m_nFront = nIndex;
    }

    if (nIndex > m_nRear)
    {
        m_nRear = nIndex;
    }
    else
    {
        m_nRear++;
    }
    
    m_nCount++;

	return m_nCount;
}


// Deletes data from the array and returns pointer to data to calling module.
template <class T>
int32_t CDynamicArray<T>::delete_data(int32_t nIndex, T** ppDataOut)
{
	if ((nIndex < m_nFront) || (nIndex > m_nRear))
	{
		cerr << "Error: Index value is out of bound.\n";
		return -1;
	}

	if (IsEmpty()) 
	{
		cerr << "Error: The Array is empty.\n";
		return -1;
	}

	// Check whether entry of given index is available or not.
	if (m_poEntryArray[nIndex].m_bIsValid == FALSE) {
		cerr << "Error: Invalid index\n";
		return -1;
	}

	// Delete the datum
	*ppDataOut = m_poEntryArray[nIndex].m_pData;
	m_poEntryArray[nIndex].m_bIsValid = FALSE;

    if (nIndex == m_nFront)
    {    // Deleting the first node.
        for (int32_t nPos = m_nFront; nPos <= m_nRear; nPos++)
        {
            if (m_poEntryArray[nPos].m_bIsValid == TRUE)
            {
                m_nFront = nPos;
                break;
            }
        }
        if (m_nFront > m_nMaxSize - m_nFront)
        {
            shift_down_array(m_nFront, m_nFront);
        }
    }
	else if (nIndex == m_nRear)
	{	// Deleting the last node.
		for (int32_t nPos = m_nRear; nPos >= m_nFront; nPos--)
		{
			if (m_poEntryArray[nPos].m_bIsValid == TRUE)
			{
				m_nRear = nPos;
				break;
			}
		}
	}
	else
    {	// Delete data in the middle of the array and shift down all entries after this index.
        shift_down_array(nIndex+1, 1);

		m_nRear--;
	}	// if (nIndex != m_nRear) 

	m_nCount--;

	return m_nCount;
}



// If key data is in the list, then retrieves data pointer, otherwise, returns NULL.
template <class T>
T* CDynamicArray<T>::retrieve_data(const T& tKeyData)
{
	T* pDataOut = NULL;
	int32_t nFoundIndex = 0;
	if (search_data(tKeyData, &nFoundIndex) == TRUE) {
        pDataOut = GetData(nFoundIndex);
	}
	return pDataOut;
}


// Shift up 1 entry from the given index.
template <class T>
uint16_t CDynamicArray<T>::shift_up_array(int32_t nStartPos)
{
    if (IsFull())
    {
        if (m_bIsExtendable)
        {
            if (DoubleArray() == -1)
            {
                cerr << "Error: Failed to double the array.\n";
                return FALSE;
            }
        }
        else
        {
            // If the array is not extensible, delete out the last entry.
            T* tmpDataOut = NULL;
            if (delete_data(m_nRear, &tmpDataOut) >= 0)
            {
                delete tmpDataOut;
                tmpDataOut = NULL;
            }
        }
    }	//if (IsFull())

    // Get ready to shift up.
    Entry* poTempArray = new Entry[m_nMaxSize];
    for (int32_t i = 0; i < m_nMaxSize; i++) {
        poTempArray[i].m_bIsValid = FALSE;
        poTempArray[i].m_pData = NULL;
    }

    // Copy from _Array to poTempArray.
    int32_t nCopyCount;
    nCopyCount = copy_array(m_poEntryArray + nStartPos, m_poEntryArray + m_nRear + 1, poTempArray);

    // Copy from poTempArray to _Array.
    if (copy_array(poTempArray, poTempArray + nCopyCount, m_poEntryArray + nStartPos + 1) != nCopyCount)
    {
        cerr << "Error: Incorrect copy operation.\n";
        return FALSE;
    }

    // Clean up.
    delete_array(poTempArray, nCopyCount);

    return TRUE;
}

// Shift down given amount of entries from the given index.
template <class T>
uint16_t CDynamicArray<T>::shift_down_array(int32_t nStartPos, int32_t nAmount)
{
    // Get ready to shift down.
    Entry* poTempArray = new Entry[m_nMaxSize];
    for (int32_t i = 0; i < m_nMaxSize; i++) {
        poTempArray[i].m_bIsValid = FALSE;
        poTempArray[i].m_pData = NULL;
    }
    
    // Copy from _Array to poTempArray.
    int32_t nCopyCount;
    nCopyCount = copy_array(m_poEntryArray + nStartPos, m_poEntryArray + m_nRear + 1, poTempArray);
 
    // Copy from poTempArray to _Array.
    if (copy_array(poTempArray, poTempArray + nCopyCount, m_poEntryArray + nStartPos - nAmount) != nCopyCount)
    {
        cerr << "Error: Incorrect copy operation.\n";
        return FALSE;
    }
    // Clean up.
    delete_array(poTempArray, nCopyCount);
    
    return TRUE;
}


// Delete array and its memory will be freed.
template <class T>
uint16_t CDynamicArray<T>::delete_array(Entry* poTargetArray, int32_t nMaxSize)
{
    if (poTargetArray != NULL)
    {
        for (int32_t i = 0; i < nMaxSize; i++)
        {
            delete poTargetArray[i].m_pData;
            poTargetArray[i].m_pData = NULL;
        }
        delete[] poTargetArray;
        poTargetArray = NULL;
        return TRUE;
    }
    else
    {
        cerr << "Error: array deletion faild.\n";
        return FALSE;
    }
}


// Copy the entries from the first to the last-1 in the original array to
// new destination array.
template <class T>
int32_t CDynamicArray<T>::copy_array(Entry* poFirst, Entry* poLast, Entry* poDest)
{
    if (poFirst == NULL || poLast == NULL || poDest == NULL)
    {
        cerr << "Error: Invalid source or destination for copy\n";
        return -1;
    }

    int32_t nCount = 0;
    while ((poFirst != NULL) && (poFirst != poLast))
    {
        if (poFirst->m_bIsValid == TRUE) 
        {
            *poDest++ = *poFirst++;
            nCount++;
        }
        else
        {
            poFirst++;
        }
    }
    return nCount;
}

template class CDynamicArray<int>;
template class CDynamicArray<float>;
template class CDynamicArray<CThreadedBst<int>::BstNode>;
template class CDynamicArray<CThreadedBst<float>::BstNode>;