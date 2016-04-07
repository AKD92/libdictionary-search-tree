

/************************************************************************************
	Implementation of Binary Search Tree Key:Value List Generation Algorithms
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "bst.h"
#include <list.h>
#include <queue.h>







int bst_keys(const BisTree *pTree, List *keyList) {
	
	BNode *pNode;
	Queue qNodes;
	ListElem *pLstElem;
	
	queue_init(&qNodes, 0);
	pLstElem = list_head(keyList);
	
	/* Use Inorder algorithm to get a Sorted Key sequence (might be convenient) */
	bst_inOrder(pTree, bst_root(pTree), &qNodes);
	
	while (queue_size(&qNodes) > 0) {
		
		queue_dequeue(&qNodes, (void **) &pNode);
		
		if (bst_isInternal((const BNode *) pNode)) {
			list_ins_next(keyList, pLstElem, (const void *) pNode->key);
			pLstElem = list_tail(keyList);
		}
	}
	
	queue_destroy(&qNodes);
	return 0;
}




int bst_elements(const BisTree *pTree, List *elementList) {
	
	BNode *pNode;
	Queue qNodes;
	ListElem *pLstElem;
	
	queue_init(&qNodes, 0);
	pLstElem = list_tail(elementList);
	
	/* Use Inorder algorithm to get a Sorted Element sequence (According to Keys) */
	bst_inOrder(pTree, bst_root(pTree), &qNodes);
	
	while (queue_size(&qNodes) > 0) {
		
		queue_dequeue(&qNodes, (void **) &pNode);
		
		if (bst_isInternal((const BNode *) pNode)) {
			list_ins_next(elementList, pLstElem, (const void *) pNode->element);
			pLstElem = list_tail(elementList);
		}
	}
	
	queue_destroy(&qNodes);
	return 0;
}
