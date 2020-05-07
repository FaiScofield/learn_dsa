/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#include <iostream>
using namespace std;

#include "../_share/util.h"
#include "../UniPrint/print.h"
#include "BinTree.h"

int testID = 0; //测试编号

//template <typename S> void visit(const S& e) { std::cout << e << " "; }
typedef void(*VST)(int);// 声明指针函数VST
void show(int in) { printf("%d ", in); }

// 随机生成期望高度为h的二叉排序树(BST)
template <typename T> void randomBinTree(BinTree<T>& bt, int h) {
    if (h <= 0) return;

    int s = 0.8 * (pow(2, h) - 1); // a h-level tree with 80% full
    while (s-- > 1 && bt.root()->height < h) {
        BinNodePosi(T) x = bt.root();
        T v = dice((T) h*h*h);
        while (v < x->data && x->lc) x = x->lc;
        while (v > x->data && x->rc) x = x->rc;
        if (!x->lc && v < x->data) { bt.insertAsLC(x, v); continue; }
        if (!x->rc && v > x->data) { bt.insertAsRC(x, v); continue; }
    }
}

// 在二叉树中随机确定一个节点位置
template <typename T> BinNodePosi(T) randomPosiInBinTree(BinNodePosi(T) root) {
    if(!HasChild(*root)) return root;
    if(!HasLChild(*root))
        return dice(2) ? randomPosiInBinTree(root->rc) : root;
    if(!HasRChild(*root))
        return dice(2) ? randomPosiInBinTree(root->lc) : root;
    switch(dice(3)) {
        case 0: return randomPosiInBinTree(root->lc);
        case 1: return randomPosiInBinTree(root->rc);
        default: return root;
    }
}

// 测试二叉树
template <typename T> void testBinTree(int h) {
    printf("\n  ==== Test %2d. Generate a binTree of height <= %d \n", testID++, h);
    BinTree<T> bt;
    bt.insertAsRoot(dice((T) h*h*h));
    randomBinTree<T>(bt, h); print(bt);

    printf("\n  ==== Test %2d. Double and increase all nodes by traversal\n", testID++);
    Double<T> doub; Increase<T> incre;
    bt.travPre(doub); bt.travPre(incre); print(bt);

    VST p = show;
    printf("\n  ==== Test %2d. Travel (level order) the Tree \n", testID++);
    bt.travLevel(p); printf("\n");

    printf("\n  ==== Test %2d. Travel (preorder) the Tree \n", testID++);
    bt.travPre(p); printf("\n");

    printf("\n  ==== Test %2d. Travel (inorder) the Tree \n", testID++);
    bt.travIn(p); printf("\n");

    printf("\n  ==== Test %2d. Travel (postorder) the Tree \n", testID++);
    bt.travPost(p); printf("\n");

    printf("\n  ==== Test %2d. Compair two trees\n", testID++);
    BinTree<T> bt2;
    bt2.insertAsRoot(dice((T) h*h*h));
    randomBinTree<T>(bt2, h); print(bt2);
    printf("\nTree 1 ");
    if (bt > bt2) printf(">");
    else if (bt == bt2) printf("=");
    else printf("<");
    printf(" Tree 2 \n");

    printf("\n  ==== Test %2d. Zig the Tree \n", testID++);
    BinNodePosi(T) center = randomPosiInBinTree(bt.root());
    printf(" the rotation center is "); print(center->data); printf(" \n");
    print(bt); center->zig(); print(bt);

    printf("\n  ==== Test %2d. Zag the Tree \n", testID++);
    printf(" the rotation center is "); print(center->data); printf(" \n");
    print(bt); center->zag(); print(bt);

    printf("\n  ==== Test %2d. Remove/release subtrees in the Tree\n", testID++);
    while(bt.size() && !bt.empty() ) {
        BinNodePosi(T) p = randomPosiInBinTree(bt.root()); // 随机选择一个节点
        if(dice(2)) {
            printf("removing "); print(p->data); printf(" ...\n");
            printf("%d node(s) removed\n", bt.remove(p)); print(bt);
        } else {
            printf("releasing "); print(p->data); printf(" ...\n");
            BinTree<T>* S = bt.secede(p); print(*S);
            printf("%d node(s) released\n", S->size());
            delete(S); S = nullptr; print(bt);
        }
    }

}

// 测试二叉树
int main(int argc, char* argv[]) {
    if(2 > argc) {
        printf( "Usage: %s <size of test>\a\a\n", argv[0]);
        return 1;
    }
    srand(( unsigned int) time(NULL));

    testBinTree<int>(atoi(argv[1]));

    return 0;
}

