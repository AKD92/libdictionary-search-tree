

/************************************************************************************
	Implementation of Binary Search Tree Mutation Functions (Insertion, Deletion)
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/








#include "bst.h"
#include <queue.h>
#include <stdlib.h>
#include <string.h>






/*	bst_expandExternal(BNode *w)
	Returns 0 if successful, -1 if fails
*/

static int bst_expandExternal(BNode *nodeExternal);


/*	bst_removeAboveExternal(BisTree *pTree, BNode *w)
	Returns 0 if successful, -1 if fails
*/

static int bst_removeAboveExternal(BisTree *pTree, BNode *nodeExternal);







static int bst_expandExternal(BNode *nodeExternal) {
	
	BNode *pLeftChild, *pRightChild;
	
	if (bst_isInternal((const BNode *) nodeExternal) == 1)
		return -1;
	
	pLeftChild = pRightChild = 0;
	pLeftChild = (BNode *) malloc(sizeof(BNode));
	pRightChild = (BNode *) malloc(sizeof(BNode));
	
	if (((unsigned int)pLeftChild & (unsigned int)pRightChild) == 0)
	{
		free((void *) pLeftChild);
		free((void *) pRightChild);
		return -1;
	}
	
	memset((void *) pLeftChild, 0, sizeof(BNode));
	memset((void *) pRightChild, 0, sizeof(BNode));
	
	/* Actually, nodeExternal bocomes an Internal by executing the following codes */
	nodeExternal->leftChild = pLeftChild;
	nodeExternal->rightChild = pRightChild;
	
	pLeftChild->parent = nodeExternal;
	pRightChild->parent = nodeExternal;
	
	return 0;
}


static int bst_removeAboveExternal(BisTree *pTree, BNode *pExternal) {
	
	int isLeftChild;
	BNode *pParent, *pHigherParent;						/* v = parent(w), u = parent(v) */
	BNode *pSibling;									/* z = sibling(w)				*/
	
	if (bst_isInternal((const BNode *) pExternal) == 1)
		return -1;
	if (bst_parent((const BNode *) pExternal) == 0)
		return -1;
	
	pParent = bst_parent((const BNode *) pExternal);			/* Parent BNode of specified external BNode */
	pHigherParent = bst_parent((const BNode *) pParent);		/* Grand parent BNode of specified BNode */
	pSibling = bst_sibling((const BNode *) pExternal);		/* Sibling or Brother BNode of specified BNode */
	
	
	/* Determine if pParent is the Left Child of pHigherParent */
	isLeftChild = (pParent == bst_leftChild((const BNode *) pHigherParent)) ? 1 : 0;
	
	/* Destroy parent BNode and specifed external BNode */
	free((void *) pParent);
	free((void *) pExternal);
	pParent = pExternal = 0;
	pSibling->parent = pHigherParent;
	
	/* If grand parent exist, adjust its left and right children appropriately */
	if (pHigherParent != 0) {
		
		switch (isLeftChild) {
		case 1:					/* pParent is Left Child of pHigherParent (Grand parent) */
			pHigherParent->leftChild = pSibling;
			break;
		case 0:					/* pParent is Right Child of pHigherParent (Grand parent) */
			pHigherParent->rightChild = pSibling;
			break;
		default:
			break;
		}
	}
	/* If Grand Parent does not exist, make the sibling BNode as pTree's Root BNode */
	else {
		pSibling->parent = 0;
		pTree->root = pSibling;
	}
	
	return 0;
}



int bst_changeElement(BisTree *pTree, const void *pKey, const void *pElem, void **pOldelem) {
	
	int res;
	BNode *targetNode;
	
	if (pTree == 0 || pKey == 0)
		return -1;
	
	targetNode = bst_binarySearch((const BisTree *) pTree, pKey, bst_root(pTree));
	
	if (bst_isExternal((const BNode *) targetNode) == 1) {
		res = -1;
	}
	else {
		if (pOldelem != 0) *pOldelem = targetNode->pElement;
		targetNode->pElement = (void *) pElem;
		res = 0;
	}
	
	return res;
}



int bst_insert(BisTree *pTree, const void *pKey, const void *pElem) {
	
	int res;
	int opExpand;
	BNode *targetNode;
	
	if (pTree == 0 || pKey == 0)
		return -1;
	
	/* Search for the pKey in our BisTree */
	targetNode = bst_binarySearch((const BisTree *) pTree, pKey, bst_root(pTree));
	
	/* Key not found, we have got an External BNode */
	/* So make it Internal and assing this Key and Elem to it */
	if (bst_isExternal((const BNode *) targetNode) == 1) {
		
		opExpand = bst_expandExternal(targetNode);
		if (opExpand != 0)
			return -1;
		
		targetNode->pKey = (void *) pKey;
		targetNode->pElement = (void *) pElem;
		pTree->size++;
		res = 0;
	}
	else {
		
		/* We have got an Internal BNode, it means Key already exist */
		/* In this situation we cannot insert the given Key into our BisTree */
		res = -1;
	}
	
	return res;
}



int bst_remove(BisTree *pTree, const void *pKey, void **pRemovedKey, void **pRemovedElem) {
	
	int res;
	int targetExternal;
	int left_external, right_external;
	int both_internal;
	
	BNode *pTarget;
	BNode *pLeftChild, *pRightChild;
	BNode *pChildExternal, *pInorderInternal, *pInorderExternal;
	
	Queue qInorder;
	
	if (pTree == 0 || pKey == 0)
		return -1;
	
	pChildExternal = 0;
	queue_init(&qInorder, 0);
	pTarget = bst_binarySearch((const BisTree *) pTree, pKey, bst_root(pTree));
	targetExternal = bst_isExternal((const BNode *) pTarget);
	
	if (targetExternal == 1) {
		res = -1;
	}
	else {
		
		if (pRemovedKey != 0) *pRemovedKey = pTarget->pKey;
		if (pRemovedElem != 0) *pRemovedElem = pTarget->pElement;
		
		pLeftChild = bst_leftChild((const BNode *) pTarget);
		pRightChild = bst_rightChild((const BNode *) pTarget);
		
		left_external = bst_isExternal((const BNode *) pLeftChild);
		right_external = bst_isExternal((const BNode *) pRightChild);
		
		/* Both childs are internal if Left And Right childs are NOT External */
		both_internal = !(left_external | right_external);
		
		if (both_internal == 0) {
			
			/* Find the External child of pTarget and pChildExternal will be the External one */
			if (left_external == 1) pChildExternal = pLeftChild;
			if (right_external == 1) pChildExternal = pRightChild;
			
			bst_removeAboveExternal(pTree, pChildExternal);
		}
		else if (both_internal == 1) {
			
			bst_inOrder((const BisTree *) pTree, pRightChild, &qInorder);
			
			/* Find two External Node from Inorder sequence */
			/* More information about this operation on the Book */
			queue_dequeue(&qInorder, (void **) &pInorderExternal);
			queue_dequeue(&qInorder, (void **) &pInorderInternal);
			
			/* Swap the pKeys and pElements between two internal node */
			pTarget->pKey = pInorderInternal->pKey;
			pInorderInternal->pKey = 0;
			pTarget->pElement = pInorderInternal->pElement;
			pInorderInternal->pElement = 0;
			
			/* Remove internal node pInorderInternal */
			bst_removeAboveExternal(pTree, pInorderExternal);
		}
		
		pTree->size--;
		res = 0;
	}
	
	queue_destroy(&qInorder);
	return res;
}

