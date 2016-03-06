


#include "bst.h"
#include <list.h>
#include <queue.h>







int bst_keys(BST *tree, List *keyList) {
	
	ListElem *n;
	BNode *node;
	Queue nodeQ;
	
	queue_init(&nodeQ, 0);
	list_init(keyList, 0);
	n = list_head(keyList);
	
	bst_inorder(tree, bst_root(tree), &nodeQ);
	
	while (queue_size(&nodeQ) > 0) {
		
		queue_dequeue(&nodeQ, (void **) &node);
		
		if (bst_isInternal(node)) {
			
			list_ins_next(keyList, n, (const void *) node->key);
			n = list_tail(keyList);
		}
	}
	
	queue_destroy(&nodeQ);
	return 0;
}




int bst_elements(BST *tree, List *elementList) {
	
	ListElem *n;
	BNode *node;
	Queue nodeQ;
	
	queue_init(&nodeQ, 0);
	list_init(elementList, 0);
	n = list_tail(elementList);
	
	bst_inorder(tree, bst_root(tree), &nodeQ);
	
	while (queue_size(&nodeQ) > 0) {
		
		queue_dequeue(&nodeQ, (void **) &node);
		
		if (bst_isInternal(node)) {
			
			list_ins_next(elementList, n, (const void *) node->element);
			n = list_tail(elementList);
		}
	}
	
	queue_destroy(&nodeQ);
	return 0;
}
