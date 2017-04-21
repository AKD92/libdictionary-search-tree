

/************************************************************************************
    Implementation of AVL Tree Restructuring Algorithms
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/








#include "avl.h"






BNode * avl_reStructure(AvlTree *tree, BNode *pNodeX);

BNode * avl_findUnbalancedNodeX(AvlTree *tree, BNode *pNode, int operationType);







BNode * avl_reStructure(AvlTree *tree, BNode *pNodeX) {
    
    int isLeftOfZ;
    BNode *pParentZ;
    BNode *pNodeY, *pNodeZ;
    BNode *pNodeA, *pNodeB, *pNodeC;
    BNode *pNodeT0, *pNodeT1, *pNodeT2, *pNodeT3;
    
    pNodeY = avl_parent(pNodeX);
    pNodeZ = avl_parent(pNodeY);
    pParentZ = avl_parent(pNodeZ);
    
    if (avl_leftChild(pParentZ) == pNodeZ) {
        isLeftOfZ = 1;
    }
    else {
        isLeftOfZ = 0;
    }
    
    if (avl_rightChild(pNodeZ) == pNodeY) {
        pNodeA = pNodeZ;
        if (avl_rightChild(pNodeY) == pNodeX) {
            pNodeB = pNodeY;
            pNodeC = pNodeX;
            pNodeT1 = avl_leftChild(pNodeB);
            pNodeT2 = avl_leftChild(pNodeC);
        }
        else if (avl_leftChild(pNodeY) == pNodeX){
            pNodeB = pNodeX;
            pNodeC = pNodeY;
            pNodeT1 = avl_leftChild(pNodeB);
            pNodeT2 = avl_rightChild(pNodeB);
        }
        else {
            return 0;
        }
    }
    else if (avl_leftChild(pNodeZ) == pNodeY) {
        pNodeC = pNodeZ;
        if (avl_leftChild(pNodeY) == pNodeX) {
            pNodeB = pNodeY;
            pNodeA = pNodeX;
            pNodeT1 = avl_rightChild(pNodeA);
            pNodeT2 = avl_rightChild(pNodeB);
        }
        else if (avl_rightChild(pNodeY) == pNodeX) {
            pNodeB = pNodeX;
            pNodeA = pNodeY;
            pNodeT1 = avl_leftChild(pNodeB);
            pNodeT2 = avl_rightChild(pNodeB);
        }
    }
    else {
        return 0;
    }
    
    pNodeT0 = avl_leftChild(pNodeA);
    pNodeT3 = avl_rightChild(pNodeC);
    
    
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
        heightL = avl_height((const AvlTree *) tree, (const BNode *) avl_leftChild(pN));
        heightR = avl_height((const AvlTree *) tree, (const BNode *) avl_rightChild(pN));
        iDiff = (int ) (heightL - heightR);
        if (iDiff < 0)
            iDiff = iDiff * (-1);
        if (iDiff >= 2) {
            pZ = pN;
            if (heightL > heightR) {
                pY = avl_leftChild(pZ);
            }
            else {
                pY = avl_rightChild(pZ);
            }
            break;
        }
        pN = avl_parent(pN);
    }
    
    if (pY != 0) {
        heightL = avl_height((const AvlTree *) tree, (const BNode *) avl_leftChild(pY));
        heightR = avl_height((const AvlTree *) tree, (const BNode *) avl_rightChild(pY));
        if (heightL > heightR) {
            pX = avl_leftChild(pY);
        }
        else if (heightR > heightL) {
            pX = avl_rightChild(pY);
        }
        else if (heightL == heightR) {
            switch (operationType) {
                case AVL_INSERTION:
                isAncestor = avl_isAncestor(tree, pNode, avl_leftChild(pY));
                if (isAncestor == 1) {
                    pX = avl_leftChild(pY);
                }
                else {
                    pX = avl_rightChild(pY);
                }
                break;
                
                case AVL_REMOVAL:
                pX = avl_rightChild(pY);
                break;
            }
        }
    }
    
    return pX;
}


