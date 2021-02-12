

#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <dlist.h>
#include "avl.h"




static int cmpInt(const void *arg1, const void *arg2);


int main(void) {
    
    DList numList;
    DListElem *elem;
    int *pElem;
    unsigned int iTotal, i;
    
    dlist_init(&numList, free);
    
    printf("Enter total integers to input:\n");
    scanf("%u", &iTotal);
    
    printf("Enter each number:");
    for (i = 0; i < iTotal; i++) {
        pElem = (int *) malloc(sizeof(int));
        scanf("%d", pElem);
        dlist_ins_next(&numList, dlist_tail(&numList), (const void *) pElem);
    }
    printf("\n\n");
    
    printf("Printing integers from Linked List (Size: %u)\n", list_size(&numList));
    elem = dlist_head(&numList);
    while (elem != 0) {
        pElem = (int *) dlist_data(elem);
        printf("%d (%p): ", *pElem, pElem);
        elem = dlist_next(elem);
    }
    printf("\n\n");
    
    printf("Applying TreeSort Algorithm to Linked List\n");
    avl_treesort_desc_dl(&numList, cmpInt);
    
    printf("Printing After Sorting Integers (Size: %u)\n", list_size(&numList));
    elem = dlist_head(&numList);
    while (elem != 0) {
        pElem = (int *) dlist_data(elem);
        printf("%d (%p): ", *pElem, pElem);
        elem = dlist_next(elem);
    }
    printf("\n\n");
    
    dlist_destroy(&numList);
    
    return 0;
}




static int cmpInt(const void *arg1, const void *arg2) {
    
    int *a, *b;
    
    a = (int *) arg1;
    b = (int *) arg2;
    return (*a - *b);
}
