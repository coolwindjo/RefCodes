#pragma once

template <class T>
class CDynamicArray {
public:
	CDynamicArray(void);
	CDynamicArray(const int32_t nMaxSize, const uint16_t bIsExtendable);
	~CDynamicArray(void);
	CDynamicArray& operator=(const CDynamicArray& poRightNode);

	virtual void PrintArray(void);
    virtual int32_t Compare(const T& arg1, const T& arg2);
    uint16_t IsEmpty(void);
	uint16_t IsFull(void);

	// Double the size of the array.
	int32_t DoubleArray(void);

	// Input data to the entry.
	int32_t EnterEntry(T* pDataIn);
	// Insert data pointer just after the last data in the array.
	int32_t Enqueue(T* pDataIn);
    // Pushes an item onto the stack.
    int32_t PushStack(T* pDataIn);

	// Removes data from the array.
	int32_t RemoveEntry(const T& tKeyData);
	// Retrieve the first data and make it invalid.
    T* Dequeue(void);
    // Pops the item on the top of the stack.
    T* PopStack(void);
    // Retrieves the data from the top of the stack without changing the stack.
    T* StackTop(void);

    // Get value of given index.
    T* GetData(const int32_t nIndex);

	// Modify the contents of the entry that contains given key data.
	virtual uint16_t ModifyEntry(const T& tKeyData, T* pNewData);
    // Sort the array according to the "Compare()" function.
    virtual uint16_t SortArray(void);

protected:
    class Entry {
    public:
        virtual Entry& operator=(const Entry& originalEntry)
        {
            if (this != &originalEntry) {
                m_bIsValid = originalEntry.m_bIsValid;
                // Needed to define operator= for the data type.
                m_pData = new T;
                *m_pData = *originalEntry.m_pData;
            }
            return *this;
        }
    private:
        friend class CDynamicArray;
        uint16_t m_bIsValid;
        T*	m_pData;
    };

    // Searches array for the key data and
    uint16_t search_data(const T& tKeyData, int32_t *pnResultPos);
    // Inserts data into designated index entry.
    int32_t insert_data(const int32_t nIndex, T* pDataIn);
    // Deletes data from the array and returns pointer to data to calling module.
    int32_t delete_data(int32_t nIndex, T** ppDataOut);
    // If key data is in the list, then retrieves data pointer, otherwise, returns NULL.
    T* retrieve_data(const T& tKeyData);

    // Shift up 1 entry from the given index.
    uint16_t shift_up_array(int32_t nStartPos);
    // Shift down given amount of entries from the given index.
    uint16_t shift_down_array(int32_t nStartPos, int32_t nAmount);

    // Delete array and its memory will be freed.
	uint16_t delete_array(Entry* poTargetArray, int32_t nMaxSize);

	// Copy the entries from the first to the last-1 in the original array
	// to new destination array.
	virtual int32_t copy_array(Entry* poFirst, Entry* poLast, Entry* poDest);

private:
    Entry* m_poEntryArray;
	int32_t m_nCount;
	int32_t m_nMaxSize;
    int32_t m_nFront;
	int32_t m_nRear;
	// If the array has been sorted, searching time can be reduced.
	uint16_t m_bIsSorted;
	// Array can be extended if it is setted.
	uint16_t m_bIsExtendable;
};
