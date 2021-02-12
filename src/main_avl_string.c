


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "avl.h"
#include <queue.h>



int cmp_str(const void *k1, const void *k2);

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(void) {
    
    AvlTree aTree;
    List lString;
    ListElem *pListElem;
    char sInput[2048], *pChar;
    unsigned int itr, iTotal;
    
    printf("AVL Tree with String Keys test program.\n");
    printf("Input how many strings you want to insert: ");
    gets(sInput);
    sscanf(sInput, "%u", &iTotal);
    
    list_init(&lString, free);
    avl_init(&aTree, cmp_str, 0, 0);
    
    for (itr = 0; itr < iTotal; itr += 1) {
        printf("Enter line %u\n", itr + 1);
        gets(sInput);
        pChar = (char *) malloc(strlen(sInput) + 1);
        strcpy(pChar, (const char *) sInput);
        avl_insert(&aTree, (const void *) pChar, 0);
    }
    
    avl_keys(&aTree, &lString);
    
    printf("Printing contents of AVL Tree\n");
    pListElem = list_head(&lString);
    PRINT_STRING_LIST:
    if (pListElem != 0) {
        pChar = (char *) list_data(pListElem);
        printf("%s\n", pChar);
        pListElem = list_next(pListElem);
        goto PRINT_STRING_LIST;
    }
    
    avl_destroy(&aTree);
    list_destroy(&lString);
    
    return 0;
}


int cmp_str(const void *k1, const void *k2) {
    const char *str1, *str2;
    str1 = (const char *) k1;
    str2 = (const char *) k2;
    return lstrcmpiA(str1, str2);
}

