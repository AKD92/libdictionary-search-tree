

/************************************************************************************
	Implementation of BST Mutation Functions (Insertion, Deletion)
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:				https://github.com/AKD92
*************************************************************************************/






#include "bst.h"
#include <queue.h>
#include <stdlib.h>
#include <string.h>






/*	bst_expandExternal(BNode *w)
	Returns 0 if successful, -1 if fails
*/

static int bst_expandExternal(BNode *nodeExternal);


/*	bst_removeAboveExternal(BST *tree, BNode *w)
	Returns 0 if successful, -1 if fails
*/

static int bst_removeAboveExternal(BST *tree, BNode *nodeExternal);







static int bst_expandExternal(BNode *nodeExternal) {
	
	BNode *leftChild, *rightChild;
	
	if (bst_isInternal((const BNode *) nodeExternal) == 1)
		return -1;
	
	leftChild = rightChild = 0;
	leftChild = (BNode *) malloc(sizeof(BNode));
	rightChild = (BNode *) malloc(sizeof(BNode));
	
	if (((unsigned int)leftChild & (unsigned int)rightChild) == 0)
	{
		free((void *) leftChild);
		free((void *) rightChild);
		return -1;
	}
	
	memset((void *) leftChild, 0, sizeof(BNode));
	memset((void *) rightChild, 0, sizeof(BNode));
	
	/* Actually, nodeExternal bocomes an Internal by executing the following codes */
	nodeExternal->leftChild = leftChild;
	nodeExternal->rightChild = rightChild;
	
	leftChild->parent = nodeExternal;
	rightChild->parent = nodeExternal;
	
	return 0;
}


static int bst_removeAboveExternal(BST *tree, BNode *nodeExternal) {
	
	int isLeftChild;
	BNode *nodeParent, *nodeHigherParent;			/* v = parent(w), u = parent(v) */
	BNode *nodeSibling;								/* z = sibling(w)				*/
	
	if (bst_isInternal((const BNode *) nodeExternal) == 1)
		return -1;
	if (bst_parent((const BNode *) nodeExternal) == 0)
		return -1;
	
	nodeParent = bst_parent((const BNode *) nodeExternal);			/* Parent BNode of specified external BNode */
	nodeHigherParent = bst_parent((const BNode *) nodeParent);		/* Grand parent BNode of specified BNode */
	nodeSibling = bst_sibling((const BNode *) nodeExternal);		/* Sibling or Brother BNode of specified BNode */
	
	
	/* Determine if nodeParent is the Left Child of nodeHigherParent */
	isLeftChild = (nodeParent == bst_leftChild((const BNode *) nodeHigherParent)) ? 1 : 0;
	
	/* Destroy parent BNode and specifed external BNode */
	free((void *) nodeParent);
	free((void *) nodeExternal);
	nodeParent = nodeExternal = 0;
	nodeSibling->parent = nodeHigherParent;
	
	/* If grand parent exist, adjust its left and right children appropriately */
	if (nodeHigherParent != 0) {
		
		switch (isLeftChild) {
		case 1:					/* nodeParent is Left Child of nodeHigherParent (Grand parent) */
			nodeHigherParent->leftChild = nodeSibling;
			break;
		case 0:					/* nodeParent is Right Child of nodeHigherParent (Grand parent) */
			nodeHigherParent->rightChild = nodeSibling;
			break;
		default:
			break;
		}
	}
	/* If Grand Parent does not exist, make the sibling BNode as tree's Root BNode */
	else {
		nodeSibling->parent = 0;
		tree->root = nodeSibling;
	}
	
	return 0;
}



int bst_changeElement(BST *tree, const void *key, const void *elem, void **old_elem) {
	
	int res;
	BNode *targetNode;
	
	if (tree == 0 || key == 0)
		return -1;
	
	targetNode = bst_binarySearch((const BST *) tree, key, bst_root(tree));
	
	if (bst_isExternal((const BNode *) targetNode) == 1) {
		res = -1;
	}
	else {
		if (old_elem != 0) *old_elem = targetNode->element;
		targetNode->element = (void *) elem;
		res = 0;
	}
	
	return res;
}



int bst_insert(BST *tree, const void *key, const void *elem) {
	
	int res;
	int opExpand;
	BNode *targetNode;
	
	if (tree == 0 || key == 0)
		return -1;
	
	/* Search for the key in our BST */
	targetNode = bst_binarySearch((const BST *) tree, key, bst_root(tree));
	
	/* Key not found, we have got an External BNode */
	/* So make it Internal and assing this Key and Elem to it */
	if (bst_isExternal((const BNode *) targetNode) == 1) {
		
		opExpand = bst_expandExternal(targetNode);
		if (opExpand != 0)
			return -1;
		
		targetNode->key = (void *) key;
		targetNode->element = (void *) elem;
		tree->size++;
		res = 0;
	}
	else {
		
		/* We have got an Internal BNode, it means Key already exist */
		/* In this situation we cannot insert the given Key into our BST */
		res = -1;
	}
	
	return res;
}



int bst_remove(BST *tree, const void *key, void **removedKey, void **removedElem) {
	
	int res;
	int targetExternal;
	int left_external, right_external;
	int both_internal;
	
	BNode *targetNode;
	BNode *leftChild, *rightChild;
	BNode *externalChild, *inorderInternal, *inorderExternal;
	
	Queue inOrder;
	
	if (tree == 0 || key == 0)
		return -1;
	
	externalChild = 0;
	queue_init(&inOrder, 0);
	targetNode = bst_binarySearch((const BST *) tree, key, bst_root(tree));
	targetExternal = bst_isExternal((const BNode *) targetNode);
	
	if (targetExternal == 1) {
		res = -1;
	}
	else {
		
		if (removedKey != 0) *removedKey = targetNode->key;
		if (removedElem != 0) *removedElem = targetNode->element;
		
		leftChild = bst_leftChild((const BNode *) targetNode);
		rightChild = bst_rightChild((const BNode *) targetNode);
		
		left_external = bst_isExternal((const BNode *) leftChild);
		right_external = bst_isExternal((const BNode *) rightChild);
		
		/* Both childs are internal if Left And Right childs are NOT External */
		both_internal = !(left_external | right_external);
		
		if (both_internal == 0) {
			
			/* Find the External child of targetNode and externalChild will be the External one */
			if (left_external == 1) externalChild = leftChild;
			if (right_external == 1) externalChild = rightChild;
			
			bst_removeAboveExternal(tree, externalChild);
		}
		else if (both_internal == 1) {
			
			bst_inOrder((const BST *) tree, rightChild, &inOrder);
			
			/* Find two External Node from Inorder sequence */
			/* More information about this operation on the Book */
			queue_dequeue(&inOrder, (void **) &inorderExternal);
			queue_dequeue(&inOrder, (void **) &inorderInternal);
			
			/* Swap the keys and elements between two internal node */
			targetNode->key = inorderInternal->key;
			inorderInternal->key = 0;
			targetNode->element = inorderInternal->element;
			inorderInternal->element = 0;
			
			/* Remove internal node inorderInternal */
			bst_removeAboveExternal(tree, inorderExternal);
		}
		
		tree->size--;
		res = 0;
	}
	
	queue_destroy(&inOrder);
	return res;
}

