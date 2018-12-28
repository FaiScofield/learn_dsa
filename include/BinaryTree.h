#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

enum {
    LH = -1,
    RH = +1,
    EH = 0
};

struct BinaryNode
{
    int data;
    int bf; // for Averange Tree

    BinaryNode *lChild, *rChild;
};

typedef BinaryNode *BinaryTree;


bool deleteBinaryNode(BinaryNode *p);

// BST
bool searchBST(BinaryTree T, int key, BinaryTree parient, BinaryTree *p);
bool insertBST(BinaryTree *T, int key);
bool deleteBST(BinaryTree *T, int key);

// AVL
bool insertAVL(BinaryTree *T, int key, bool *taller);
void leftBalance(BinaryTree *T);
void rightBalance(BinaryTree *T);
void rRotate(BinaryTree *T);
void lRotate(BinaryTree *T);


#endif
