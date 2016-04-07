

/************************************************************************************
	Implementation of Binary Search Tree Sort Algorithms for Linked List
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "bst.h"
#include <list.h>
#include <dlist.h>
#include <stack.h>
#include <queue.h>






int (*fpCmpUserElem) (const void *arg1, const void *arg2);

static int bst_cmpWrapper(const void *arg1, const void *arg2);





/************************************************************************************/
/************************************************************************************/


int bst_sort(List *list, int (*compare) (const void *arg1, const void *arg2))
{
	return bst_sortAscending(list, compare);
}


int bst_sortDList(DList *dlist, int (*compare) (const void *arg1, const void *arg2))
{
	return bst_sortAscendingDList(dlist, compare);
}




/************************************************************************************/
/************************************************************************************/


int bst_sortAscending(List *list, int (*compare) (const void *arg1, const void *arg2))
{
	
	void *pDataElem;
	register ListElem *pLstElem;
	BNode *pNode;
	BisTree bTree;
	Queue qInorder;
	
	if (list_size(list) < 2)
		return -1;
	
	fpCmpUserElem = compare;
	queue_init(&qInorder, 0);
	bst_init(&bTree, bst_cmpWrapper, 0, 0);
	
	
	/* Insert each object from Singly Linked List to Binary Search Tree (BisTree) */
	pLstElem = list_head(list);
	while (pLstElem != 0) {
		pDataElem = list_data(pLstElem);
		bst_insert(&bTree, (const void *) pDataElem, 0);
		pLstElem = list_next(pLstElem);
	}
	
	
	/* bst_inOrder() returns objects in Ascending Order */
	bst_inOrder((const BisTree *) &bTree, bst_root(&bTree), &qInorder);
	bst_eraseExternalLinks(&qInorder);
	
	
	/* Update object links (pointers) from Queue to Singly Linked List */
	pLstElem = list_head(list);
	while (queue_size(&qInorder) > 0) {
		queue_dequeue(&qInorder, (void **) &pNode);
		list_data(pLstElem) = pNode->pKey;
		pLstElem = list_next(pLstElem);
	}
	
	fpCmpUserElem = 0;
	queue_destroy(&qInorder);
	bst_destroy(&bTree);
	
	return 0;
}


int bst_sortDescending(List *list, int (*compare) (const void *arg1, const void *arg2))
{
	
	void *pDataElem;
	register ListElem *pLstElem;
	BNode *pNode;
	BisTree bTree;
	Stack stReverse;
	Queue qInorder;
	
	if (list_size(list) < 2)
		return -1;
	
	fpCmpUserElem = compare;
	stack_init(&stReverse, 0);
	queue_init(&qInorder, 0);
	bst_init(&bTree, bst_cmpWrapper, 0, 0);
	
	
	/* Insert each object from Singly Linked List to Binary Search Tree (BisTree) */
	pLstElem = list_head(list);
	while (pLstElem != 0) {
		pDataElem = list_data(pLstElem);
		bst_insert(&bTree, (const void *) pDataElem, 0);
		pLstElem = list_next(pLstElem);
	}
	
	
	/* bst_inOrder() returns objects in Ascending Order */
	bst_inOrder((const BisTree *) &bTree, bst_root(&bTree), &qInorder);
	
	
	/* Using a Stack for reversing all objects (Descending Order) */
	while (queue_size(&qInorder) > 0) {
		queue_dequeue(&qInorder, (void **) &pNode);
		if (bst_isInternal((const BNode *) pNode) == 1) {
			stack_push(&stReverse, (const void *) pNode);
		}
	}
	
	
	/* Update object links (pointers) from Stack to Singly Linked List */
	pLstElem = list_head(list);
	while (stack_size(&stReverse) > 0) {
		stack_pop(&stReverse, (void **) &pNode);
		list_data(pLstElem) = pNode->pKey;
		pLstElem = list_next(pLstElem);
	}
	
	fpCmpUserElem = 0;
	stack_destroy(&stReverse);
	queue_destroy(&qInorder);
	bst_destroy(&bTree);
	
	return 0;
}




/************************************************************************************/
/************************************************************************************/


int bst_sortAscendingDList(DList *dlist, int (*compare) (const void *arg1, const void *arg2))
{
	
	void *pDataElem;
	register DListElem *pLstElem;
	BNode *pNode;
	BisTree bTree;
	Queue qInorder;
	
	if (dlist_size(dlist) < 2)
		return -1;
	
	fpCmpUserElem = compare;
	queue_init(&qInorder, 0);
	bst_init(&bTree, bst_cmpWrapper, 0, 0);
	
	
	/* Insert each object from Doubly Linked List to Binary Search Tree (BisTree) */
	pLstElem = dlist_head(dlist);
	while (pLstElem != 0) {
		pDataElem = dlist_data(pLstElem);
		bst_insert(&bTree, (const void *) pDataElem, 0);
		pLstElem = dlist_next(pLstElem);
	}
	
	
	/* bst_inOrder() returns objects in Ascending Order */
	bst_inOrder((const BisTree *) &bTree, bst_root(&bTree), &qInorder);
	bst_eraseExternalLinks(&qInorder);
	
	
	/* Update object links (pointers) from Queue to Doubly Linked List */
	pLstElem = dlist_head(dlist);
	while (queue_size(&qInorder) > 0) {
		queue_dequeue(&qInorder, (void **) &pNode);
		dlist_data(pLstElem) = pNode->pKey;
		pLstElem = dlist_next(pLstElem);
	}
	
	fpCmpUserElem = 0;
	queue_destroy(&qInorder);
	bst_destroy(&bTree);
	
	return 0;
}


int bst_sortDescendingDList(DList *dlist, int (*compare) (const void *arg1, const void *arg2))
{
	
	void *pDataElem;
	register DListElem *pLstElem;
	BNode *pNode;
	BisTree bTree;
	Stack stReverse;
	Queue qInorder;
	
	if (dlist_size(dlist) < 2)
		return -1;
	
	fpCmpUserElem = compare;
	stack_init(&stReverse, 0);
	queue_init(&qInorder, 0);
	bst_init(&bTree, bst_cmpWrapper, 0, 0);
	
	
	/* Insert each object from Doubly Linked List to Binary Search Tree (BisTree) */
	pLstElem = dlist_head(dlist);
	while (pLstElem != 0) {
		pDataElem = dlist_data(pLstElem);
		bst_insert(&bTree, (const void *) pDataElem, 0);
		pLstElem = dlist_next(pLstElem);
	}
	
	
	/* bst_inOrder() returns objects in Ascending Order */
	bst_inOrder((const BisTree *) &bTree, bst_root(&bTree), &qInorder);
	
	
	/* Using a Stack for reversing all objects (Descending Order) */
	while (queue_size(&qInorder) > 0) {
		queue_dequeue(&qInorder, (void **) &pNode);
		if (bst_isInternal((const BNode *) pNode) == 1) {
			stack_push(&stReverse, (const void *) pNode);
		}
	}
	
	
	/* Update object links (pointers) from Stack to Doubly Linked List */
	pLstElem = dlist_head(dlist);
	while (stack_size(&stReverse) > 0) {
		stack_pop(&stReverse, (void **) &pNode);
		dlist_data(pLstElem) = pNode->pKey;
		pLstElem = dlist_next(pLstElem);
	}
	
	fpCmpUserElem = 0;
	stack_destroy(&stReverse);
	queue_destroy(&qInorder);
	bst_destroy(&bTree);
	
	return 0;
}




/************************************************************************************/
/************************************************************************************/


static int bst_cmpWrapper(const void *arg1, const void *arg2) {
	
	int cmpValue;
	
	cmpValue = fpCmpUserElem(arg1, arg2);
	if (cmpValue == 0)
		cmpValue = (int) (arg1 - arg2);
	
	return cmpValue;
}

