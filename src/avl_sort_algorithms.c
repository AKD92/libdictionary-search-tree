

/************************************************************************************
    Implementation of Binary Search Tree Sort Algorithms for Linked List
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "avl.h"
#include "avl_internal.h"
#include <list.h>
#include <dlist.h>
#include <stack.h>
#include <queue.h>







static void destroy_list(void *arg);





int avl_treesort(List *list, int (*fpCompare) (const void *arg1, const void *arg2))
{
    return avl_treesort_asc(list, fpCompare);
}



int avl_treesort_dl(DList *dlist, int (*fpCompare) (const void *arg1, const void *arg2))
{
    return avl_treesort_dl_asc(dlist, fpCompare);
}



int avl_treesort_asc(List *list, int (*fpCompare) (const void *arg1, const void *arg2))
{
    
    void *pDataElem;
    register ListElem *pLstElem;
    int opval;
    BNode *pNode;
    AvlTree bTree;
    Queue inorder;
    Queue *eqv_elems;
    
    if (list == 0 || fpCompare == 0)
        return -1;
    if (list_size(list) < 2)
        return 0;
    
    queue_init(&inorder, 0);
    avl_init(&bTree, fpCompare, 0, destroy_list);
    
    
    /* Insert each object from Singly Linked List to Binary Search Tree (AvlTree) */
    pLstElem = list_head(list);
    while (pLstElem != 0) {
        pDataElem = list_data(pLstElem);
        opval = avl_insert(&bTree, (const void *) pDataElem, 0);
        
        /*  If insertion is failed (element already exists)
            Then we insert this into a list as the data/value of the key
        */
        if (opval != 0) {
            eqv_elems = 0;
            avl_lookup(&bTree, (const void *) pDataElem, (void **) &eqv_elems);
            
            if (eqv_elems == 0) {
                eqv_elems = (Queue *) malloc(sizeof(Queue));
                queue_init(eqv_elems, 0);
                avl_reassign(&bTree, (const void *) pDataElem, (const void *) eqv_elems);
            }
            queue_enqueue(eqv_elems, (const void *) pDataElem);
        }
        pLstElem = list_next(pLstElem);
    }
    
    
    /* bst_inorder() returns objects in Ascending Order */
    bst_inorder(bst_root(&bTree), BNODE_ALLOW_INTERNAL, &inorder);
    
    
    /* Update object links (pointers) from Queue to Singly Linked List */
    pLstElem = list_head(list);
    while (queue_size(&inorder) > 0) {
        queue_dequeue(&inorder, (void **) &pNode);
        list_data(pLstElem) = pNode->pKey;
        
        /*  We may have multiple eqv_elems of same element as value associated with this key
            If so, then obtain the queue and transfer the elements from queue to output list
        */
        if (pNode->pElement != 0) {
            eqv_elems = (Queue *) pNode->pElement;
            while (queue_size(eqv_elems) > 0) {
                pLstElem = list_next(pLstElem);
                queue_dequeue(eqv_elems, (void **) &pDataElem);
                list_data(pLstElem) = pDataElem;
            }
        }
        pLstElem = list_next(pLstElem);
    }
    
    queue_destroy(&inorder);
    avl_destroy(&bTree);
    
    return 0;
}



int avl_treesort_desc(List *list, int (*fpCompare) (const void *arg1, const void *arg2))
{
    
    void *pDataElem;
    register ListElem *pLstElem;
    int opval;
    BNode *pNode;
    AvlTree bTree;
    Queue inorder;
    Queue *eqv_elems;
    
    if (list == 0 || fpCompare == 0)
        return -1;
    if (list_size(list) < 2)
        return 0;
    
    queue_init(&inorder, 0);
    bst_init(&bTree, fpCompare, 0, destroy_list);
    
    
    /* Insert each object from Singly Linked List to Binary Search Tree (AvlTree) */
    pLstElem = list_head(list);
    while (pLstElem != 0) {
        pDataElem = list_data(pLstElem);
        opval = avl_insert(&bTree, (const void *) pDataElem, 0);
        
        /*  If insertion is failed (element already exists)
            Then we insert this into a list as the data/value of the key
        */
        if (opval != 0) {
            eqv_elems = 0;
            avl_lookup(&bTree, (const void *) pDataElem, (void **) &eqv_elems);
            
            if (eqv_elems == 0) {
                eqv_elems = (Queue *) malloc(sizeof(Queue));
                queue_init(eqv_elems, 0);
                avl_reassign(&bTree, (const void *) pDataElem, (const void *) eqv_elems);
            }
            queue_enqueue(eqv_elems, (const void *) pDataElem);
        }
        pLstElem = list_next(pLstElem);
    }
    
    
    /* bst_reverse_inorder() returns objects in Descending Order */
    bst_reverse_inorder(bst_root(&bTree), BNODE_ALLOW_INTERNAL, &inorder);
    
    
    /* Update object links (pointers) from Stack to Singly Linked List */
    pLstElem = list_head(list);
    while (queue_size(&inorder) > 0) {
        queue_dequeue(&inorder, (void **) &pNode);
        list_data(pLstElem) = pNode->pKey;
        
        /*  We may have multiple eqv_elems of same element as value associated with this key
            If so, then obtain the queue and transfer the elements from queue to output list
        */
        if (pNode->pElement != 0) {
            eqv_elems = (Queue *) pNode->pElement;
            while (queue_size(eqv_elems) > 0) {
                pLstElem = list_next(pLstElem);
                queue_dequeue(eqv_elems, (void **) &pDataElem);
                list_data(pLstElem) = pDataElem;
            }
        }
        pLstElem = list_next(pLstElem);
    }
    
    queue_destroy(&inorder);
    avl_destroy(&bTree);
    
    return 0;
}



int avl_treesort_dl_asc(DList *dlist, int (*fpCompare) (const void *arg1, const void *arg2))
{
    
    void *pDataElem;
    register DListElem *pLstElem;
    int opval;
    BNode *pNode;
    AvlTree bTree;
    Queue inorder, *eqv_elems;
    
    if (dlist == 0 || fpCompare == 0)
        return -1;
    if (dlist_size(dlist) < 2)
        return 0;
    
    queue_init(&inorder, 0);
    bst_init(&bTree, fpCompare, 0, destroy_list);
    
    
    /* Insert each object from Doubly Linked List to Binary Search Tree (AvlTree) */
    pLstElem = dlist_head(dlist);
    while (pLstElem != 0) {
        pDataElem = dlist_data(pLstElem);
        opval = avl_insert(&bTree, (const void *) pDataElem, 0);
        
        /*  If insertion is failed (element already exists)
            Then we insert this into a list as the data/value of the key
        */
        if (opval != 0) {
            eqv_elems = 0;
            avl_lookup(&bTree, (const void *) pDataElem, (void **) &eqv_elems);
            
            if (eqv_elems == 0) {
                eqv_elems = (Queue *) malloc(sizeof(Queue));
                queue_init(eqv_elems, 0);
                avl_reassign(&bTree, (const void *) pDataElem, (const void *) eqv_elems);
            }
            queue_enqueue(eqv_elems, (const void *) pDataElem);
        }
        pLstElem = dlist_next(pLstElem);
    }
    
    
    /* bst_inorder() returns objects in Ascending Order */
    bst_inorder(bst_root(&bTree), BNODE_ALLOW_INTERNAL, &inorder);
    
    
    /* Update object links (pointers) from Queue to Doubly Linked List */
    pLstElem = dlist_head(dlist);
    while (queue_size(&inorder) > 0) {
        queue_dequeue(&inorder, (void **) &pNode);
        dlist_data(pLstElem) = pNode->pKey;
        
        /*  We may have multiple eqv_elems of same element as value associated with this key
            If so, then obtain the queue and transfer the elements from queue to output list
        */
        if (pNode->pElement != 0) {
            eqv_elems = (Queue *) pNode->pElement;
            while (queue_size(eqv_elems) > 0) {
                pLstElem = dlist_next(pLstElem);
                queue_dequeue(eqv_elems, (void **) &pDataElem);
                dlist_data(pLstElem) = pDataElem;
            }
        }
        pLstElem = dlist_next(pLstElem);
    }
    
    queue_destroy(&inorder);
    avl_destroy(&bTree);
    
    return 0;
}



int avl_treesort_dl_desc(DList *dlist, int (*fpCompare) (const void *arg1, const void *arg2))
{
    
    void *pDataElem;
    register DListElem *pLstElem;
    int opval;
    BNode *pNode;
    AvlTree bTree;
    Stack stReverse;
    Queue inorder, *eqv_elems;
    
    if (dlist == 0 || fpCompare == 0)
        return -1;
    if (dlist_size(dlist) < 2)
        return 0;
    
    stack_init(&stReverse, 0);
    queue_init(&inorder, 0);
    bst_init(&bTree, fpCompare, 0, destroy_list);
    
    
    /* Insert each object from Doubly Linked List to Binary Search Tree (AvlTree) */
    pLstElem = dlist_head(dlist);
    while (pLstElem != 0) {
        pDataElem = dlist_data(pLstElem);
        opval = avl_insert(&bTree, (const void *) pDataElem, 0);
        
        /*  If insertion is failed (element already exists)
            Then we insert this into a list as the data/value of the key
        */
        if (opval != 0) {
            eqv_elems = 0;
            avl_lookup(&bTree, (const void *) pDataElem, (void **) &eqv_elems);
            
            if (eqv_elems == 0) {
                eqv_elems = (Queue *) malloc(sizeof(Queue));
                queue_init(eqv_elems, 0);
                avl_reassign(&bTree, (const void *) pDataElem, (const void *) eqv_elems);
            }
            queue_enqueue(eqv_elems, (const void *) pDataElem);
        }
        pLstElem = dlist_next(pLstElem);
    }
    
    
    /* bst_inorder() returns objects in Ascending Order */
    bst_inorder(bst_root(&bTree), BNODE_ALLOW_INTERNAL, &inorder);
    
    
    /* Using a Stack for reversing all objects (Descending Order) */
    while (queue_size(&inorder) > 0) {
        queue_dequeue(&inorder, (void **) &pNode);
        stack_push(&stReverse, (const void *) pNode);
    }
    
    
    /* Update object links (pointers) from Stack to Doubly Linked List */
    pLstElem = dlist_head(dlist);
    while (stack_size(&stReverse) > 0) {
        stack_pop(&stReverse, (void **) &pNode);
        dlist_data(pLstElem) = pNode->pKey;
        
        /*  We may have multiple eqv_elems of same element as value associated with this key
            If so, then obtain the queue and transfer the elements from queue to output list
        */
        if (pNode->pElement != 0) {
            eqv_elems = (Queue *) pNode->pElement;
            while (queue_size(eqv_elems) > 0) {
                pLstElem = dlist_next(pLstElem);
                queue_dequeue(eqv_elems, (void **) &pDataElem);
                dlist_data(pLstElem) = pDataElem;
            }
        }
        pLstElem = dlist_next(pLstElem);
    }
    
    stack_destroy(&stReverse);
    queue_destroy(&inorder);
    avl_destroy(&bTree);
    
    return 0;
}




/************************************************************************************/
/************************************************************************************/


static void destroy_list(void *arg) {
    queue_destroy((Queue *) arg);
    free(arg);
    return;
}

