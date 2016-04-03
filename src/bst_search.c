

/************************************************************************************
	Implementation of BST Look-Up (Search) Algorithms
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:				https://github.com/AKD92
*************************************************************************************/






#include "bst.h"








BNode * bst_binarySearch(const BST *tree, const void *key, BNode *startNode) {
	
	register int opCompareKey;
	register const BNode *pNode;
	
	pNode = (const BNode *) startNode;
	while (bst_isExternal(pNode) != 1) {
		
		opCompareKey = tree->compare_key((const void *) key, (const void *) pNode->key);
		if (opCompareKey == 0) {
			break;
		}
		else if (opCompareKey < 0) {
			pNode = bst_leftChild(pNode);
		}
		else if (opCompareKey > 0) {
			pNode = bst_rightChild(pNode);
		}
	}
	
	return (BNode *) pNode;
}





int bst_findElement(const BST *tree, const void *key, void **elem) {
	
	int res;
	const BNode *targetNode;
	
	targetNode = bst_binarySearch(tree, key, bst_root(tree));
	
	if (bst_isInternal(targetNode) == 1) {
		if (elem != 0) *elem = targetNode->element;
		res = 0;
	}
	else if (bst_isExternal(targetNode) == 1) {
		res = -1;
	}
	
	return res;
}
