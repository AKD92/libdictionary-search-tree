

/************************************************************************************
    Implementation of AVL Tree Restructuring Algorithms
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/








#include "avl.h"
#include "avl_internal.h"







BNode * avl_restructure(AvlTree *tree, BNode *pNodeX) {
    
    int isLeftOfZ;
    BNode *pParentZ;
    BNode *pNodeY, *pNodeZ;
    BNode *pNodeA, *pNodeB, *pNodeC;
    BNode *pNodeT0, *pNodeT1, *pNodeT2, *pNodeT3;
    
    pNodeY = avl_parent(pNodeX);
    pNodeZ = avl_parent(pNodeY);
    pParentZ = avl_parent(pNodeZ);
    
    if (avl_leftchild(pParentZ) == pNodeZ) {
        isLeftOfZ = 1;
    }
    else {
        isLeftOfZ = 0;
    }
    
    if (avl_rightchild(pNodeZ) == pNodeY) {
        pNodeA = pNodeZ;
        if (avl_rightchild(pNodeY) == pNodeX) {
            pNodeB = pNodeY;
            pNodeC = pNodeX;
            pNodeT1 = avl_leftchild(pNodeB);
            pNodeT2 = avl_leftchild(pNodeC);
        }
        else if (avl_leftchild(pNodeY) == pNodeX){
            pNodeB = pNodeX;
            pNodeC = pNodeY;
            pNodeT1 = avl_leftchild(pNodeB);
            pNodeT2 = avl_rightchild(pNodeB);
        }
        else {
            return 0;
        }
    }
    else if (avl_leftchild(pNodeZ) == pNodeY) {
        pNodeC = pNodeZ;
        if (avl_leftchild(pNodeY) == pNodeX) {
            pNodeB = pNodeY;
            pNodeA = pNodeX;
            pNodeT1 = avl_rightchild(pNodeA);
            pNodeT2 = avl_rightchild(pNodeB);
        }
        else if (avl_rightchild(pNodeY) == pNodeX) {
            pNodeB = pNodeX;
            pNodeA = pNodeY;
            pNodeT1 = avl_leftchild(pNodeB);
            pNodeT2 = avl_rightchild(pNodeB);
        }
    }
    else {
        return 0;
    }
    
    pNodeT0 = avl_leftchild(pNodeA);
    pNodeT3 = avl_rightchild(pNodeC);
    
    
    pNodeA->pLeftNode = pNodeT0;
    pNodeA->pRightNode = pNodeT1;
    pNodeT0->pParentNode = pNodeA;
    pNodeT1->pParentNode = pNodeA;
    
    pNodeC->pLeftNode = pNodeT2;
    pNodeC->pRightNode = pNodeT3;
    pNodeT2->pParentNode = pNodeC;
    pNodeT3->pParentNode = pNodeC;
    
    pNodeB->pLeftNode = pNodeA;
    pNodeB->pRightNode = pNodeC;
    pNodeA->pParentNode = pNodeB;
    pNodeC->pParentNode = pNodeB;
    
    pNodeB->pParentNode = pParentZ;
    
    if (pParentZ == 0) {
        tree->pRootNode = pNodeB;
    }
    else {
        if (isLeftOfZ == 1) {
            pParentZ->pLeftNode = pNodeB;
        }
        else if (isLeftOfZ == 0) {
            pParentZ->pRightNode = pNodeB;
        }
    }
    
    return pNodeB;
}



BNode * avl_findUnbalancedNodeX(AvlTree *tree, BNode *pNode, int operationType) {
    
    BNode *pN;
    BNode *pZ, *pY, *pX;
    unsigned int heightL, heightR;
    int iDiff;
    int isAncestor;
    
    pN = pNode;
    pZ = pY = pX = 0;
    
    while (pN != 0) {
            
        avl_height((const BNode *) avl_leftchild(pN), &heightL);
        avl_height((const BNode *) avl_rightchild(pN), &heightR);
        iDiff = (int ) (heightL - heightR);
        
        if (iDiff < 0)
            iDiff = iDiff * (-1);
            
        if (iDiff >= 2) {
            pZ = pN;
            if (heightL > heightR) {
                pY = avl_leftchild(pZ);
            }
            else {
                pY = avl_rightchild(pZ);
            }
            break;
        }
        pN = avl_parent(pN);
    }
    
    if (pY != 0) {
        
        avl_height((const BNode *) avl_leftchild(pY), &heightL);
        avl_height((const BNode *) avl_rightchild(pY), &heightR);
        
        if (heightL > heightR) {
            pX = avl_leftchild(pY);
        }
        else if (heightR > heightL) {
            pX = avl_rightchild(pY);
        }
        else if (heightL == heightR) {
            switch (operationType) {
                case AVL_INSERTION:
                    isAncestor = avl_is_ancestor(tree, avl_leftchild(pY), pNode);
                    if (isAncestor == 1) {
                        pX = avl_leftchild(pY);
                    }
                    else {
                        pX = avl_rightchild(pY);
                    }
                    break;
                
                case AVL_REMOVAL:
                    pX = avl_rightchild(pY);
                    break;
            }
        }
    }
    
    return pX;
}


