

/************************************************************************************
    Internal Program Interface for AVL Tree based Dictionary ADT
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef AVL_INTERNAL_H_INCLUDED
#define AVL_INTERNAL_H_INCLUDED




#include "avl.h"
#include "bst_internal.h"





#define AVL_INSERTION               1
#define AVL_REMOVAL                 2





#define     avl_root                bst_root

#define     avl_parent              bst_parent

#define     avl_leftchild           bst_leftchild

#define     avl_rightchild          bst_rightchild

#define     avl_sibling             bst_sibling

#define     avl_is_external         bst_is_external

#define     avl_is_internal         bst_is_internal

#define     avl_is_root             bst_is_root

#define     avl_is_ancestor         bst_is_ancestor

#define     avl_depth               bst_depth

#define     avl_height              bst_height



#define     avl_preorder            bst_preorder

#define     avl_inorder             bst_inorder

#define     avl_reverse_inorder     bst_reverse_inorder

#define     avl_postorder           bst_postorder

#define     avl_levelorder_lr       bst_levelorder_lr

#define     avl_levelorder_rl       bst_levelorder_rl


#define     avl_search_node         bst_search_node



BNode * avl_restructure(AvlTree *tree, BNode *pNodeX);

BNode * avl_findUnbalancedNodeX(AvlTree *tree, BNode *pNode, int operationType);




#endif

