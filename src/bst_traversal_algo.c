

/************************************************************************************
	Implementation of BST Tree Traversal Algorithms
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
*************************************************************************************/






#include "bst.h"
#include <stack.h>
#include <queue.h>







int bst_compareNodeObj(const void *key1, const void *key2);







int bst_compareNodeObj(const void *key1, const void *key2) {
	
	if (key1 == key2) return 0;
	else return 1;
	
}




int bst_postorder(const BST *tree, BNode *v, Queue *out) {
	
	BNode *n;
	BNode *n_left, *n_right;
	
	Stack st1, st2;
	
	stack_init(&st1, 0);
	stack_init(&st2, 0);
	
	stack_push(&st1, (const void *) v);
	
	while (stack_size(&st1) > 0) {
		
		stack_pop(&st1, (void **) &n);
		stack_push(&st2, (const void *) n);
		
		n_left = bst_leftChild((const BNode *) n);
		n_right = bst_rightChild((const BNode *) n);
		
		if (n_left != 0) {
			stack_push(&st1, (const void *) n_left);
		}
		if (n_right != 0) {
			stack_push(&st1, (const void *) n_right);
		}
	}
	
	while (stack_size(&st2) > 0) {
		
		stack_pop(&st2, (void **) &n);
		queue_enqueue(out, (const void *) n);
	}
	
	return 0;
}




int bst_inorder(const BST *tree, BNode *v, Queue *out) {
	
	BNode *n;
	BNode *n_left, *n_right;
	int opCompare;
	Stack st;
	/*	Queue out;*/
	
	stack_init(&st, 0);
	/*	queue_init(&out, 0);*/
	
	stack_push(&st, (const void *) v);
	
	while (stack_size(&st) > 0) {
		
		stack_pop(&st, (void **) &n);
		
		n_left = bst_leftChild((const BNode *) n);
		n_right = bst_rightChild((const BNode *) n);
		
		opCompare = queue_linearSearch(out, (void*) n_left, bst_compareNodeObj);
		
		if (n_left != 0 && opCompare == 0) {
			stack_push(&st, (const void *) n);
			stack_push(&st, (const void *) n_left);
		}
		else {
			queue_enqueue(out, (const void *) n);
			if (n_right != 0) {
				stack_push(&st, (const void *) n_right);
			}
		}
		
	}
	
	/*	while (queue_size(&out) > 0) {*/
	
	/*		queue_dequeue(&out, &n);*/
	/*		opCompare = visit(n);*/
	/*		if (opCompare == -1) break;*/
	/*	}*/
	
	stack_destroy(&st);
	/*	queue_destroy(&out);*/
	
	return 0;
}
