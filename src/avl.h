

/************************************************************************************
    Program Interface for AVL Tree based Dictionary ADT
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef AVL_TREE_DATA_STRUCTURE_H
#define AVL_TREE_DATA_STRUCTURE_H






#define AVL_INSERTION           1
#define AVL_REMOVAL             2




#include "bst.h"






/**********************************************************************************************/
/***********************************                       ************************************/
/***********************************    DATA STRUCTURES    ************************************/
/***********************************                       ************************************/
/**********************************************************************************************/


typedef BisTree AvlTree;







/**********************************************************************************************/
/***********************************                       ************************************/
/***********************************   PUBLIC INTERFACES   ************************************/
/***********************************                       ************************************/
/**********************************************************************************************/



#define     avl_size                bst_size

#define     avl_init                bst_init

#define     avl_destroy             bst_destroy

#define     avl_root                bst_root

#define     avl_parent              bst_parent

#define     avl_leftChild           bst_leftChild

#define     avl_rightChild          bst_rightChild

#define     avl_sibling             bst_sibling

#define     avl_isExternal          bst_isExternal

#define     avl_isInternal          bst_isInternal

#define     avl_isRoot              bst_isRoot

#define     avl_isAncestor          bst_isAncestor

#define     avl_depth               bst_depth

#define     avl_height              bst_height



#define     avl_preOrder            bst_preOrder

#define     avl_inOrder             bst_inOrder

#define     avl_postOrder           bst_postOrder

#define     avl_levelOrderLR        bst_levelOrderLR

#define     avl_levelOrderRL        bst_levelOrderRL

#define     avl_eraseExternalLinks  bst_eraseExternalLinks



#define     avl_searchNode          bst_searchNode

#define     avl_search              bst_search



int avl_insert(AvlTree *pTree, const void *pKey, const void *pElem);


int avl_remove(AvlTree *pTree, const void *pKey, void **pRemovedKey, void **pRemovedElem);



#define     avl_changeElement       bst_changeElement



#define     avl_listKeys            bst_listKeys

#define     avl_listElements        bst_listElements

#define     avl_listKeysElements    bst_listKeysElements






#endif


