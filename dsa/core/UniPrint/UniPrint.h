/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#ifndef UNI_PRINT_HPP
#define UNI_PRINT_HPP

#include "../List/List.hpp"
//#include "../Utility.h"
#include "../Vector/Vector.hpp"
#include "print_int_array.h"
//#include "../Queue/Queue.h"
//#include "../Stack/Stack.h"
//#include "../BinTree/BinTree.h" //二叉树
//#include "../Bitmap/Bitmap.h"
//#include "../Graph/Graph.h" // 图
//#include "../Graph/GraphMatrix.h" // 基于邻接矩阵实现的图
//#include "../Huffman/HuffTree.h" //Huffman树
//#include "../BST/BST.h" //二叉搜索树
//#include "../AVL/AVL.h" //AVL树
//#include "../Splay/Splay.h" //伸展树
//#include "../RedBlack/RedBlack.h" //红黑树
//#include "../BTree/BTree.h" //二叉搜索树
//#include "../Entry/Entry.h" //词条
//#include "../Skiplist/Quadlist.h" //四叉表
//#include "../Skiplist/Skiplist.h" //跳转表
//#include "../Hashtable/Hashtable.h" //散列表
//#include "../PQ_List/PQ_List.h" //基于列表实现的优先级队列
//#include "../PQ_ComplHeap/PQ_ComplHeap.h" //基于完全堆实现的优先级队列
//#include "../PQ_LeftHeap/PQ_LeftHeap.h" //基于左式堆实现的优先级队列
//#include "../huffman/huffChar.h" //Huffman超字符

//namespace dsa
//{
//class UniPrint;
//}



namespace dsa
{

using std::cout;
using std::endl;

class UniPrint;

#define print(x) dsa::UniPrint::p(x)
#define PRINT(x) dsa::UniPrint::p(x)

#define ROOT 0
#define L_CHILD 1
#define R_CHILD (-1 * L_CHILD)
// static void print(char* x) { printf(" %s", x ? x : "<NULL>"); }         // 字符串特别处理
// static void print(const char* x) { printf(" %s", x ? x : "<NULL>"); }   // 字符串特别处理


class UniPrint
{
public:
    static void p(int e) { printf("%d", e); }
    static void p(float e) { printf("%.2f", e); }
    static void p(double e) { printf("%.2f", e); }
    static void p(char e) { printf("%c", (31 < e) && (e < 128) ? e : '$'); }
    static void p(const char* s) { s ? printf("%s", s) : printf("<NULL>"); }
    //    static void p(VStatus);  // 图顶点的状态
    //    static void p(EType);    // 图边的类型

    //    static void p(HuffChar&);    // Huffman（超）字符
    //    template <typename K, typename V>
    //    static void p(Entry<K, V>&);  // Entry

    template <typename T>
    static void p(const Vector<T>& V);

    template <typename T>
    static void p(const List<T>& L);

    //    template <typename T>
    //    static void p(const Stack<T>& S);

    //    template <typename T>
    //    static void p(const Queue<T>& Q);

    //    template <typename T>
    //    static void p(const BinNode<T>& node);

    //    template <typename T>
    //    static void p(const BinTree<T>& bt);

    //    template <typename T>
    //    static void p(BST<T>&);

    //    template <typename T>
    //    static void p(AVL<T>&);

    //    template <typename T>
    //    static void p(Splay<T>&);

    //    template <typename T>
    //    static void p(BTree<T>&);

    //    template <typename T>
    //    static void p(RedBlack<T>&);

    //    template <typename T> static void p(Quadlist<T>&); // Quadlist
    //    template <typename K, typename V> static void p(Skiplist<K, V>&); // Skiplist
    //    template <typename K, typename V>
    //    static void p(Hashtable<K, V>&);  // Hashtable
    //    template <typename T> static void p(PQ_List<T>&); // PQ_List
    //    template <typename T> static void p(PQ_ComplHeap<T>&); // PQ_ComplHeap
    //    template <typename T> static void p(PQ_LeftHeap<T>&); // PQ_LeftHeap

    //    template <typename Tv, typename Te>
    //    static void p(GraphMatrix<Tv, Te>& s);
    //    template <typename T> static void p(T& x); // 向量、列表等支持traverse()遍历操作的线性结构
    //    template <typename T> static void p(T* s) // 所有指针
    //    { s ? p(*s) : print("<NULL>"); } // 统一转为引用
};  // UniPrint

// template <class T> static void print(T* x) { x ? UniPrint::p(*x) : printf("<NULL>"); }
// template <class T> static void print(T& x) { UniPrint::p(x); }
// template <class T> static void print(const T& x) { UniPrint::p(x); } // for Stack


// void UniPrint::p(VStatus e)
//{
//    switch (e) {
//    case UNDISCOVERED:
//        printf("U");
//        break;
//    case DISCOVERED:
//        printf("D");
//        break;
//    case VISITED:
//        printf("V");
//        break;
//    default:
//        printf("X");
//        break;
//    }
//}
// void UniPrint::p(EType e)
//{
//    switch (e) {
//    case UNDETERMINED:
//        printf("U");
//        break;
//    case TREE:
//        printf("T");
//        break;
//    case CROSS:
//        printf("C");
//        break;
//    case BACKWARD:
//        printf("B");
//        break;
//    case FORWARD:
//        printf("F");
//        break;
//    default:
//        printf("X");
//        break;
//    }
//}

/******************************************************************************************
 * 基本类型
 ******************************************************************************************/
template <typename T>
void UniPrint::p(const Vector<T>& V)
{
    if (V.empty())
        return;
    for (int i = 0; i < V.size(); ++i)
        cout << V[i] << " ";
    cout << endl;
}

template <typename T>
void UniPrint::p(const List<T>& L)
{
    if (L.empty())
        return;
    for (auto p = L.first(); p != L.last(); p = p->next)
        cout << p->data << " <--> ";
    cout << L.last()->data << endl;
}


//// BinTree节点
// template <typename T>
// void UniPrint::p(const BinNode<T>& node)
//{
//    p(node.data);  // 数值
//    /*
//        // height & NPL
//        #if   defined(DSA_LEFTHEAP)
//        printf("(%-2d)", node.npl); //NPL
//        #elif defined(DSA_BST)
//        printf("(%-2d)", node.height); //高度
//        #elif defined(DSA_AVL)
//        printf("(%-2d)", node.height); //高度
//        #elif defined(DSA_REDBLACK)
//        printf("(%-2d)", node.height); //高度
//        #elif defined(DSA_SPLAY)
//        printf("(%-2d)", node.height); //高度
//        #endif

//        // 父子链接指针
//        printf(
//            ( (node.lc && &node != node.lc->parent) ||
//            (node.rc && &node != node.rc->parent) ) ?
//            "@" : " "
//        );

//        // 节点颜色
//        #if defined(DSA_REDBLACK)
//        printf(node.color == RB_BLACK ? "B" : "R"); //
//        #endif

//        // 父子（黑）高度、NPL匹配
//        #if defined(DSA_PQ_COMPLHEAP)
//        // 高度不必匹配
//        #elif defined(DSA_PQ_LEFTHEAP)
//        printf(//NPL
//        (node.rc && node.npl != 1 + node.rc->npl) ||
//        (node.lc && node.npl >  1 + node.lc->npl) ?
//        "%%" : " "
//        );
//        #elif defined(DSA_REDBLACK)
//        printf(BlackHeightUpdated (node) ? " " : "!"); //黑高度
//        #else
//        printf(HeightUpdated (node) ? " " : "!"); //（常规）高度
//        #endif

//        // 左右平衡
//        #if defined(DSA_AVL)
//        if (!AvlBalanced (node)) printf("X"); //AVL平衡
//        else if (0 < BalFac (node)) printf("\\"); //AVL平衡
//        else if (BalFac (node) < 0) printf("/"); //AVL平衡
//        else printf("-"); //AVL平衡
//        #elif defined(DSA_REDBLACK)
//        if (!Balanced (node)) printf("X"); //RB平衡
//        else if (0 < BalFac (node)) printf("\\"); //RB平衡
//        else if (BalFac (node) < 0) printf("/"); //RB平衡
//        else printf("-"); //RB平衡
//        #else
//        // 平衡无所谓
//        #endif
//    */
//}


///******************************************************************************************
// * 二叉树输出打印
// ******************************************************************************************/
// template <typename T>
// void UniPrint::p(const BinTree<T>& bt)
//{
//    if (!bt.size())
//        return;
//    printf("%s[%p]*size:%d:\n", typeid(bt).name(), &bt, bt.size());  // 基本信息
//    Bitmap* branchType = new Bitmap;                // 记录当前节点祖先的方向
//    printBinTree(bt.root(), -1, ROOT, branchType);  // 树状结构
//    delete branchType;
//    printf("\n");
//}


///******************************************************************************************
// * 基于BinTree实现的BST
// ******************************************************************************************/
// template <typename T>
// void UniPrint::p(BST<T>& bt)
//{  // 引用
//    if (!bt.size())
//        return;
//    printf("%s[%p]*%d:\n", typeid(bt).name(), &bt, bt.size());  // 基本信息
//    Bitmap* branchType = new Bitmap;                            // 记录当前节点祖先的方向
//    printBinTree(bt.root(), -1, ROOT, branchType);              // 树状结构
//    delete branchType;
//    printf("\n");
//}


///******************************************************************************************
// * 基于BST实现的AVL
// * 其中调用的BinNode的打印例程，可以显示BF状态
// ******************************************************************************************/
// template <typename T>
// void UniPrint::p(AVL<T>& avl)
//{                                                                  // 引用
//    printf("%s[%p]*%d:\n", typeid(avl).name(), &avl, avl.size());  // 基本信息
//    Bitmap* branchType = new Bitmap;                 // 记录当前节点祖先的方向
//    printBinTree(avl.root(), -1, ROOT, branchType);  // 树状结构
//    delete branchType;
//    printf("\n");
//}

///******************************************************************************************
// * 基于BST实现的RedBlack
// * 其中调用的BinNode的打印例程，可以显示BF状态
// ******************************************************************************************/
// template <typename T>
// void UniPrint::p(RedBlack<T>& rb)
//{                                                               // 引用
//    printf("%s[%p]*%d:\n", typeid(rb).name(), &rb, rb.size());  // 基本信息
//    Bitmap* branchType = new Bitmap;                            // 记录当前节点祖先的方向
//    printBinTree(rb.root(), -1, ROOT, branchType);              // 树状结构
//    delete branchType;
//    printf("\n");
//}

///******************************************************************************************
// * 基于BST实现的Splay
// * 鉴于Splay不必设置bf之类的附加标识，其打印例程与BST完全一致
// ******************************************************************************************/
// template <typename T>
// void UniPrint::p(Splay<T>& bt)
//{                                                               // 引用
//    printf("%s[%p]*%d:\n", typeid(bt).name(), &bt, bt.size());  // 基本信息
//    Bitmap* branchType = new Bitmap;                            // 记录当前节点祖先的方向
//    printBinTree(bt.root(), -1, ROOT, branchType);              // 树状结构
//    delete branchType;
//    printf("\n");
//}

///******************************************************************************************
// * BTree打印（入口）
// ******************************************************************************************/
// template <typename T>
// void UniPrint::p(BTree<T>& bt)
//{                                                               // 引用
//    printf("%s[%p]*%d:\n", typeid(bt).name(), &bt, bt.size());  // 基本信息
//    Bitmap* leftmosts = new Bitmap;                             // 记录当前节点祖先的方向
//    Bitmap* rightmosts = new Bitmap;                            // 记录当前节点祖先的方向
//    printBTree(bt.root(), 0, true, true, leftmosts, rightmosts);  // 输出树状结构
//    delete leftmosts;
//    delete rightmosts;
//    printf("\n");
//}


///******************************************************************************************
// * Entry
// ******************************************************************************************/
// template <typename K, typename V>
// void UniPrint::p(Entry<K, V>& e)
//{
//    printf("-<");
//    print(e.key);
//    printf(":");
//    print(e.value);
//    printf(">-");
//}


///******************************************************************************************
// * Hashtable
// ******************************************************************************************/
// template <typename K, typename V>
// void UniPrint::p(Hashtable<K, V>& ht)
//{
//    printf("%s[%p]*%d/%d:\n", typeid(ht).name(), &ht, ht.N, ht.M);  // 基本信息
//    for (int i = 0; i < ht.M; i++)                                  // 输出桶编号
//        printf("  %4d  ", i);
//    printf("\n");
//    for (int i = 0; i < ht.M; i++)  // 输出所有元素
//        if (ht.ht[i])
//            printf("-<%04d>-", ht.ht[i]->key);  // 演示用，仅适用于int
//        else if (ht.lazyRemoval->test(i))
//            printf("-<xxxx>-");
//        else
//            printf("--------");
//    printf("\n");
//    for (int i = 0; i < ht.M; i++)  // 输出所有元素
//        if (ht.ht[i])
//            printf("    %c   ", ht.ht[i]->value);  // 演示用，仅适用于char
//        //        if (ht.ht[i]) printf("%8s", ht.ht[i]->value); // 针对Huffman编码中使用的散列表
//        else if (ht.lazyRemoval->test(i))
//            printf(" <xxxx> ");
//        else
//            printf("        ");
//    printf("\n");
//}


///******************************************************************************************
// * 图Graph
// ******************************************************************************************/
// template <typename Tv, typename Te>  // 顶点类型、边类型
// void UniPrint::p(GraphMatrix<Tv, Te>& g)
//{
//    int inD = 0, outD = 0;
//    for (int i = 0; i < g.n; i++)
//        inD += g.inDegree(i);
//    for (int i = 0; i < g.n; i++)
//        outD += g.outDegree(i);
//    // 基本信息
//    printf("%s[%p]*(%d, %d):\n", typeid(g).name(), &g, g.n, g.e);
//    // 标题行
//    printf("%3d %3d |  ", g.n, inD);
//    for (int i = 0; i < g.n; i++) {
//        print(g.vertex(i));
//        printf("[");
//        print(g.status(i));
//        printf("]\t");
//    }
//    printf("\n");
//    // 标题行（续）
//    printf("%3d %3d |  ", outD, g.e);
//    for (int i = 0; i < g.n; i++) {
//        print(g.inDegree(i));
//        printf(" \t");
//    }
//    printf("| dTime fTime Parent Weight\n");

//    // 水平分隔线
//    printf("--------+--");
//    for (int i = 0; i < g.n; i++)
//        printf("-----------");
//    printf("-+--------------------------\n");

//    // 逐行输出各顶点
//    for (int i = 0; i < g.n; i++) {
//        print(g.vertex(i));
//        printf("[");
//        print(g.status(i));
//        printf("] ");
//        print(g.outDegree(i));
//        printf("  |  ");
//        for (int j = 0; j < g.n; j++)
//            if (g.exists(i, j)) {
//                print(g.edge(i, j));
//                print(g.type(i, j));
//                printf("\t");
//            } else
//                printf(".\t");
//        printf("|   ");
//        print(g.dTime(i));
//        printf("    ");
//        print(g.fTime(i));
//        printf("     ");
//        if (0 > g.parent(i))
//            print("^  ");
//        else
//            print(g.vertex(g.parent(i)));
//        printf(" ");
//        if (WINT_MAX > g.priority(i))
//            print(g.priority(i));
//        else
//            print(" INF");
//        printf("\n");
//    }
//    printf("\n");
//}


///******************************************************************************************
// * 二叉树各种派生类的统一打印
// ******************************************************************************************/
// template <typename T>
// static void printBinTree(BinNodePosi(T) bt, int depth, int type, Bitmap* bType)
//{
//    if (!bt)
//        return;
//    if (-1 < depth)  // 设置当前层的拐向标志
//        R_CHILD == type ? bType->set(depth) : bType->clear(depth);
//    printBinTree(bt->rc, depth + 1, R_CHILD, bType);  // 右子树（在上）
//    print(*bt);
//    printf("\t*");
//    for (int i = -1; i < depth; ++i)  // 根据相邻各层
//        if ((0 > i) || bType->test(i) == bType->test(i + 1))  // 的拐向是否一致，即可确定是否应该打印横线
//            printf("   ");
//        else
//            printf("│  ");
//    switch (type) {
//    case R_CHILD:
//        printf("┌─ ");
//        break;
//    case L_CHILD:
//        printf("└─ ");
//        break;
//    default:
//        printf("── ");
//        break;  // root
//    }
//    print(*bt);
//    //#if defined(DSA_HUFFMAN)
//    //    if (IsLeaf (*bt)) bType->print(depth + 1); //输出Huffman编码
//    //#endif
//    printf("\n");
//    printBinTree(bt->lc, depth + 1, L_CHILD, bType);  // 左子树（在下）
//}


///******************************************************************************************
// * BTree打印（递归）
// ******************************************************************************************/
// template <typename T>
// static void printBTree(BTNodePosi(T) bt, int depth, bool isLeftmost, bool isRightmost,
//                       Bitmap* leftmosts, Bitmap* rightmosts)
//{
//    if (!bt)
//        return;
//    isLeftmost ? leftmosts->set(depth) : leftmosts->clear(depth);  // 设置或清除当前层的拐向标志
//    isRightmost ? rightmosts->set(depth) : rightmosts->clear(depth);  // 设置或清除当前层的拐向标志
//    int k = bt->child.size() - 1;  // 找到当前节点的最右侧孩子，并
//    printBTree(bt->child[k], depth + 1, false, true, leftmosts, rightmosts);  // 递归输出之
//    bool parentOK = false;
//    BTNodePosi(T) p = bt->parent;
//    if (!p)
//        parentOK = true;
//    else
//        for (int i = 0; i < p->child.size(); i++)
//            if (p->child[i] == bt)
//                parentOK = true;
//    while (0 < k--) {  // 自右向左，输出各子树及其右侧的关键码
//        printf(parentOK ? " " : "X");
//        print(bt->key[k]);
//        printf("\t*>");
//        for (int i = 0; i < depth; i++)  // 根据相邻各层
//            (leftmosts->test(i) && leftmosts->test(i + 1) ||
//             rightmosts->test(i) && rightmosts->test(i + 1)) ?  // 的拐向是否一致，即可确定
//                printf("     ") :
//                printf("│    ");  // 是否应该打印横向联接线
//        if (((0 == depth && 1 < bt->key.size()) || !isLeftmost && isRightmost) && bt->key.size() - 1 == k)
//            printf("┌─");
//        else if (((0 == depth && 1 < bt->key.size()) || isLeftmost && !isRightmost) && 0 == k)
//            printf("└─");
//        else
//            printf("├─");
//        print(bt->key[k]);
//        printf("\n");
//        printBTree(bt->child[k], depth + 1, 0 == k, false, leftmosts, rightmosts);  // 递归输出子树
//    }
//}

}  // namespace dsa




#endif  // UNI_PRINT_HPP
