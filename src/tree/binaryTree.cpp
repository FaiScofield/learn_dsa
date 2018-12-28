#include "BinaryTree.h"


bool searchBST(BinaryTree T, int key, BinaryTree parient, BinaryTree* p)
{
    if (!T) {
        *p = parient;
        return false;
    }
    else if (key == T->data) {
        *p = T;
        return true;
    }
    else if (key < T->data)
        return searchBST(T->lChild, key, T, p);
    else
        return searchBST(T->rChild, key, T, p);
}

bool insertBST(BinaryTree* T, int key)
{
    BinaryTree p, s;
    if (!searchBST(*T, key, nullptr, &p)) { // 找不到以key为值的节点才插入
        s = (BinaryTree)malloc(sizeof(BinaryNode));
        s->data = key;
        s->lChild = s->rChild = nullptr;

        if (!p)
            *T = s;
        else if (key < p->data)
            p->lChild = s;
        else
            p->rChild = s;

        return true;
    }
    else
        return false;
}

bool deleteBinaryNode(BinaryTree *p)
{
    if (!*p) {
        std::cerr << "Empty input binary node! \n";
        return false;
    }

    BinaryTree q, s;
    // 待删除节点只有左子树
    if ((*p)->rChild == nullptr) {
        q = *p;     // 防止内存泄露，先让临时指针指向要删除节点的内存，再清楚
        *p = (*p)->lChild;
        free(q);
    }
    // 待删除节点只有右子树
    else if ((*p)->lChild == nullptr) {
        q = *p;
        *p = (*p)->rChild;
        free(q);
    }
    // 待删除节点即有左子树又有右子树
    // 取其左子数中最大子节点(或右子树中最小子节点)的值替换其值
    // 这样就不需要修改它的前驱和后继了
    else {
        q = *p;
        s = (*p)->lChild;
        while (s->rChild != nullptr) {
            q = s;
            s = s->rChild;
        }

        (*p)->data = s->data;
        if (q != *p)
            q->rChild = s->lChild;
        else
            q->lChild = s->lChild;

        free(s);
    }

    return true;
}

bool deleteBST(BinaryTree* T, int key)
{
    if (!*T) {
        std::cerr << "Empty binary tree! \n";
        return false;
    }
    else {
        if (key == (*T)->data)
            return deleteBinaryNode(T);
        else if (key < (*T)->data)
            return deleteBST(&(*T)->lChild, key);
        else
            return deleteBST(&(*T)->rChild, key);
    }

    return true;
}


bool insertAVL(BinaryTree* T, int key, bool* taller)
{
    if (!*T) {
        *T = (BinaryTree)malloc(sizeof(BinaryNode));
        (*T)->data = key;
        (*T)->lChild = (*T)->rChild = nullptr;
        (*T)->bf = 0;
        *taller = true;
    }
    else {
        if (key == (*T)->data) {
            *taller = false;
            return false;
        }
        if (key < (*T)->data) {
            if (!insertAVL(&(*T)->lChild, key, taller))
                return false;
            if (*taller) {
                switch((*T)->bf) {
                    case LH:
                        leftBalance(T);
                        *taller = false;
                        break;
                    case EH:
                        (*T)->bf = LH;
                        *taller = true;
                        break;
                    case RH:
                        (*T)->bf = EH;
                        *taller = false;
                        break;
                }
            }
        }
        else {
            if (!insertAVL(&(*T)->rChild, key, taller))
                return false;
            if (*taller) {
                switch((*T)->bf) {
                case LH:
                    (*T)->bf = EH;
                    *taller = false;
                    break;
                case EH:
                    (*T)->bf = RH;
                    *taller = true;
                    break;
                case RH:
                    rightBalance(T);
                    *taller = false;
                    break;
                default:
                    break;
                }
            }
        }
    }

    return true;
}

void leftBalance(BinaryTree *T)
{
    BinaryTree L, Lr;
    L = (*T)->lChild;

    switch (L->bf) {
    case LH:
        (*T)->bf = L->bf = EH;
        rRotate(T);
        break;
    case RH:
        Lr = L->rChild;
        switch (Lr->bf) {
        case LH:
            (*T)->bf = RH;
            L->bf = EH;
            break;
        case EH:
            (*T)->bf = L->bf = EH;
            break;
        case RH:
            (*T)->bf = EH;
            L->bf = LH;
            break;
        }
        Lr->bf = EH;
        lRotate(&(*T)->lChild);
        rRotate(T);
    }
}

void rightBalance(BinaryTree *T)
{

}

void rRotate(BinaryTree *T)
{
    BinaryTree L;
    L = (*T)->lChild;
    (*T)->lChild = L->lChild;
    L->rChild = *T;
    *T = L;
}

void lRotate(BinaryTree *T)
{
    BinaryTree R;
    R = (*T)->rChild;
    (*T)->rChild = R->rChild;
    R->lChild = *T;
    *T = R;
}
