

/************************************************************************************
	Implementation of BST Query Functions
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
*************************************************************************************/






#include "bst.h"
#include <stack.h>
#include <queue.h>




#define maxu(a, b) ((a) > (b) ? (a) : (b))








unsigned int bst_size(const BST *tree) {
	
	return tree->size;
}



BNode * bst_root(const BST *tree) {
	
	return (tree == 0 ? 0 : tree->root);
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



int bst_isRoot(const BST *tree, const BNode *v) {
	
	if (v == bst_root(tree)) {
		return 1;
	}
	else {
		return 0;
	}
}



unsigned int bst_depth(const BST *tree, const BNode *v) {
	
	register unsigned int iDepth;
	register const BNode *nodeCurrent;
	
	iDepth = 0;
	nodeCurrent = v;
	
	while (nodeCurrent != bst_root(tree)) {
		nodeCurrent = bst_parent(nodeCurrent);
		iDepth = iDepth + 1;
	}
	
	return iDepth;
}



unsigned int bst_height(const BST *tree, const BNode *node) {
	
	int isExternal;
	Queue postOrder;
	register unsigned int iCount;
	unsigned int nExternal;
	unsigned int heightR, heightL, heightN;
	const BNode *currentNode;
	unsigned int *tmpHeightData;
	
	iCount = 0;
	nExternal = bst_size(tree) + 1;
	queue_init(&postOrder, 0);
	bst_postOrder(tree, (BNode *) node, &postOrder);
	tmpHeightData = (unsigned int *) malloc(sizeof(unsigned int) * nExternal);
	
	while (queue_size(&postOrder) > 0) {
		
		queue_dequeue(&postOrder, (void **) &currentNode);
		isExternal = bst_isExternal(currentNode);
		
		if (isExternal == 1) {
			*(tmpHeightData + iCount) = 0;
			iCount = iCount + 1;
		}
		else {
			iCount = iCount - 1;
			heightR = *(tmpHeightData + iCount);
			
			iCount = iCount - 1;
			heightL = *(tmpHeightData + iCount);
			
			heightN = 1 + maxu(heightL, heightR);
			*(tmpHeightData + iCount) = heightN;
			iCount = iCount + 1;
		}
	}
	
	heightN = *(tmpHeightData + iCount - 1);
	queue_destroy(&postOrder);
	free((void *) tmpHeightData);
	
	return heightN;
}

