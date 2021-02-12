



#include "avl.h"
#include "avl_internal.h"
#include <stdio.h>
#include <stdlib.h>
#include <queue.h>



int cmpInt(const void *k1, const void *k2);

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(void) {
    
    AvlTree avlTree;
    Queue nodes;
    int *pKey, *pRemovedKey;
    int opRes;
    List *list;
    ListElem *elem;
    BNode *pNode;
    int keys[13] = {44, 17, 88, 28, 65, 97, 29, 54, 82, 76, 80, 78 , 28};
    unsigned int depth, height;
    
    avl_init(&avlTree, cmpInt, 0, 0);
    queue_init(&nodes, 0);
    
    printf("\nInserting 13 auto-allocated key\n");
    int i = 0;
    while (i < 13) {
        opRes = avl_insert(&avlTree, (const void *) &keys[i], 0);
        printf("insert avl: %d opRes: %d\n", keys[i], opRes);
        i++;
    }
    
    printf("Complete\n");
    
    
    pKey = (int *) malloc(sizeof(int));
    *pKey = 77;
    printf("\nInserted a manually allocated key, addr: %p, val: %d\n\n",
                    pKey, *pKey);
    avl_insert(&avlTree, pKey, 0);
    pKey = 0;
    
    avl_levelorder_lr(avl_root(&avlTree), BST_ALLOW_INTERNAL, &nodes);
    printf("Printing after insertion (Level LR Order) (Internal = %u)\n",
                            queue_size(&nodes));
    
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    
    
    queue_destroy(&nodes);
    queue_init(&nodes, 0);
    avl_preorder(avl_root(&avlTree), BST_ALLOW_INTERNAL, &nodes);
    printf("Printing after insertion (Pre Order) (Internal = %u)\n",
                            queue_size(&nodes));
    
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    

    queue_destroy(&nodes);
    queue_init(&nodes, 0);
    avl_postorder(avl_root(&avlTree), BST_ALLOW_INTERNAL, &nodes);
    printf("Printing after insertion (Post Order) (Internal = %u)\n",
                            queue_size(&nodes));
                            
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    
    
    queue_destroy(&nodes);
    queue_init(&nodes, 0);
    avl_inorder(avl_root(&avlTree), BST_ALLOW_INTERNAL, &nodes);
    printf("Printing after insertion (In Order) (Internal = %u)\n",
                            queue_size(&nodes));
                            
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    
    
    pKey = (int *) malloc(sizeof(int));
    *pKey = 88;
    pNode = avl_search_node(&avlTree, (const void *) pKey, avl_root(&avlTree));
    
    opRes = avl_depth(pNode, &depth);
    opRes = avl_height(pNode, &height);
    printf("Depth of %d: %u, Height of %d: %u\n\n", *pKey, depth, *pKey, height);
    free(pKey);
    
    opRes = avl_height(avl_root(&avlTree), &height);
    printf("Height of Root: %u\n\n", height);
    
    pKey = (int *) malloc(sizeof(int));
    *pKey = 77;
    avl_remove(&avlTree, pKey, (void **) &pRemovedKey, 0);
    free(pKey);
    printf("Removed Key addr: %p, Value: %d\n", pRemovedKey, *pRemovedKey);
    free(pRemovedKey);
    printf("Again Removed Key addr: %p, Value: %d\n\n", pRemovedKey, *pRemovedKey);
    
    pKey = (int *) malloc(sizeof(int));
    *pKey = 44;
    avl_remove(&avlTree, pKey, (void **) &pRemovedKey, 0);
    free(pKey);
    printf("Removed Key addr: %p, Value: %d\n", pRemovedKey, *pRemovedKey);
    printf("Again Removed Key addr: %p, Value: %d\n\n", pRemovedKey, *pRemovedKey);
    
    queue_destroy(&nodes);
    queue_init(&nodes, 0);
    avl_levelorder_lr(avl_root(&avlTree), BST_ALLOW_INTERNAL, &nodes);
    printf("Printing after removal (Level LR Order) (Internal = %u)\n",
                            queue_size(&nodes));
                            
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    
    
    queue_destroy(&nodes);
    queue_init(&nodes, 0);
    avl_preorder(avl_root(&avlTree), BST_ALLOW_INTERNAL, &nodes);
    printf("Printing after removal (Pre Order) (Internal = %u)\n",
                            queue_size(&nodes));
                            
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    
    
    queue_destroy(&nodes);
    queue_init(&nodes, 0);
    avl_postorder(avl_root(&avlTree), BST_ALLOW_INTERNAL, &nodes);
    printf("Printing after insertion (Post Order) (Internal = %u)\n",
                            queue_size(&nodes));
                            
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    
    
    queue_destroy(&nodes);
    queue_init(&nodes, 0);
    avl_inorder(avl_root(&avlTree), BST_ALLOW_INTERNAL, &nodes);
    printf("Printing after removal (In Order) (Internal = %u)\n",
                            queue_size(&nodes));
                            
    list = (List *) &nodes;
    elem = list_head(list);
    while (elem != 0) {
        pNode = (BNode *) list_data(elem);
        printf("%d ", *(int *)(pNode->pKey));
        elem = list_next(elem);
    }
    printf("\n\n");
    
    avl_depth(avl_root(&avlTree), &depth);
    avl_height(avl_root(&avlTree), &height);
    printf("Depth of Root: %u, Height of Root: %u\n\n", depth, height);
    
    queue_destroy(&nodes);
    printf("Queue destroyed\n");
    avl_destroy(&avlTree);
    printf("AVL Tree destroyed\n");
    
    return 0;
}


int cmpInt(const void *k1, const void *k2) {
    int *i1 = (int *) k1;
    int *i2 = (int *) k2;
    
    return (*i1 - *i2);
}

