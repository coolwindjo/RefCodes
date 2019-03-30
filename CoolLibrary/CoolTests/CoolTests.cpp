#include<stdio.h>

#include "CoolTests.h"

#include "CoolLib.h"

CoolTests::CoolTests()
{
}

CoolTests::~CoolTests()
{
}

void CoolTests::MatrixTest(void)
{
    CoolLib::CCoolLib cool;
    CMatrix<int>* pMat1;
    CMatrix<int>* pMat2;
    pMat1 = cool.MAT_Create(10, 5);
    pMat2 = cool.MAT_Create(10, 10);
    cool.MAT_FillMatrix(pMat1, 3, 10, 0.7);
    cool.MAT_FillMatrix(pMat2, 3, 10, 0.7);
    cool.MAT_PrintMatrix(pMat1, &cout);
    cool.MAT_Transpose(pMat1);
    cool.MAT_PrintMatrix(pMat1, &cout);
    cool.MAT_PrintMatrix(pMat2, &cout);
    cool.MAT_MultAssign(pMat1, pMat2);
    cool.MAT_PrintMatrix(pMat1, &cout);
}

// Generate an Integer Matrix.
int** CoolTests::genIntMatrix(int rows, int cols, int minVal, int maxVal, double zeroRatio)
{
	if ((rows>0) && (cols>0) && (minVal<maxVal) && (zeroRatio >= 0) && (zeroRatio <= 1)) {
		int** mat = new int*[rows];
		for (int i = 0; i<rows; i++) {
			mat[i] = new int[cols];
		}
		double denominator = (1 / (static_cast<double>(1) - zeroRatio));
		// Random integer generations.
		srand(static_cast<unsigned int>(time(NULL)));
		for (int i = 0; i<rows; i++) {
			int val = 0;
			for (int j = 0; j<cols; j++) {
				val = static_cast<int>(
					minVal +
					static_cast<double>(rand())
					/ (static_cast<double>(RAND_MAX) + static_cast<double>(1))
					*(maxVal - minVal + 1)
					*denominator
					);
				if (val <= maxVal)
					mat[i][j] = val;
				else
					mat[i][j] = 0;
			}
		}
		return mat;
	}
	else {
		cerr << "Error: Invalid Parameters." << endl;
		return NULL;
	}
}

// Delete given Integer Matrix.
bool CoolTests::delIntMatrix(int** mat, int rows)
{
	if (mat) {
		for (int i = 0; i<rows; i++) {
			if (mat[i])
				delete[] mat[i];
				mat[i] = NULL;
		}
		delete[] mat;
		mat = NULL;
		return TRUE;
	}
	return FALSE;
}

// Print given Integer Matrix.
void CoolTests::printIntMatrix(int** mat, int rows, int cols)
{
	if (mat) {
		cout << setw(6) << " MAT";
		for (int j = 0; j<cols; j++) {
			cout << setw(1) << "[";
			cout << setw(3) << j + 1;
			cout.setf(ios::left);
			cout << setw(2) << "]";
			cout.unsetf(ios::left);
		}
		cout << endl;
		for (int i = 0; i<rows; i++) {
			cout << setw(1) << "[";
			cout << setw(3) << i + 1;
			cout.setf(ios::left);
			cout << setw(2) << "]";
			cout.unsetf(ios::left);
			for (int j = 0; j<cols; j++) {
				cout << setw(5) << mat[i][j] << setw(1) << " ";
			}
			cout << endl;
		}
	}
}

// Test array manipulation.
int CoolTests::ArrayManipulation(void)
{
    CoolLib::CCoolLib cool;
    cool.ARR_Create();

    int* data = new int;
    *data = 3;
    if (cool.ARR_EnterEntry(data) == 1) {
        cout << *data << " added with sorting.\n";
    }
    else {
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    data = new int;
    *data = 5;
    if (cool.ARR_EnterEntry(data) == 2) {
        cout << *data << " added with sorting.\n";
    }
    else {
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    data = new int;
    *data = 1;
    if (cool.ARR_EnterEntry(data) == 3) {
        cout << *data << " added with sorting.\n";
    }
    else {
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    data = new int;
    *data = 2;
    if (cool.ARR_EnterEntry(data) == 4) {
        cout << *data << " added with sorting.\n";
    }
    else {
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    data = new int;
    *data = 6;
    if (cool.ARR_Enqueue(data) == 5) {
        cout << *data << " enqueued.\n";
    }
    else {
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    data = new int;
    *data = 4;
    if (cool.ARR_EnterEntry(data) == 6) {
        cout << *data << " added.\n";
    }
    else {
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    data = new int;
    *data = 1;
    if (cool.ARR_EnterEntry(data) == 7) {
        cout << *data << " added.\n";
    }
    else {
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    int key = 2;
    data = new int;
    *data = 7;
    if (cool.ARR_ModifyEntry(key, data))
        cout << key << " changed to " << *data << endl;
    cool.ARR_PrintArray();
    delete data;
    data = NULL;

    key = 7;
    if (cool.ARR_RemoveEntry(key) == 5)
        cout << key << " deleted\n";
    cool.ARR_PrintArray();

    data = new int;
    *data = -4;
    if (cool.ARR_EnterEntry(data) == 6) {
        cout << *data << " added.\n";
    }
    else {
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    data = new int;
    *data = -2;
    if (cool.ARR_EnterEntry(data) == 7) {
        cout << *data << " added.\n";
    }
    else {
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    data = new int;
    *data = 14;
    if (cool.ARR_EnterEntry(data) == 8) {
        cout << *data << " added.\n";
    }
    else {
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    data = new int;
    *data = 12;
    if (cool.ARR_EnterEntry(data) == 9) {
        cout << *data << " added.\n";
    }
    else {
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    data = new int;
    *data = -1;
    if (cool.ARR_EnterEntry(data) == 10) {
        cout << *data << " added.\n";
    }
    else {
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    data = new int;
    *data = -6;
    if (cool.ARR_EnterEntry(data) == 11) {
        cout << *data << " added.\n";
    }
    else {
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    if ((data = cool.ARR_Dequeue()) != NULL) {
        cout << *data << " deleted\n";
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();


    if ((data = cool.ARR_Dequeue()) != NULL) {
        cout << *data << " deleted\n";
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    data = new int;
    *data = 12;
    if (cool.ARR_EnterEntry(data) == 10) {
        cout << *data << " added\n";
    }
    else {
        delete data;
        data = NULL;
    }
    cool.ARR_PrintArray();

    //GeneralArray<int> arr2;
    //arr2 = sarr;
    //arr2.printArray();

    return 0;
}


int CoolTests::LinkedListTest(void)
{
    CoolLib::CCoolLib cool;

    cool.LNK_Create();
    cool.LNK_PrintList(&cout);

    int data = 2;
    if (cool.LNK_AddNode(data) == 1) {
        cout << data << " added\n";
    }
    cool.LNK_PrintList(&cout);

    data = 3;
    if (cool.LNK_AddNode(data) == 2) {
        cout << data << " added\n";
    }
    cool.LNK_PrintList(&cout);

    data = 1;
    if (cool.LNK_AddNode(data) == 3) {
        cout << data << " added\n";
    }
    cool.LNK_PrintList(&cout);

    data = 3;
    if (cool.LNK_AddNode(data) == 3) {
        cout << data << " added\n";
    }
    cool.LNK_PrintList(&cout);

    data = 3;
    if (cool.LNK_Enqueue(data) == 4) {
        cout << data << " enqueued\n";
    }
    cool.LNK_PrintList(&cout);

    int	key = 2;
    data = 7;
    if (cool.LNK_ModifyNode(key, data))
        cout << key << " changed to " << data << endl;
    cool.LNK_PrintList(&cout);

    key = 7;
    if (cool.LNK_RemoveNode(key) == 3) {
        cout << key << " deleted\n";
    }
    cool.LNK_PrintList(&cout);

    data = 12;
    if (cool.LNK_AddNode(data) == 4) {
        cout << data << " added\n";
    }
    cool.LNK_PrintList(&cout);

    data = 8;
    if (cool.LNK_AddNode(data) == 5) {
        cout << data << " added\n";
    }
    cool.LNK_PrintList(&cout);

    data = 0;
    if (cool.LNK_AddNode(data) == 6) {
        cout << data << " added\n";
    }
    cool.LNK_PrintList(&cout);

    data = -1;
    if (cool.LNK_AddNode(data) == 7) {
        cout << data << " added\n";
    }
    cool.LNK_PrintList(&cout);

    cool.LNK_InvertList();
    cool.LNK_PrintList(&cout);

    if ((data = cool.LNK_Dequeue()) != NULL) {
        cout << data << " deleted\n";
    }
    cool.LNK_PrintList(&cout);

    if ((data = cool.LNK_Dequeue()) != NULL)
    {
        cout << data << " deleted\n";
    }
    else
    {
        return -1;
    }
    cool.LNK_PrintList(&cout);

    data = 11;
    if (cool.LNK_PushStack(data) == 6) {
        cout << data << " added\n";
    }
    cool.LNK_PrintList(&cout);

    key = 8;
    if (cool.LNK_RemoveNode(key) == 5) {
        cout << key << " deleted\n";
    }

    cool.LNK_PrintList(&cout);

    cool.LNK_DeleteList();
    cool.LNK_PrintList(&cout);

    data = 9;
    if (cool.LNK_AddNode(data) == 1) {
        cout << data << " added\n";
    }
    cool.LNK_PrintList(&cout);

    data = 8;
    if (cool.LNK_AddNode(data) == 2) {
        cout << data << " added\n";
    }
    cool.LNK_PrintList(&cout);

    data = 0;
    if (cool.LNK_AddNode(data) == 3) {
        cout << data << " added\n";
    }
    cool.LNK_PrintList(&cout);

    cool.LNK_InvertList();

    cool.LNK_PrintList(&cout);

    return 0;
}

const int  kMaxTerms = 1100;
int CoolTests::SortingMethods(void)
{
    CoolLib::CCoolLib cool;
    ofstream fout;

    int integerList1[kMaxTerms];
    int integerList2[kMaxTerms];
    int *pIntLine = new int[kMaxTerms];
    ifstream fin;
    fin.open("10000.txt");
    if (fin.fail()) {
        cout << "Input file openning failed" << endl;
        exit(EXIT_FAILURE);
    }

    cool.IOM_Create();
    int numTerms = 0;
    int tmp;
    while (tmp = cool.IOM_GetIntegerListFromStream(&fin, &pIntLine, kMaxTerms)) {
        for (int i = 0; i<tmp; i++) {
            integerList1[numTerms + i] = pIntLine[i];
            integerList2[numTerms + i] = pIntLine[i];
        }
        numTerms += tmp;
    }
    fin.close();

    fout.open("SortedList1.txt");
    if (fout.fail()) {
        cout << "Output file opening failed" << endl;
        exit(EXIT_FAILURE);
    }
    cool.SRT_Create();
    cool.Timer.TimerOn("MaxHeapSort");
    cool.SRT_MaxHeapSort(integerList1, numTerms);
    cool.Timer.TimerOff();
    for (int i = 0; i<numTerms; i++) {
        fout << integerList1[i] << endl;
    }
    fout.close();

    fout.open("SortedList2.txt");
    if (fout.fail()) {
        cout << "Output file opening failed" << endl;
        exit(EXIT_FAILURE);
    }
    cool.Timer.TimerOn("MinHeapSort");
    cool.SRT_MinHeapSort(integerList2, numTerms);
    cool.Timer.TimerOff();
    for (int i = 0; i<numTerms; i++) {
        fout << integerList2[i] << endl;
    }
    fout.close();
    delete[] pIntLine;
    pIntLine = NULL;
    return 0;
}

// Test Stack and Queue arrays.
int CoolTests::StackNQueue(void)
{
    CoolLib::CCoolLib stk;
    CoolLib::CCoolLib qua;

    int* pData;
    uint16_t done = FALSE;

    int sel;
    // Interface.
    cout << "Program \"Stack&Queue test\" has started...\n";
    while (1) {
        cout << "\n1 Stack test\n";
        cout << "2 Queue test\n";
        cout << "Choose one that you want to run.(Others for EXIT)\n>";
        cin >> sel;

        switch (sel) {
        case 1:	// Stack test.
            while (!done) {
                pData = new int;
                cout << "Enter a number: 9 to stop: " << endl;
                cin >> *pData;
                if ((*pData == 9) || stk.ARR_IsFull())
                    done = TRUE;
                else
                    stk.ARR_PushStack(pData);
            }
            done = FALSE;
            cout << "\n\n The list of numbers :" << endl;
            while (!stk.ARR_IsEmpty()) {
                pData = stk.ARR_PopStack();
                cout << *pData << endl;
                delete pData;
                pData = NULL;
            }
            break;
        case 2:	// Queue test.
            while (!done) {
                pData = new int;
                cout << "Enter a number: -1 to dequeue, 99 to stop: " << endl;
                cin >> *pData;
                if ((*pData == 99) || (*pData < (0 - CoolLib::kMaxLineLen)) || (*pData>CoolLib::kMaxIntegerRange))
                    done = TRUE;
                else if (*pData == -1) {// Check point - must typecast!!
                    if ((pData = qua.ARR_Dequeue()) == NULL)
                        done = TRUE;	//	Check Point! - detect no more items.
                    else
                        cout << *pData << " dequeued!!" << endl;
                }
                else
                    done = !qua.ARR_Enqueue(pData);
            }
            done = FALSE;
            cout << "\n\n The list of numbers :" << endl;
            while (!qua.ARR_IsEmpty()) {
                pData = qua.ARR_Dequeue();
                cout << *pData << endl;
                delete pData;
                pData = NULL;
            }
            break;
        default:
            return 0;
        }
        sel = 0;
    }//while

    return 0;
}


// Test for IO Methods.
void CoolTests::ReadStringsFromFile(void)
{
	CoolLib::CCoolLib cool;
	ifstream fin;

	fin.open("training_sample.txt");
	if (fin.fail()) {
		cout << "Input file openning failed" << endl;
		exit(EXIT_FAILURE);
	}

	cool.IOM_Create();
	string *pstrList = new string[kMaxTerms];
	char* pData = NULL;
	int numStr;
	while ((numStr = cool.IOM_GetStringListFromStream(&fin, &pstrList, 100)) > 0) {
		for (int i = 0; i<numStr; i++) {
			cout << setw(1) << "[";
			cout << setw(10) << pstrList[i];
			cout.setf(ios::left);
			cout << setw(2) << "]";
			cout.unsetf(ios::left);
		}
		cout << endl;
	}
	delete[] pstrList;
	pstrList = NULL;
	fin.close();
}

void CoolTests::ThrdBSTTest(void)
{
	CoolLib::CCoolLib cool;
	cool.BST_Create();
	cool.BST_InorderTraverse(&cout, 0);

	int* data = new int;
	*data = 5;
	if (cool.BST_AddNode(data) == 0) {
		cout << "i" << *data << " : ";
		data = new int;
	}
	cool.BST_LevelOrderTraverse(&cout, 1);

	*data = 3;
	if (cool.BST_AddNode(data) == 0) {
		cout << "i" << *data << " : ";
		data = new int;
	}
	cool.BST_LevelOrderTraverse(&cout, 1);

	*data = 6;
	if (cool.BST_AddNode(data) == 0) {
		cout << "i" << *data << " : ";
		data = new int;
	}
	cool.BST_LevelOrderTraverse(&cout, 1);

	*data = 4;
	if (cool.BST_AddNode(data) == 0) {
		cout << "i" << *data << " : ";
		data = new int;
	}
	cool.BST_LevelOrderTraverse(&cout, 1);

	*data = 7;
	if (cool.BST_AddNode(data) == 0) {
		cout << "i" << *data << " : ";
		data = new int;
	}
	cool.BST_LevelOrderTraverse(&cout, 1);

	cool.BST_IterInorderTraverse(&cout, 0);
	cool.BST_PrintTree(&cout);

	int key = 5;
	cout << "s" << key << " : ";
	if (cool.BSTsearch_dataNode(key))
		cout << "Exist\n";
	else
		cout << "Not exist\n";

	*data = 9;
	if (cool.BST_AddNode(data) == 0) {
		cout << "i" << *data << " : ";
		data = new int;
	}
	cool.BST_LevelOrderTraverse(&cout, 1);
	cool.BST_PrintTree(&cout);

	key = 6;
	if (cool.BST_RemoveNode(key) == 0) {
		cout << "d" << key << " : ";
	}
	cool.BST_LevelOrderTraverse(&cout, 1);

	*data = 1;
	if (cool.BST_AddNode(data) == 0) {
		cout << "i" << *data << " : ";
		data = new int;
	}
	cool.BST_LevelOrderTraverse(&cout, 1);

	cool.BST_PrintTree(&cout);

}

