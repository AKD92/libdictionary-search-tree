

/************************************************************************************
	Implementation of BST Look-Up (Search) Algorithms
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
*************************************************************************************/






#include "bst.h"








BNode * bst_binarySearch(const BST *tree, const void *key, BNode *startNode) {
	
	register int opCompare;
	const BNode *curNode;
	
	curNode = (const BNode *) startNode;
	
	while (bst_isExternal(curNode) != 1) {
		
		opCompare = tree->compare_key((const void *) key, (const void *) curNode->key);
		
		if (opCompare == 0) {
			break;
		}
		else if (opCompare < 0) {
			curNode = bst_leftChild(curNode);
		}
		else if (opCompare > 0) {
			curNode = bst_rightChild(curNode);
		}
	}
	
	return (BNode *) curNode;
}





int bst_findElement(const BST *tree, const void *key, void **elem) {
	
	int res;
	const BNode *v;
	
	v = bst_binarySearch(tree, key, bst_root(tree));
	
	if (bst_isInternal(v) == 1) {
		if (elem != 0) *elem = v->element;
		res = 0;
	}
	else if (bst_isExternal(v) == 1) {
		res = -1;
	}
	
	return res;
}
