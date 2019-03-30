/*!
    \file       CoolLib.h
    \brief      Cool Library
    \pre        First initialize the system
    \warning    Not guranteed to be used
    \bug        Not all memory is freed when deleting an object of this class.
    \details    Library Managed by Cool

    \author     JO, Seunghyeon (coolwind@hotmail.co.kr)
    \version    1.0.0
    \date       2016.02.08
    \copyright  2016-Current JO, Seunghyeon Seoul
*/


#ifndef COOL_LIB_H
#define COOL_LIB_H


#ifndef __cplusplus
extern "C" {
#endif

#ifdef WIN32

#ifdef COOL_LIB_EXPORTS ///< CoolLib.dll source code will define this macro before including this header
#pragma message ("Create the Cool Library ")
#define COOL_LIB_API __declspec( dllexport ) // export symbols
#else	// #ifdef COOL_LIB_EXPORTS
#ifdef _WINDLL
#if	WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
#ifdef _DEBUG
#pragma comment( lib, "CoolLib.WindowsPhone_Win32_Debug.lib" )
#else 
#pragma comment( lib, "CoolLib.WindowsPhone_Win32_Release.lib" )
#endif
#elif	WINAPI_FAMILY == WINAPI_FAMILY_APP
#ifdef _DEBUG
#pragma comment( lib, "CoolLib.Windows_Win32_Debug.lib" )
#else 
#pragma comment( lib, "CoolLib.Windows_Win32_Release.lib" )
#endif
#else
#ifdef _DEBUG
#pragma comment( lib, "CoolLib.General_Win32_Debug.lib" )
#else 
#pragma comment( lib, "CoolLib.General_Win32_Release.lib" )
#endif
#endif	// #if	WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
#endif	// #ifdef _WINDDLL
#pragma message ("Use the Cool Library ")
#define COOL_LIB_API __declspec( dllimport )
#endif	// #ifdef COOL_LIB_EXPORTS

#else	// #ifdef WIN32

#if defined(_CONSOLE) /*|| defined(_USRDLL)*/
#ifdef COOL_LIB_EXPORTS
#pragma message ("Create the Cool Library ")
#define COOL_LIB_API __declspec( dllexport ) // export symbols
#else	// #ifdef COOL_LIB_EXPORTS
#pragma message ("Use the Cool Library ")
#define COOL_LIB_API __declspec( dllimport )
#endif	// #ifdef COOL_LIB_EXPORTS
#elif X64
#ifdef COOL_LIB_EXPORTS ///< CoolLib.dll source code will define this macro before including this header
#pragma message ("Create the Cool Library ")
#define COOL_LIB_API __declspec( dllexport ) // export symbols
#else	// #ifdef COOL_LIB_EXPORTS
#ifdef _DEBUG
#pragma comment( lib, "CoolLib.General_x64_Debug.lib" )
#else 
#pragma comment( lib, "CoolLib.General_x64_Release.lib" )
#endif
#pragma message ("Use the Cool Library ")
#define COOL_LIB_API __declspec( dllimport )
#endif	// #ifdef COOL_LIB_EXPORTS
#else	// #if defined(_CONSOLE) || defined(_USRDLL)
#ifdef COOL_LIB_EXPORTS
#define COOL_LIB_API __attribute__ ((visibility("default")))
#else	// #ifdef COOL_LIB_EXPORTS
#define COOL_LIB_API
#endif	// #ifdef COOL_LIB_EXPORTS
#endif	// #if defined(_CONSOLE) || defined(_USRDLL)

#endif	// #ifdef WIN32

#include "CodeAnalysis.h"
#include "Matrix.h"
#include "IoMethods.h"
#include "SortMethods.h"
#include "ThreadedBst.h"
#include "DynamicArray.h"
#include "LinkedList.h"

#include <windows.h> // using CTimer::


namespace CoolLib {

// Macro functions.
#ifdef __GNUC__
#define PACKED( class_to_pack ) class_to_pack __attribute__((__packed__))
#else
#define PACKED( class_to_pack ) __pragma( pack(push, 1) ) class_to_pack __pragma( pack(pop) )
#define PACK(N) __pragma(pack(push, N))
#define UNPACK	__pragma(pack(pop))
#endif

#define SWAP(x,y,t)                                                 \
		((t) = (x), (x) = (y), (y) = (t) )

#define MALLOC(p, s)                                                \
	    if (!( (p) = malloc(s) ))                                   \
        {	cerr << "Insufficient Memory"; exit( EXIT_FAILURE );    }

// Limits.
const int32_t kMaxLineLen = 1024;
const int32_t kMaxIntegerRange = 2147483647;	// Integer range : -2147483647~2147483648.

template <typename T>
struct GenericImage
{
	uint32_t 	nCols;		///< width
	uint32_t 	nRows;		///< height
	uint32_t 	nChannels;	///< number of channels
	uint32_t 	nPlanes;	///< number of planes
	T*			data;
};

enum COOL_LIB_API ReturnCode {
    kErr = -1,
    kSuccess = 0,
    // (Classname) Errors.
    kClassName_ErrorType
};

class COOL_LIB_API CCoolLib { 
public:
	CCoolLib();
	~CCoolLib();
			
	//////////////////////////////////////////////////////////////////////
    /// Enumeration of errors returned by various classes.
	//////////////////////////////////////////////////////////////////////
	void PrintError(ReturnCode rc)
    {
        char *err;
        switch (rc) {
        case kSuccess:
            err = "Success";
            break;

            // (Classname) Errors.
        case kClassName_ErrorType:
            err = "Invalid type";
            break;

            // Unknown return constant.
        default:
            err = "--- Unkown error ---: Please report to the author";
            break;
        }
        cerr << "Error: " << err << endl;
    }

    class COOL_LIB_API CTimer {
    public:
        CTimer()
            : m_szMessage(NULL)
            , m_szTime(NULL)
            , m_ulMsgLen(0)
        {}
        ~CTimer() {}

        void TimerOn(char* str)
        {
            // Set the resolution of time.
            QueryPerformanceFrequency(static_cast<_LARGE_INTEGER *>(&m_lFrequency));

            // Get the name of the function.
            m_ulMsgLen = strlen(str) + 1;
            m_szMessage = new char[m_ulMsgLen];
            memcpy_s(m_szMessage, m_ulMsgLen, str, sizeof(char)*m_ulMsgLen);

            // Start.
            QueryPerformanceCounter(static_cast<_LARGE_INTEGER*>(&m_lBeginTime));
        }

        void TimerOff()
        {	
            // End.
            QueryPerformanceCounter(static_cast<_LARGE_INTEGER*>(&m_lEndTime));

            // Calculate the time.
            __int64 elapsed = m_lEndTime.QuadPart - m_lBeginTime.QuadPart;
            double duringTime = static_cast<double>(elapsed / static_cast<double>(m_lFrequency.QuadPart));

            // Print the message.
            m_szTime = new char[m_ulMsgLen + 40];
            _snprintf_s(m_szTime, m_ulMsgLen + 40, m_ulMsgLen + 40, "%.10f seconds elapsed during %s \n",
                static_cast<double>(duringTime), m_szMessage);
            cout << endl;
            cout << m_szTime;
            delete[] m_szTime;
            m_szTime = NULL;
            delete[] m_szMessage;
            m_szMessage = NULL;
        }
    private:
        _LARGE_INTEGER m_lFrequency;
        _LARGE_INTEGER m_lBeginTime;
        _LARGE_INTEGER m_lEndTime;
        char* m_szMessage;
        char* m_szTime;
        size_t m_ulMsgLen;
    } Timer;
        
	//////////////////////////////////////////////////////////////////////
	/// Matrix calculations.
	//////////////////////////////////////////////////////////////////////
	CMatrix<int>* MAT_Create(int32_t rows, int32_t cols)
	{
		CMatrix<int>* poMat = new CMatrix<int>(rows, cols);
		return poMat;
	}
	void MAT_FillMatrix(CMatrix<int>* poMat, int32_t nMinVal, int32_t nMaxVal, double dZeroRatio);
	void MAT_PrintMatrix(CMatrix<int>* poMat, ostream* fout);
	void MAT_Transpose(CMatrix<int>* poMat);
	void MAT_MultAssign(CMatrix<int>* poMat, CMatrix<int>* poMultiplerMat);

	//////////////////////////////////////////////////////////////////////
	/// Input / Output Methods.
	//////////////////////////////////////////////////////////////////////
	void IOM_Create()
	{
		m_poIO = new CIoMethods;
	}
	int32_t IOM_GetIntegerListFromStream(ifstream* pifStream, int32_t **ppnIntegerList, int32_t nMaxLineLen);
	int32_t IOM_GetStringListFromStream(ifstream* pifStream, string **ppstrList, int32_t nMaxLineLen);

	//////////////////////////////////////////////////////////////////////
	/// Sorting Methods.
	//////////////////////////////////////////////////////////////////////
	void SRT_Create()
    {
        m_poSort = new CSortMethods<int>;
    }
    void SRT_MaxHeapSort(int32_t a[], int32_t size);
    void SRT_MinHeapSort(int32_t a[], int32_t size);

	//////////////////////////////////////////////////////////////////////
	/// Simple(General) Array.
	//////////////////////////////////////////////////////////////////////
	void ARR_Create()
    {
        m_poArr = new CDynamicArray<int>;
    }
    void ARR_Create(int32_t maxSize)
    {
        m_poArr = new CDynamicArray<int>(maxSize, TRUE);
    }
    void ARR_PrintArray(void);
    uint16_t ARR_IsFull(void)
    {
        return m_poArr->IsFull();
    }
    uint16_t ARR_IsEmpty(void)
    {
        return m_poArr->IsEmpty();
    }
    /// Input data to the entry.
    int32_t ARR_EnterEntry(int32_t* pnData);
    /// Insert data pointer just after the last data in the array.
    int32_t ARR_Enqueue(int32_t* pnData);
    /// Pushes an item onto the stack.
    int32_t ARR_PushStack(int32_t* pnData);
    /// Removes data from the array.
    int32_t ARR_RemoveEntry(const int32_t& nKeyData);
    /// Retrieve the first data and make it invalid.
    int32_t* ARR_Dequeue(void);
    /// Pops the item on the top of the stack.
    int32_t* ARR_PopStack(void);
    /// Retrieves the data from the top of the stack without changing the stack.
    int32_t* ARR_StackTop(void);
    /// Modify the contents of the entry that contains given key data.
    uint16_t ARR_ModifyEntry(const int32_t& nKeyData, int32_t* pnNewData);

    /// Linked List.
    void LNK_Create()
    {
        m_poLink = new CLinkedList<int>;
    }
    void LNK_PrintList(ostream* fout);
    /// Insert data pointer just after the last data in the list.
    int32_t LNK_Enqueue(int32_t nData);
    /// Insert data pointer at the beginning in the list.
    int32_t LNK_PushStack(int32_t nData);
    /// Adds a node containing data to the list and make it bSorted list if bSorted==TRUE.
    int32_t LNK_AddNode(int32_t nData);
    /// Modify the contents of the node that contains given key data.
    uint16_t LNK_ModifyNode(const int32_t& nKeyData, const int32_t& nNewData);
    /// Retrieve the first data and erase the node.
    int32_t LNK_Dequeue(void);
    /// Removes data from the list.
    int32_t LNK_RemoveNode(const int32_t& nKeyData);
    /// Available Space List - Erase the circular list pointed to by given list pointer.
    uint16_t LNK_DeleteList(void);
    /// Inverting Circular Linked list.
    uint16_t LNK_InvertList(void);

    /// Binary Searching Tree.
    void BST_Create()
    {
        m_poBst = new CThreadedBst<int>(TRUE);
    }
    /// Adds a node containing data to the tree.
    int32_t BST_AddNode(int32_t* pnData);
    /// Removes data from the tree.
    int32_t BST_RemoveNode(const int32_t& nKeyData);
    /// Do operation with each node while in-order traversing around the whole tree.
    void BST_InorderTraverse(ostream* fout, int32_t operation);
    /// Do operation with each node while iterative in-order traversal..
    void BST_IterInorderTraverse(ostream* fout, int32_t operation);
    /// Do operation with each node while level-order traversing around the whole tree.
    void BST_LevelOrderTraverse(ostream* fout, int32_t operation);
    /// Return existence value.
    uint16_t BSTsearch_dataNode(const int32_t& nKeyData);
    void BST_PrintTree(ostream* fout);

private:
	CIoMethods	*m_poIO;

	CSortMethods<int>	*m_poSort;
	
	CDynamicArray<int>	*m_poArr;

	CLinkedList<int>	*m_poLink;

	CThreadedBst<int>	*m_poBst;

};  //class COOL_LIB_API CCoolLib { 

} //namespace CoolLib {

#ifdef WIN32
#pragma warning(default : 4200)
#endif

#ifndef __cplusplus
}
#endif


#endif  // COOL_LIB_H
