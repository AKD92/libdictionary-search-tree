

/************************************************************************************
	Implementation of Binary Search Tree Look-Up (Search) Algorithms
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "bst.h"








BNode * bst_binarySearch(const BisTree *pTree, const void *key, BNode *pStartNode) {
	
	register int opCompareKey;
	register const BNode *pNode;
	
	pNode = (const BNode *) pStartNode;
	while (bst_isExternal(pNode) != 1) {
		
		opCompareKey = pTree->fpCompareKey((const void *) key, (const void *) pNode->pKey);
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
	
	int retVal;
	const BNode *pTarget;
	
	pTarget = bst_binarySearch(pTree, key, bst_root(pTree));
	
	if (bst_isInternal(pTarget) == 1) {
		if (elem != 0) *elem = pTarget->pElement;
		retVal = 0;
	}
	else if (bst_isExternal(pTarget) == 1) {
		retVal = -1;
	}
	
	return retVal;
}

