

/************************************************************************************
	Implementation of BST Look-Up (Search) Algorithms
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
*************************************************************************************/






#include "bst.h"








BNode * bst_binarySearch(const BST *tree, const void *key, BNode *startNode) {
	
	register int opCompare;
	
	/*	printf("treeSearch: Is v the root? %d\n", bst_isRoot(tree, v));*/
	/*	printf("treeSearch: Is v external? %d\n", bst_isExternal(v));*/
	
	while (bst_isExternal((const BNode *) startNode) != 1) {
		
		opCompare = tree->compare_key((const void *) key, (const void *) startNode->key);
		
		if (opCompare == 0) {
			break;
		}
		else if (opCompare < 0) {
			startNode = bst_leftChild((const BNode *) startNode);
		}
		else if (opCompare > 0) {
			startNode = bst_rightChild((const BNode *) startNode);
		}
	}
	
	return startNode;
}





/*	Searches for a given key in the BST
Return 0 if successful, -1 otherwise
*/


int bst_findElement(const BST *tree, const void *key, void **elem) {
	
	int res;
	BNode *v;
	
	v = bst_binarySearch(tree, key, bst_root(tree));
	
	if (bst_isInternal((const BNode *) v) == 1) {
		if (elem != 0) *elem = v->element;
		res = 0;
	}
	else if (bst_isExternal((const BNode *) v) == 1) {
		res = -1;
	}
	
	return res;
}
