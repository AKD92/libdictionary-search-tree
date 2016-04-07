

/************************************************************************************
	Implementation of Binary Search Tree Look-Up (Search) Algorithms
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "bst.h"








BNode * bst_binarySearch(const BisTree *pTree, const void *key, BNode *startNode) {
	
	register int opCompareKey;
	register const BNode *pNode;
	
	pNode = (const BNode *) startNode;
	while (bst_isExternal(pNode) != 1) {
		
		opCompareKey = pTree->fpCompareKey((const void *) key, (const void *) pNode->key);
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





int bst_findElement(const BisTree *pTree, const void *key, void **elem) {
	
	int res;
	const BNode *pTargetNode;
	
	pTargetNode = bst_binarySearch(pTree, key, bst_root(pTree));
	
	if (bst_isInternal(pTargetNode) == 1) {
		if (elem != 0) *elem = pTargetNode->element;
		res = 0;
	}
	else if (bst_isExternal(pTargetNode) == 1) {
		res = -1;
	}
	
	return res;
}
