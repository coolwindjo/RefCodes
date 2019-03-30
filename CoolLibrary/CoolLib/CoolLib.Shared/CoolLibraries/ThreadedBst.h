#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

template <class T>
class CThreadedBst
{
public:
	CThreadedBst(void);
	CThreadedBst(uint16_t bIsMinimizeHeight);
	~CThreadedBst(void);

    virtual void PrintTree(ostream* fout);
    virtual int32_t Compare(const T& arg1, const T& arg2);
    // Check whether the list is empty or not.
	uint16_t IsEmpty(void);

	// Adds a node containing data to the tree.
	int32_t AddNode(T* pDataIn);
	// Removes data from the tree.
	int32_t RemoveNode(const T& tKeyData);
	int32_t CopyWholeTree(CThreadedBst* poCopiedTree);
	// Do operation with each node while in-order traversing around the whole tree.
	void InorderTraverse(ostream* fout, int32_t operation);
	// Do operation with each node while iterative in-order traversal..
	void IterInorderTraverse(ostream* fout, int32_t operation);
	// Do operation with each node while level-order traversing around the whole tree.
	void LevelOrderTraverse(ostream* fout, int32_t operation);
	// Return existence value.
	uint16_t SearchNode(const T& tKeyData);
	// Define data comparison function.

protected:
    class BstNode
    {
    public:
        virtual bool operator<(const BstNode& rhs) const
        {
            if (this != &rhs) {
                return (*m_pData < *rhs.m_pData);
            }
            return false;
        }
        virtual bool operator>(const BstNode& rhs) const
        {
            if (this != &rhs) {
                return (*m_pData > *rhs.m_pData);
            }
            return false;
        }
        friend ostream& operator<<(ostream& os, const BstNode& rhs)
        {
            if (rhs.m_pData != NULL)
            {
                os << *rhs.m_pData;
            }
            return os;
        }
    private:
        friend class CThreadedBst;
        T*		m_pData;
        bool	m_bLeftThreadExists;
        bool	m_bRightThreadExists;
        BstNode* m_poLeftNode;
        BstNode* m_poRightNode;
    };
    // Insert the new data into a leaf node in the BST tree.
	uint16_t insert_data(BstNode* pParentNode, T* pDataIn); //
	// Searches BST and passes back address of the parent node. 
	// Return appropriate position for the data if the tree does not have it
	uint16_t search_data(const T& tKeyData, BstNode** ppParentNode);//
	// Deletes the target node from the tree and retrieve the pointer to data.
	uint16_t delete_node(BstNode* pTargetNode, T** ppDataOut); //
	// If key data is in the list, then retrives data pointer, otherwise, returns NULL.
	T* retrieve_item(const T& tKeyData);//
	// Copy the tree nodes from the given node as a root.
	int32_t _CopyTree(BstNode* tree, BstNode* copyTree);//
	// Insert rightNode as the right child of the pParentNode.
	uint16_t insert_to_right(BstNode* pParentNode, BstNode* rightNode);//
	// Insert leftNode as the left child of the pParentNode.
	uint16_t insert_to_left(BstNode* pParentNode, BstNode* leftNode);//
	// Retrieve the successor of the current node in inorder-traversal.
	BstNode* _RetrieveInorderSuccessor(BstNode* pCurrentNode);//
	// Do operation with each node while post-order traversing around the whole tree.
	void _PostOrderTraverse(ostream* fout, int32_t operation, BstNode* pCurrentNode,  int32_t tmpHeight);
	// Update the height of the tree.
	void _UpdateHeight(void);
	// Recursively swap the two left, right branches of the tree that rooted from given node.
	uint16_t _SwapTree(BstNode* pMiddleNode);//
	// Check equality between the two given trees and return the number of different nodes.
	int32_t _Equal(BstNode* first, BstNode* second);//
	// Make new node with the pDataIn.
	BstNode* _MakeNode(T* pDataIn);	//
	void _PrintTreeNode(BstNode* node, ostream* fout);
	// A function being carried on while traversing the tree.
	virtual void _DoSomething(ostream* fout, BstNode* node);//

private:
    // The root node of the whole tree.
    BstNode* m_poHeaderNode;
    // The number of nodes in the tree.
    int32_t m_nCount;
    // The number of levels in the tree.
    int32_t m_nHeight;
    // Intelligent insertion to minimize the height of the tree.
    uint16_t m_bIsMinimizeHeight;
    // Current position node for traverse.
    BstNode* m_poNodePos;

};
