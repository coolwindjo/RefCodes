#include <cstdlib>
#include <cmath>

#include "CoolLibraries\ThreadedBst.h"
#include "CoolLibraries\DynamicArray.h"

#define TRUE 1
#define FALSE 0

template <class T>
CThreadedBst<T>::CThreadedBst(void)
	: m_poNodePos(NULL)
	, m_nCount(0)
	, m_nHeight(0)
	, m_bIsMinimizeHeight(TRUE)
{
	m_poHeaderNode = _MakeNode(NULL);
	m_poHeaderNode->m_bLeftThreadExists = TRUE;
	m_poHeaderNode->m_bRightThreadExists = FALSE;
}

template <class T>
CThreadedBst<T>::CThreadedBst(uint16_t minimizeHeight)
	: m_poNodePos(NULL)
	, m_nCount(0)
	, m_nHeight(0)
{
	m_bIsMinimizeHeight = minimizeHeight;
	m_poHeaderNode = _MakeNode(NULL);
	m_poHeaderNode->m_bLeftThreadExists = TRUE;
	m_poHeaderNode->m_bRightThreadExists = FALSE;
}

template <class T>
CThreadedBst<T>::~CThreadedBst(void)
{
	InorderTraverse(NULL, -1);
	delete m_poHeaderNode;
	m_poHeaderNode = NULL;
}

// Check whether the list is empty or not.
template <class T>
uint16_t CThreadedBst<T>::IsEmpty(void)
{
	return (m_nCount == 0);
}

// Adds a node containing data to the tree.
template <class T>
int32_t CThreadedBst<T>::AddNode(T* pDataIn)
{
	BstNode* pParentNode = NULL;

	if (search_data(*pDataIn, &pParentNode) == TRUE)
		return 1;

	if (insert_data(pParentNode, pDataIn) == FALSE)
		return -1;
	return 0;
}

// Removes data from the tree.
template <class T>
int32_t CThreadedBst<T>::RemoveNode(const T& tKeyData)
{
	T* pDataOut = NULL;
	uint16_t found, success = FALSE;
	BstNode* pParentNode = NULL;
	if (found = search_data(tKeyData, &pParentNode)) {
		if (pParentNode == NULL)	// Removing root node;
			success = delete_node(m_poHeaderNode->m_poLeftNode, &pDataOut);
		else {
			if (Compare(tKeyData, *pParentNode->m_pData) < 0)
				success = delete_node(pParentNode->m_poLeftNode, &pDataOut);
			else if (Compare(tKeyData, *pParentNode->m_pData) > 0)
				success = delete_node(pParentNode->m_poRightNode, &pDataOut);
			else {
				success = delete_node(pParentNode, &pDataOut);
			}
		}
	}
	if (found) {
		if (success)
			return 0;
		else
			return -1;
	}
	else
		return 1;
}

template <class T>
int32_t CThreadedBst<T>::CopyWholeTree(CThreadedBst* poCopiedTree)
{
	return 0;
}

// Do operation with each node while in-order traversing around the whole tree.
template <class T>
void CThreadedBst<T>::InorderTraverse(ostream* fout, int32_t operation)
{
	BstNode* preTmp = NULL;
	BstNode* tmp = m_poHeaderNode;
	while (TRUE) {
		preTmp = tmp;
		// Get next node.
		tmp = _RetrieveInorderSuccessor(tmp);
		// If it's header, then finish.
		if (tmp == m_poHeaderNode) {	// Finish!
			if (operation == 0)
				*fout << endl;
			break;
		}
		// Visiting node.
		if (operation == 0)	// Normal printing.
			*fout << setw(5) << *tmp->m_pData;
		else if (operation == -1) {	// Delete the node.
			T* itemPtr = NULL;
			if (preTmp != m_poHeaderNode) {
				delete_node(preTmp, &itemPtr);
				delete itemPtr;
				itemPtr = NULL;
			}
		}
		else	// Do something els.
			_DoSomething(fout, tmp);
	}
}

// Do operation with each node while iterative in-order traversal..
template <class T>
void CThreadedBst<T>::IterInorderTraverse(ostream* fout, int32_t operation)
{
	CDynamicArray<BstNode> stack;
	BstNode* node = m_poHeaderNode->m_poLeftNode;
	if (node == NULL) {
		cerr << "Error: Invalid root node\n";
		return;
	}
	while (TRUE) {
		while (node != NULL) {
			stack.PushStack(node);
			if (node->m_bLeftThreadExists == FALSE)
				node = node->m_poLeftNode;
			else
				break;
		}
		if ((node = stack.PopStack()) == NULL) {
			*fout << endl;
			break;
		}
		*fout << setw(5) << *node->m_pData;
		if (node->m_bRightThreadExists == FALSE)
			node = node->m_poRightNode;
		else
			node = NULL;
	}
}

// Do operation with each node while level-order traversing around the whole tree.
template <class T>
void CThreadedBst<T>::LevelOrderTraverse(ostream* fout, int32_t operation)
{
	CDynamicArray<BstNode> queue;
	BstNode* tmp = m_poHeaderNode->m_poLeftNode;
	if (tmp == NULL) {
		cerr << "Error: Invalid root node\n";
		return;
	}
	// Make null & invalid node. Make it differ dependent on the <class T>.
	T NULL_DATA = 0, INVALID_DATA = -1;
	BstNode* emptyNode = NULL;
	_UpdateHeight();
	// Compute the number of nodes to print out.
	// Maximum number of nodes in a BST = 2^(height) -1
	int32_t maxNumNode = static_cast<int>(pow(2.0, static_cast<double>(m_nHeight))) - 1;
	queue.Enqueue(tmp);
	for (int32_t i = 0; i<maxNumNode; i++) {
		tmp = queue.Dequeue();
		if (tmp != NULL) {
			if (operation == 0) {	// Normal printing.
				*fout << setw(5) << *tmp->m_pData;
			}
			else if (operation == 1) { // Print out as a complete BST form.
				if (*tmp->m_pData == static_cast<T>(INVALID_DATA))
					*fout << setw(5) << "-1";
				else {
					*fout << setw(5) << *tmp->m_pData;
				}
			}
			else	// Do something else.
				_DoSomething(fout, tmp);

			// If there is left child or should print out as a complete BST form,
			if ((operation != 0) || ((tmp->m_poLeftNode != m_poHeaderNode) && (tmp->m_bLeftThreadExists == FALSE))) {
				if ((operation == 1) && (*tmp->m_pData == static_cast<T>(INVALID_DATA))) {
					tmp = _MakeNode(tmp->m_pData);	// Make node of '-1'.
					queue.Enqueue(tmp);
				}
				else if ((operation == 1) && (tmp->m_bLeftThreadExists == TRUE)) {
					emptyNode = _MakeNode(&NULL_DATA);	// Make node of '0'.
					emptyNode->m_poLeftNode = _MakeNode(&INVALID_DATA);	// Make node of '-1'.
					emptyNode->m_poRightNode = _MakeNode(&INVALID_DATA);	// Make node of '-1'.
					queue.Enqueue(emptyNode);
				}
				else // Just enqueue left child for normal printing.
					queue.Enqueue(tmp->m_poLeftNode);
			}
			// If there is right child or should print out as a complete BST form, 
			if ((operation != 0) || ((tmp->m_poRightNode != m_poHeaderNode) && (tmp->m_bRightThreadExists == FALSE))) {
				if ((operation == 1) && (*tmp->m_pData == static_cast<T>(INVALID_DATA))) {
					tmp = _MakeNode(tmp->m_pData);	// Make node of '-1'.
					queue.Enqueue(tmp);
				}
				else if ((operation == 1) && (tmp->m_bRightThreadExists == TRUE)) {
					emptyNode = _MakeNode(&NULL_DATA);	// Make node of '0'.
					emptyNode->m_poLeftNode = _MakeNode(&INVALID_DATA);	// Make node of '-1'.
					emptyNode->m_poRightNode = _MakeNode(&INVALID_DATA);	// Make node of '-1'.
					queue.Enqueue(emptyNode);
				}
				else // Just enqueue right child for normal printing.
					queue.Enqueue(tmp->m_poRightNode);
			}
		} // if (tmp!=NULL) {
		else
			break;
	}
	*fout << endl;
}

// Return existence value.
template <class T>
uint16_t CThreadedBst<T>::SearchNode(const T& tKeyData)
{
	BstNode* tmp = NULL;
	return search_data(tKeyData, &tmp);
}

// Define data comparison function.
template <class T>
int32_t CThreadedBst<T>::Compare(const T& arg1, const T& arg2)
{
	int32_t result = 0;
	if (arg1 < arg2)
		result = -1;
	else if (arg1 > arg2)
		result = 1;
	return result;
}

template <class T>
void CThreadedBst<T>::PrintTree(ostream* fout)
{
	_UpdateHeight();
	if (m_poHeaderNode->m_bLeftThreadExists == FALSE)
		_PrintTreeNode(m_poHeaderNode->m_poLeftNode, fout);
	else
		cerr << "Error: Empty tree.\n";
}


// Insert the new data into a leaf node in the BST tree.
template <class T>
uint16_t CThreadedBst<T>::insert_data(BstNode* pParentNode, T* pDataIn)
{
	uint16_t result = FALSE;
	if (pDataIn == NULL) {
		return FALSE;
	}
	// Memory allocation and initialization for a newNode.
	BstNode* newNode = _MakeNode(pDataIn);

	if (pParentNode == NULL) { // Adding to empty tree.
		if (!IsEmpty()) {
			cerr << "Error: Invalid parent node.";
			return FALSE;
		}
		m_nHeight = 1;
		result = insert_to_left(m_poHeaderNode, newNode);
	}
	else {	// Adding to any other tree.
		if (Compare(*pParentNode->m_pData, *newNode->m_pData) < 0)
			result = insert_to_right(pParentNode, newNode);
		else
			result = insert_to_left(pParentNode, newNode);
	}
	m_nCount++;
    
    return result;
}

// Searches BST and passes back address of the parent node. 
// Return appropriate position for the data if the tree does not have it
template <class T>
uint16_t CThreadedBst<T>::search_data(const T& tKeyData, BstNode** ppParentNode)
{
	int32_t result = 1;
	//*ppParentNode = NULL;

	if (IsEmpty())
		return FALSE;

	BstNode* tmp = m_poHeaderNode->m_poLeftNode;
	do {
		if ((result = Compare(tKeyData, *tmp->m_pData)) == 0)
			break;	// Key data has been found.
		else if ((result = Compare(tKeyData, *tmp->m_pData)) < 0) {
			if (tmp->m_bLeftThreadExists == TRUE)
				if ((tmp->m_poLeftNode != m_poHeaderNode)
					&& ((*ppParentNode)->m_bLeftThreadExists == FALSE)
					&& ((*ppParentNode)->m_bRightThreadExists == TRUE)
					&& m_bIsMinimizeHeight) {
					// If parent's left node is not available,
					tmp = tmp->m_poLeftNode;
					break; // Back tracking to proper parent node;
				}
				else
					break;	// If left node is not a child, halt!
			else {
				*ppParentNode = tmp; // Store address of the parent of the target.
				tmp = tmp->m_poLeftNode;
			}
		}
		else {	// Key data is bigger than the data of the current node.
			if (tmp->m_bRightThreadExists == TRUE) {
				if ((tmp->m_poRightNode != m_poHeaderNode)
					&& ((*ppParentNode)->m_bLeftThreadExists == TRUE)
					&& ((*ppParentNode)->m_bRightThreadExists == FALSE)
					&& m_bIsMinimizeHeight) {
					// If parent's right node is not available,
					tmp = tmp->m_poRightNode;
					break; // Back tracking to proper parent node;
				}
				else
					break; // If right node is not a child, halt!
			}
			else {
				*ppParentNode = tmp; // Store address of the parent of the target.
				tmp = tmp->m_poRightNode;
			}
		}
	} while (tmp != m_poHeaderNode);
	if (result == 0)
		return TRUE;
	else {
		*ppParentNode = tmp; // Store address of the parent of proper position.
		return FALSE;
	}
}

// Deletes data from the tree and retrieve the pointer to data.
template <class T>
uint16_t CThreadedBst<T>::delete_node(BstNode* pTargetNode, T** ppDataOut)
{
	if (!IsEmpty()) {
		if (pTargetNode != NULL) {
			*ppDataOut = pTargetNode->m_pData;
			BstNode* pParentNode = NULL;
			if (search_data(*pTargetNode->m_pData, &pParentNode)) {
				if (pParentNode == NULL) { // Deleting root node.
					if ((pTargetNode->m_bLeftThreadExists == TRUE) && (pTargetNode->m_bRightThreadExists == TRUE)) {
						// Leaf node deletion.
						m_poHeaderNode->m_poLeftNode = pTargetNode->m_poLeftNode;
						m_poHeaderNode->m_bLeftThreadExists = TRUE;
						delete pTargetNode;
						pTargetNode = NULL;
					} // if ((pTargetNode->m_bLeftThreadExists == TRUE) && (pTargetNode->m_bRightThreadExists == TRUE)) {
					else if ((pTargetNode->m_bLeftThreadExists == FALSE) && (pTargetNode->m_bRightThreadExists == FALSE)) {
						// Deletion of non-leaf node with two children.
						BstNode* preTmp = pTargetNode;
						BstNode* tmp = pTargetNode->m_poLeftNode;
						while (tmp->m_bRightThreadExists == FALSE) {	// Check whether tmp is a leaf node.
							preTmp = tmp;
							tmp = _RetrieveInorderSuccessor(tmp);
						}
						T itemTmp = *tmp->m_pData;
						T* itemPtr = NULL;
						delete_node(tmp, &itemPtr);
						delete itemPtr;
						itemPtr = NULL;
						*pTargetNode->m_pData = itemTmp;
					}
					else { // Deletion of non-leaf node with one child.
						if (pTargetNode->m_bLeftThreadExists == FALSE) {	// If pTargetNode has a left child,
							m_poHeaderNode->m_poLeftNode = pTargetNode->m_poLeftNode;	// Make it pParentNode's left child.
							m_poHeaderNode->m_bLeftThreadExists = FALSE;
						}
						else { // Otherwise,
							m_poHeaderNode->m_poLeftNode = pTargetNode->m_poRightNode;
							m_poHeaderNode->m_bLeftThreadExists = FALSE;
						}
						delete pTargetNode;
						pTargetNode = NULL;
					}
				} // if (pParentNode == NULL) { // Deleting root node.
				else { // Deleting any other nodes.
					if ((pTargetNode->m_bLeftThreadExists == TRUE) && (pTargetNode->m_bRightThreadExists == TRUE)) {
						// Leaf node deletion.
						if (pTargetNode == pParentNode->m_poLeftNode) {
							pParentNode->m_poLeftNode = pTargetNode->m_poLeftNode;
							pParentNode->m_bLeftThreadExists = TRUE;
						}
						else if (pTargetNode == pParentNode->m_poRightNode) {
							pParentNode->m_poRightNode = pTargetNode->m_poRightNode;
							pParentNode->m_bRightThreadExists = TRUE;
						}
						else {
							cerr << "Error: Invalid parent node.\n";
							return FALSE;
						}
						delete pTargetNode;
						pTargetNode = NULL;
					} // if ((pTargetNode->m_bLeftThreadExists == TRUE) && (pTargetNode->m_bRightThreadExists == TRUE)) {
					else if ((pTargetNode->m_bLeftThreadExists == FALSE) && (pTargetNode->m_bRightThreadExists == FALSE)) {
						// Deletion of non-leaf node with two children.
						BstNode* preTmp = pTargetNode;
						BstNode* tmp = pTargetNode->m_poLeftNode;
						while (tmp->m_bRightThreadExists == FALSE) {	// Check whether tmp is a leaf node.
							preTmp = tmp;
							tmp = _RetrieveInorderSuccessor(tmp);
						}
						T itemTmp = *tmp->m_pData;
						T* itemPtr = NULL;
						delete_node(tmp, &itemPtr);
						m_nCount++;
						delete itemPtr;
						itemPtr = NULL;
						*pTargetNode->m_pData = itemTmp;
					}
					else { // Deletion of non-leaf node with one child.
						if (pTargetNode == pParentNode->m_poLeftNode) {
							if (pTargetNode->m_bLeftThreadExists == FALSE) {	// If pTargetNode has a left child,
								BstNode* tmp = pTargetNode->m_poLeftNode;
								if (tmp->m_poRightNode == pTargetNode)
									tmp->m_poRightNode = pTargetNode->m_poRightNode;
								// Make it pParentNode's left child.
								pParentNode->m_poLeftNode = pTargetNode->m_poLeftNode;
								pParentNode->m_bLeftThreadExists = FALSE;
							}
							else { // Otherwise, a right child
								BstNode* tmp = pTargetNode->m_poRightNode;
								if (tmp->m_poLeftNode == pTargetNode)
									tmp->m_poLeftNode = pTargetNode->m_poLeftNode;
								// Make it pParentNode's left child.
								pParentNode->m_poLeftNode = tmp;
								pParentNode->m_bLeftThreadExists = FALSE;
							}
						}
						else if (pTargetNode == pParentNode->m_poRightNode) {
							if (pTargetNode->m_bLeftThreadExists == FALSE) {	// If pTargetNode has a left child,
								BstNode* tmp = pTargetNode->m_poLeftNode;
								if (tmp->m_poRightNode == pTargetNode)
									tmp->m_poRightNode = pTargetNode->m_poRightNode;
								// Make it pParentNode's left child.
								pParentNode->m_poRightNode = pTargetNode->m_poLeftNode;
								pParentNode->m_bLeftThreadExists = FALSE;
							}
							else { // Otherwise, a right child
								BstNode* tmp = pTargetNode->m_poRightNode;
								if (tmp->m_poLeftNode == pTargetNode)
									tmp->m_poLeftNode = pTargetNode->m_poLeftNode;
								// Make it pParentNode's left child.
								pParentNode->m_poRightNode = pTargetNode->m_poRightNode;
								pParentNode->m_bRightThreadExists = FALSE;
							}
						}
						else {
							cerr << "Error: Invalid parent node.\n";
							return FALSE;
						}
						delete pTargetNode;
						pTargetNode = NULL;
					}
				} // else { // Deleting any other nodes.
				m_nCount--;
				return TRUE;
			} // if (search_data( &pParentNode, pTargetNode->m_pData )) {
		} // if (pTargetNode != NULL) {
		cerr << "Error: Invalid target.\n";
	}
	else
		cerr << "Error: The List is empty.\n";
	return FALSE;
}

// If key data is in the list, then retrives data pointer, otherwise, returns NULL.
template <class T>
T* CThreadedBst<T>::retrieve_item(const T& tKeyData)
{
	T* pDataOut = NULL;
	BstNode* pParentNode = NULL;
	if (search_data(tKeyData, &pParentNode)) {
		if (pParentNode == NULL) // Empty tree.
			pDataOut = NULL;
		else {
			if (Compare(*pParentNode->m_pData, tKeyData) < 0)
				pDataOut = pParentNode->m_poRightNode->m_pData;
			else
				pDataOut = pParentNode->m_poLeftNode->m_pData;
		}
	}
	return pDataOut;
}

// Copy the tree nodes from the given node as a root.
template <class T>
int32_t CThreadedBst<T>::_CopyTree(BstNode* tree, BstNode* copyTree)
{
	int32_t count = 0;
	BstNode* tmp = NULL;
	if (tree != NULL) {
		tmp = new BstNode;
		count += _CopyTree(tree->m_poLeftNode, tmp->m_poLeftNode);
		count += _CopyTree(tree->m_poRightNode, tmp->m_poRightNode);
		*tmp->m_pData = *tree->m_pData;
		return ++count;
	}
	else
		return 0;
}

// Insert rightNode as the right child of the pParentNode.
template <class T>
uint16_t CThreadedBst<T>::insert_to_right(BstNode* pParentNode, BstNode* rightNode)
{
	if ((pParentNode == NULL) || (rightNode == NULL))
		return FALSE;
	else {
		// Copy the right child or thread of pParentNode
		// to the right child or thread of rightNode.
		rightNode->m_poRightNode = pParentNode->m_poRightNode;
		rightNode->m_bRightThreadExists = pParentNode->m_bRightThreadExists;
		// Assign the predecessor of rightNode with pParentNode.
		rightNode->m_poLeftNode = pParentNode;
		rightNode->m_bLeftThreadExists = TRUE;
		// Assign the right child of pParentNode with rightNode.
		pParentNode->m_poRightNode = rightNode;
		pParentNode->m_bRightThreadExists = FALSE;
		// Assign the predecessor of the successor of rightNode with rightNode.
		BstNode* tmp = NULL;
		if (rightNode->m_bRightThreadExists == FALSE) {
			tmp = _RetrieveInorderSuccessor(rightNode);
			tmp->m_poLeftNode = rightNode;
		}
		return TRUE;
	}
}

// Insert leftNode as the left child of the pParentNode.
template <class T>
uint16_t CThreadedBst<T>::insert_to_left(BstNode* pParentNode, BstNode* leftNode)
{
	if ((pParentNode == NULL) || (leftNode == NULL))
		return FALSE;
	else {
		// Copy the left child or thread of pParentNode
		// to the left child or thread of leftNode.
		leftNode->m_poLeftNode = pParentNode->m_poLeftNode;
		leftNode->m_bLeftThreadExists = pParentNode->m_bLeftThreadExists;
		// Assign the predecessor of leftNode with pParentNode.
		leftNode->m_poRightNode = pParentNode;
		leftNode->m_bRightThreadExists = TRUE;
		// Assign the left child of pParentNode with leftNode.
		pParentNode->m_poLeftNode = leftNode;
		pParentNode->m_bLeftThreadExists = FALSE;
		// Assign the predecessor of the successor of leftNode with leftNode.
		BstNode* tmp = NULL;
		if (leftNode->m_bLeftThreadExists == FALSE) {	// If parent has a left child,
			tmp = leftNode->m_poLeftNode;
			while (_RetrieveInorderSuccessor(tmp) != pParentNode)
				tmp = _RetrieveInorderSuccessor(tmp);
			tmp->m_poRightNode = leftNode;
		}
		return TRUE;
	}
}

// Retrieve the successor of the current node in inorder-traversal.
template <class T>
typename CThreadedBst<T>::BstNode* CThreadedBst<T>::_RetrieveInorderSuccessor(BstNode* pCurrentNode)
{
	BstNode* tmp = NULL;
	tmp = pCurrentNode->m_poRightNode;
	if (pCurrentNode->m_bRightThreadExists == FALSE)	// If current node has a right child node,
		while (tmp->m_bLeftThreadExists == FALSE)
			tmp = tmp->m_poLeftNode;
	return tmp;
}

// Do operation with each node while post-order traversing around the whole tree.
template <class T>
void CThreadedBst<T>::_PostOrderTraverse(ostream* fout, int32_t operation,
	BstNode* pCurrentNode, int32_t tmpHeight)
{
	if (pCurrentNode != NULL) {
		if (m_nHeight < tmpHeight)
			m_nHeight = tmpHeight;
		if (pCurrentNode->m_bLeftThreadExists == FALSE)
			_PostOrderTraverse(fout, operation, pCurrentNode->m_poLeftNode, ++tmpHeight);
		if (pCurrentNode->m_bRightThreadExists == FALSE) {
			if (pCurrentNode->m_bLeftThreadExists == FALSE) // If there is left child, then we already visited.
				tmpHeight--; // Therefore, we ought to reset the current height.
			_PostOrderTraverse(fout, operation, pCurrentNode->m_poRightNode, ++tmpHeight);
		}
		if (fout != NULL)
			*fout << *pCurrentNode->m_pData << " ";
		tmpHeight--;
	}
}

// Update the height of the tree.
template <class T>
void CThreadedBst<T>::_UpdateHeight(void)
{
	if (!IsEmpty()) {
		int32_t tmpHeight = 0;
		_PostOrderTraverse(NULL, 0, m_poHeaderNode->m_poLeftNode, ++tmpHeight);
	}
}

// Recursively swap the two left, right branches of the tree that rooted from given node.
template <class T>
uint16_t CThreadedBst<T>::_SwapTree(BstNode* pMiddleNode)
{
	BstNode* tmp = NULL;
	if (pMiddleNode != NULL) {
		_SwapTree(pMiddleNode->m_poLeftNode);
		_SwapTree(pMiddleNode->m_poRightNode);
		tmp = pMiddleNode->m_poLeftNode;
		pMiddleNode->m_poLeftNode = pMiddleNode->m_poRightNode;
		pMiddleNode->m_poRightNode = tmp;
		return TRUE;
	}
	else
		return FALSE;
}

// Check equality between the two given trees and return the number of different nodes.
template <class T>
int32_t CThreadedBst<T>::_Equal(BstNode* first, BstNode* second)
{
	if ((first == NULL) && (second == NULL))
		return 0;
	else if ((first != NULL) && (second != NULL)) {
		int32_t count = 0;
		if (Compare(*first->m_pData, *second->m_pData) == 0)
			count++;
		count += _Equal(first->m_poLeftNode, second->m_poLeftNode);
		count += _Equal(first->m_poRightNode, second->m_poRightNode);
		return count;
	}
	else {
		return 1;
	}
}

// Make new node with the pDataIn.
template <class T>
typename CThreadedBst<T>::BstNode* CThreadedBst<T>::_MakeNode(T* pDataIn)
{
	BstNode* newNode = NULL;
	if ((newNode = new BstNode) == NULL) {
		cerr << "Error: Memory allocation.\n";
		exit(EXIT_FAILURE);
	}
	newNode->m_pData = pDataIn;
	newNode->m_poLeftNode = newNode;
	newNode->m_bLeftThreadExists = FALSE;
	newNode->m_poRightNode = newNode;
	newNode->m_bRightThreadExists = FALSE;
	return newNode;
}

template <class T>
void CThreadedBst<T>::_PrintTreeNode(BstNode* node, ostream* fout)
{
	if (node != NULL) {
		if (node->m_pData != NULL) {
			if ((node->m_bLeftThreadExists == TRUE) && (node->m_bRightThreadExists == TRUE)) {
				// If the node is leaf.
				*fout << "\t";
				*fout << setw(1) << "(";
				*fout << setw(1) << *node->m_pData;
				*fout << setw(1) << ")";
				*fout << endl;
			}
			else {
				*fout << setw(1) << "[";
				*fout << setw(1) << *node->m_pData;
				*fout << setw(1) << "]";
				*fout << endl;
				if (node->m_bRightThreadExists == FALSE) {
					*fout << "\t";
					_PrintTreeNode(node->m_poRightNode, fout);
				}
				if (node->m_bLeftThreadExists == FALSE) {
					*fout << "\t";
					_PrintTreeNode(node->m_poLeftNode, fout);
				}
				*fout << endl;
			}
		}
		else
			cerr << "Error: Empty Node\n";
	}
}

// A function being carried on while traversing the tree.
template <class T>
void CThreadedBst<T>::_DoSomething(ostream* fout, BstNode* pNode)
{
	*fout << *pNode->m_pData << endl;
}

template class CThreadedBst<int>;
template class CThreadedBst<float>;
