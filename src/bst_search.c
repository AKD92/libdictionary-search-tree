


#include "bst.h"








BNode * bst_treeSearch(BST *tree, void *key, BNode *startNode) {
	
	int cmpres;
	
	/*	printf("treeSearch: Is v the root? %d\n", bst_isRoot(tree, v));*/
	/*	printf("treeSearch: Is v external? %d\n", bst_isExternal(v));*/
	
	while (bst_isExternal(startNode) != 1) {
		
		cmpres = tree->compare_key(key, startNode->key);
		
		if (cmpres == 0) {
			break;
		}
		else if (cmpres < 0) {
			startNode = bst_leftChild(startNode);
		}
		else if (cmpres > 0) {
			startNode = bst_rightChild(startNode);
		}
	}
	
	return startNode;
}





/*	Searches for a given key in the BST
Return 0 if successful, -1 otherwise
*/


int bst_findElement(BST *tree, void *key, void **elem) {
	
	int res;
	BNode *v;
	v = bst_treeSearch(tree, key, bst_root(tree));
	
	if (bst_isInternal(v) == 1) {
		*elem = v->element;
		res = 0;
	}
	else if (bst_isExternal(v) == 1) {
		res = -1;
	}
	
	return res;
}