

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



BNode * bst_parent(const BNode *v) {
	
	return (v == 0 ? 0 : v->parent);
}



BNode * bst_leftChild(const BNode *v) {
	
	return (v == 0 ? 0 : v->leftChild);
}



BNode * bst_rightChild(const BNode *v) {
	
	return (v == 0 ? 0 : v->rightChild);
}



BNode * bst_sibling(const BNode *v) {
	
	BNode *sibling;
	BNode *parent;
	
	parent = bst_parent(v);
	if (parent == 0) {
		sibling = 0;
	}
	else {
		if (v == bst_leftChild(parent)) {
			sibling = bst_rightChild(parent);
		}
		else if (v == bst_rightChild(parent)) {
			sibling = bst_leftChild(parent);
		}
	}
	
	return sibling;
}



int bst_isExternal(const BNode *v) {
	
	unsigned int left, right;
	
	left = (unsigned int) bst_leftChild(v);
	right = (unsigned int) bst_rightChild(v);
	
	if ((left | right) == 0) {
	// if ((left == 0) & (right == 0)) {
		return 1;
	}
	else {
		return 0;
	}
}



int bst_isInternal(const BNode *v) {
	
	unsigned int left, right;
	
	left = (unsigned int) bst_leftChild(v);
	right = (unsigned int) bst_rightChild(v);
	
	if ((left | right) != 0) {
	// if ((left != 0) | (right != 0)) {
		return 1;
	}
	else {
		return 0;
	}
}



int bst_isRoot(const BisTree *pTree, const BNode *v) {
	
	if (v == bst_root(pTree)) {
		return 1;
	}
	else {
		return 0;
	}
}



unsigned int bst_depth(const BisTree *pTree, const BNode *v) {
	
	register unsigned int iDepth;
	register const BNode *nodeCurrent;
	
	iDepth = 0;
	nodeCurrent = v;
	
	while (nodeCurrent != bst_root(pTree)) {
		nodeCurrent = bst_parent(nodeCurrent);
		iDepth = iDepth + 1;
	}
	
	return iDepth;
}



unsigned int bst_height(const BisTree *pTree, const BNode *node) {
	
	int isExternal;
	Queue qPostorder;
	register unsigned int iCount;
	unsigned int nExternal;
	unsigned int heightR, heightL, heightN;
	const BNode *pNode;
	unsigned int *pTmpHeight;
	
	iCount = 0;
	nExternal = bst_size(pTree) + 1;
	queue_init(&qPostorder, 0);
	bst_postOrder(pTree, (BNode *) node, &qPostorder);
	pTmpHeight = (unsigned int *) malloc(sizeof(unsigned int) * nExternal);
	
	while (queue_size(&qPostorder) > 0) {
		
		queue_dequeue(&qPostorder, (void **) &pNode);
		isExternal = bst_isExternal(pNode);
		
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

