

/************************************************************************************
	Implementation of Binary Search Tree Query Functions
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "bst.h"
#include <stack.h>
#include <queue.h>




#define maxu(a, b) ((a) > (b) ? (a) : (b))








BNode * bst_root(const BisTree *pTree) {
	
	return (pTree == 0 ? 0 : pTree->root);
}



BNode * bst_parent(const BNode *pNode) {
	
	return (pNode == 0 ? 0 : pNode->parent);
}



BNode * bst_leftChild(const BNode *pNode) {
	
	return (pNode == 0 ? 0 : pNode->leftChild);
}



BNode * bst_rightChild(const BNode *pNode) {
	
	return (pNode == 0 ? 0 : pNode->rightChild);
}



BNode * bst_sibling(const BNode *pNode) {
	
	BNode *sibling;
	BNode *parent;
	
	parent = bst_parent(pNode);
	if (parent == 0) {
		sibling = 0;
	}
	else {
		if (pNode == bst_leftChild(parent)) {
			sibling = bst_rightChild(parent);
		}
		else if (pNode == bst_rightChild(parent)) {
			sibling = bst_leftChild(parent);
		}
	}
	
	return sibling;
}



int bst_isExternal(const BNode *pNode) {
	
	unsigned int left, right;
	
	left = (unsigned int) bst_leftChild(pNode);
	right = (unsigned int) bst_rightChild(pNode);
	
	if ((left | right) == 0) {
	// if ((left == 0) & (right == 0)) {
		return 1;
	}
	else {
		return 0;
	}
}



int bst_isInternal(const BNode *pNode) {
	
	unsigned int left, right;
	
	left = (unsigned int) bst_leftChild(pNode);
	right = (unsigned int) bst_rightChild(pNode);
	
	if ((left | right) != 0) {
	// if ((left != 0) | (right != 0)) {
		return 1;
	}
	else {
		return 0;
	}
}



int bst_isRoot(const BisTree *pTree, const BNode *pNode) {
	
	int retVal;
	
	retVal = bst_root(pTree) == pNode ? 1 : 0;
	return retVal;
}



unsigned int bst_depth(const BisTree *pTree, const BNode *pNode) {
	
	register unsigned int iDepth;
	register const BNode *pCurrent;
	
	iDepth = 0;
	pCurrent = pNode;
	
	while (pCurrent != bst_root(pTree)) {
		pCurrent = bst_parent(pCurrent);
		iDepth = iDepth + 1;
	}
	
	return iDepth;
}



unsigned int bst_height(const BisTree *pTree, const BNode *pNode) {
	
	int isExternal;
	Queue qPostorder;
	register unsigned int iCount;
	unsigned int nExternal;
	unsigned int heightR, heightL, heightN;
	const BNode *pCurrent;
	unsigned int *pTmpHeight;
	
	iCount = 0;
	pCurrent = 0;
	pTmpHeight = 0;
	nExternal = bst_size(pTree) + 1;
	pTmpHeight = (unsigned int *) malloc(sizeof(unsigned int) * nExternal);
	
	if (pTmpHeight == 0)
		return 0;
	
	
	/* Initialize the Queue and store PostOrder nodes on it */
	queue_init(&qPostorder, 0);
	bst_postOrder(pTree, (BNode *) pNode, &qPostorder);
	
	while (queue_size(&qPostorder) > 0) {
		
		queue_dequeue(&qPostorder, (void **) &pCurrent);
		isExternal = bst_isExternal(pCurrent);
		
		if (isExternal == 1) {
			*(pTmpHeight + iCount) = 0;
			iCount = iCount + 1;
		}
		else {
			iCount = iCount - 1;
			heightR = *(pTmpHeight + iCount);
			
			iCount = iCount - 1;
			heightL = *(pTmpHeight + iCount);
			
			heightN = 1 + maxu(heightL, heightR);
			*(pTmpHeight + iCount) = heightN;
			iCount = iCount + 1;
		}
	}
	
	heightN = *(pTmpHeight + iCount - 1);
	queue_destroy(&qPostorder);
	free((void *) pTmpHeight);
	
	return heightN;
}

