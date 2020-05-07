#include "UniPrint.h"

/******************************************************************************************
 * 基本类型
 ******************************************************************************************/
//template <typename T>
//void UniPrint::p(const Vector<T>& V)
//{
//    if (V.empty())
//        return;
//    for (int i = 0; i < V.size(); ++i)
//        cout << V[i] << " ";
//    cout << endl;
//}

//template <typename T>
//void UniPrint::p(const List<T>& L)
//{
//    if (L.empty())
//        return;
//    for (auto p = L.first(); p != L.last(); p = p->succ)
//        cout << p->data << " <--> ";
//    cout << L.last()->data << endl;
//}

// template <typename T>
// void UniPrint::p(const Stack<T>& S)
//{
//    if (S.empty())
//        return;
//    for (int i = 0; i < S.size(); ++i)
//        cout << S[i] << " ";
//    cout << endl;
//}

// template <typename T>
// void UniPrint::p(const Queue<T>& Q)
//{
//    if (Q.empty())
//        return;
//    for (auto p = Q.first(); p != Q.last(); p = p->succ)
//        cout << p->data << " <--> ";
//    cout << Q.last()->data << endl;
//}

// void UniPrint::p(VStatus e) {
//    switch (e) {
//        case UNDISCOVERED:   printf("U"); break;
//        case DISCOVERED:     printf("D"); break;
//        case VISITED:        printf("V"); break;
//        default:             printf("X"); break;
//    }
//}
// void UniPrint::p(EType e) {
//    switch (e) {
//        case UNDETERMINED:   printf("U"); break;
//        case TREE:           printf("T"); break;
//        case CROSS:          printf("C"); break;
//        case BACKWARD:       printf("B"); break;
//        case FORWARD:        printf("F"); break;
//        default:             printf("X"); break;
//    }
//}


/****************************************************************************************
 * BinTree节点
 ****************************************************************************************/
//template <typename T>
//void UniPrint::p(BinNode<T>& node)
//{
//    p(node.data);  //数值
//    /**************************************************************************************
//     * height & NPL
//     *************************************************************************************/
//#if defined(DSA_LEFTHEAP)
//    printf("(%-2d)", node.npl);  // NPL
//#elif defined(DSA_BST)
//    printf("(%-2d)", node.height);  //高度
//#elif defined(DSA_AVL)
//    printf("(%-2d)", node.height);                 //高度
//#elif defined(DSA_REDBLACK)
//    printf("(%-2d)", node.height);            //高度
//#elif defined(DSA_SPLAY)
//    printf("(%-2d)", node.height);  //高度
//#endif
//    /******************************************************************************************
//     * 父子链接指针
//     ******************************************************************************************/
//    printf(((node.lc && &node != node.lc->parent) || (node.rc && &node != node.rc->parent)) ? "@" : " ");
//    /******************************************************************************************
//     * 节点颜色
//     ******************************************************************************************/
//#if defined(DSA_REDBLACK)
//    printf(node.color == RB_BLACK ? "B" : " ");  //（忽略红节点）
//#endif
//    /******************************************************************************************
//     * 父子（黑）高度、NPL匹配
//     ******************************************************************************************/
//#if defined(DSA_PQ_COMPLHEAP)
//    //高度不必匹配
//#elif defined(DSA_PQ_LEFTHEAP)
//    printf(                         // NPL
//        (node.rc && node.npl != 1 + node.rc->npl) || (node.lc && node.npl > 1 + node.lc->npl) ?
//            "%%" :
//            " ");
//#elif defined(DSA_REDBLACK)
//    printf(BlackHeightUpdated(node) ? " " : "!");  //黑高度
//#else
//    printf(HeightUpdated(node) ? " " : "!");  //（常规）高度
//#endif
//    /******************************************************************************************
//     * 左右平衡
//     ******************************************************************************************/
//#if defined(DSA_AVL)
//    if (!AvlBalanced(node))
//        printf("X");  // AVL平衡
//    else if (0 < BalFac(node))
//        printf("\\");  // AVL平衡
//    else if (BalFac(node) < 0)
//        printf("/");  // AVL平衡
//    else
//        printf("-");  // AVL平衡
//#elif defined(DSA_REDBLACK)
//    if (!Balanced(node))
//        printf("X");  // RB平衡
//    else if (0 < BalFac(node))
//        printf("\\");  // RB平衡
//    else if (BalFac(node) < 0)
//        printf("/");  // RB平衡
//    else
//        printf("-");  // RB平衡
//#else
//                                                   //平衡无所谓
//#endif
//}


/******************************************************************************************
 * 二叉树输出打印
 ******************************************************************************************/
#define ROOT 0
#define L_CHILD 1
#define R_CHILD -1 * L_CHILD

/******************************************************************************************
 * 基础BinTree
 ******************************************************************************************/
//template <typename T>  //元素类型
//void UniPrint::p(BinTree<T>& bt)
//{                                                               // 引用
//    printf("%s[%d]*%d:\n", typeid(bt).name(), &bt, bt.size());  // 基本信息
//    Bitmap* branchType = new Bitmap;                            // 记录当前节点祖先的方向
//    printBinTree(bt.root(), -1, ROOT, branchType);              // 树状结构
//    release(branchType);
//    printf("\n");
//}

/******************************************************************************************
 * 基于BinTree实现的BST
 ******************************************************************************************/
//template <typename T>  //元素类型
//void UniPrint::p(BST<T>& bt)
//{                                                               //引用
//    printf("%s[%d]*%d:\n", typeid(bt).name(), &bt, bt.size());  //基本信息
//    Bitmap* branchType = new Bitmap;                            //记录当前节点祖先的方向
//    printBinTree(bt.root(), -1, ROOT, branchType);              //树状结构
//    release(branchType);
//    printf("\n");
//}

///******************************************************************************************
// * 基于BST实现的AVL
// * 其中调用的BinNode的打印例程，可以显示BF状态
// ******************************************************************************************/
// template <typename T> //元素类型
// void UniPrint::p(AVL<T> & avl) { //引用
//   printf("%s[%d]*%d:\n", typeid (avl).name(), &avl, avl.size()); //基本信息
//   Bitmap* branchType = new Bitmap; //记录当前节点祖先的方向
//   printBinTree (avl.root(), -1, ROOT, branchType); //树状结构
//   release (branchType); printf("\n");
//}

///******************************************************************************************
// * 基于BST实现的RedBlack
// * 其中调用的BinNode的打印例程，可以显示BF状态
// ******************************************************************************************/
// template <typename T> //元素类型
// void UniPrint::p(RedBlack<T> & rb) { //引用
//   printf("%s[%d]*%d:\n", typeid (rb).name(), &rb, rb.size()); //基本信息
//   Bitmap* branchType = new Bitmap; //记录当前节点祖先的方向
//   printBinTree (rb.root(), -1, ROOT, branchType); //树状结构
//   release (branchType); printf("\n");
//}

///******************************************************************************************
// * 基于BST实现的Splay
// * 鉴于Splay不必设置bf之类的附加标识，其打印例程与BST完全一致
// ******************************************************************************************/
// template <typename T> //元素类型
// void UniPrint::p(Splay<T> & bt) { //引用
//   printf("%s[%d]*%d:\n", typeid (bt).name(), &bt, bt.size()); //基本信息
//   Bitmap* branchType = new Bitmap; //记录当前节点祖先的方向
//   printBinTree (bt.root(), -1, ROOT, branchType); //树状结构
//   release (branchType); printf("\n");
//}

/******************************************************************************************
 * 二叉树各种派生类的统一打印
 ******************************************************************************************/
//template <typename T>  //元素类型
//static void printBinTree(BinNodePosi(T) bt, int depth, int type, Bitmap* bType)
//{
//    if (!bt)
//        return;
//    if (-1 < depth)  //设置当前层的拐向标志
//        R_CHILD == type ? bType->set(depth) : bType->clear(depth);
//    printBinTree(bt->rc, depth + 1, R_CHILD, bType);  //右子树（在上）
//    print(bt);
//    printf(" *");
//    for (int i = -1; i < depth; i++)                          //根据相邻各层
//        if ((0 > i) || bType->test(i) == bType->test(i + 1))  //的拐向是否一致，即可确定
//            printf("      ");                                 //是否应该
//        else
//            printf("│    ");  //打印横线
//    switch (type) {
//    case R_CHILD:
//        printf("┌─");
//        break;
//    case L_CHILD:
//        printf("└─");
//        break;
//    default:
//        printf("──");
//        break;  // root
//    }
//    print(bt);
//#if defined(DSA_HUFFMAN)
//    if (IsLeaf(*bt))
//        bType->print(depth + 1);  //输出Huffman编码
//#endif
//    printf("\n");
//    printBinTree(bt->lc, depth + 1, L_CHILD, bType);  //左子树（在下）
//}

/******************************************************************************************
 * BTree打印（入口）
 ******************************************************************************************/
//template <typename T>  //元素类型
//void UniPrint::p(BTree<T>& bt)
//{                                                               //引用
//    printf("%s[%d]*%d:\n", typeid(bt).name(), &bt, bt.size());  //基本信息
//    Bitmap* leftmosts = new Bitmap;                             //记录当前节点祖先的方向
//    Bitmap* rightmosts = new Bitmap;                            //记录当前节点祖先的方向
//    printBTree(bt.root(), 0, true, true, leftmosts, rightmosts);  //输出树状结构
//    release(leftmosts);
//    release(rightmosts);
//    printf("\n");
//}

/******************************************************************************************
 * BTree打印（递归）
 ******************************************************************************************/
//template <typename T>  //元素类型
//static void printBTree(BTNodePosi(T) bt, int depth, bool isLeftmost, bool isRightmost,
//                       Bitmap* leftmosts, Bitmap* rightmosts)
//{
//    if (!bt)
//        return;
//    isLeftmost ? leftmosts->set(depth) : leftmosts->clear(depth);  //设置或清除当前层的拐向标志
//    isRightmost ? rightmosts->set(depth) : rightmosts->clear(depth);  //设置或清除当前层的拐向标志
//    int k = bt->child.size() - 1;  //找到当前节点的最右侧孩子，并
//    printBTree(bt->child[k], depth + 1, false, true, leftmosts, rightmosts);  //递归输出之
//    bool parentOK = false;
//    BTNodePosi(T) p = bt->parent;
//    if (!p)
//        parentOK = true;
//    else
//        for (int i = 0; i < p->child.size(); i++)
//            if (p->child[i] == bt)
//                parentOK = true;
//    while (0 < k--) {  //自右向左，输出各子树及其右侧的关键码
//        printf(parentOK ? " " : "X");
//        print(bt->key[k]);
//        printf(" *>");
//        for (int i = 0; i < depth; i++)  //根据相邻各层
//            (leftmosts->test(i) && leftmosts->test(i + 1) ||
//             rightmosts->test(i) && rightmosts->test(i + 1)) ?  //的拐向是否一致，即可确定
//                printf("      ") :
//                printf("│    ");  //是否应该打印横向联接线
//        if (((0 == depth && 1 < bt->key.size()) || !isLeftmost && isRightmost) && bt->key.size() - 1 == k)
//            printf("┌─");
//        else if (((0 == depth && 1 < bt->key.size()) || isLeftmost && !isRightmost) && 0 == k)
//            printf("└─");
//        else
//            printf("├─");
//        print(bt->key[k]);
//        printf("\n");
//        printBTree(bt->child[k], depth + 1, 0 == k, false, leftmosts, rightmosts);  //递归输出子树
//    }
//}

///******************************************************************************************
// * Entry
// ******************************************************************************************/
// template <typename K, typename V>
// void UniPrint::p(Entry<K, V>& e) //引用
//{  printf("-<"); print(e.key); printf(":"); print(e.value); printf(">-");  }


/******************************************************************************************
 * 图Graph
 ******************************************************************************************/
//template <typename Tv, typename Te>  //顶点类型、边类型
//void UniPrint::p(GraphMatrix<Tv, Te>& s)
//{  //引用
//    int inD = 0;
//    for (int i = 0; i < s.n; i++)
//        inD += s.inDegree(i);
//    int outD = 0;
//    for (int i = 0; i < s.n; i++)
//        outD += s.outDegree(i);
//    printf("%s[%d]*(%d, %d):\n", typeid(s).name(), &s, s.n, s.e);  //基本信息
//                                                                   // 标题行
//    print(s.n);
//    printf(" ");
//    print(inD);
//    printf("|");
//    for (int i = 0; i < s.n; i++) {
//        print(s.vertex(i));
//        printf("[");
//        print(s.status(i));
//        printf("] ");
//    }
//    printf("\n");
//    // 标题行（续）
//    print(outD);
//    printf(" ");
//    print(s.e);
//    printf("|");
//    for (int i = 0; i < s.n; i++) {
//        print(s.inDegree(i));
//        printf(" ");
//    }
//    printf("| dTime fTime Parent Weight\n");
//    // 水平分隔线
//    printf("-----------+");
//    for (int i = 0; i < s.n; i++)
//        printf("------");
//    printf("+----------------------------\n");
//    // 逐行输出各顶点
//    for (int i = 0; i < s.n; i++) {
//        print(s.vertex(i));
//        printf("[");
//        print(s.status(i));
//        printf("] ");
//        print(s.outDegree(i));
//        printf("|");
//        for (int j = 0; j < s.n; j++)
//            if (s.exists(i, j)) {
//                print(s.edge(i, j));
//                print(s.type(i, j));
//            } else
//                printf("     .");
//        printf("| ");
//        print(s.dTime(i));
//        printf(" ");
//        print(s.fTime(i));
//        printf("     ");
//        if (0 > s.parent(i))
//            print("^");
//        else
//            print(s.vertex(s.parent(i)));
//        printf("  ");
//        if (INT_MAX > s.priority(i))
//            print(s.priority(i));
//        else
//            print(" INF");
//        printf("\n");
//    }
//    printf("\n");
//}

/******************************************************************************************
 * Hashtable
 ******************************************************************************************/

//template <typename K, typename V>  // e、value
//void UniPrint::p(Hashtable<K, V>& ht)
//{                                                                   //引用
//    printf("%s[%d]*%d/%d:\n", typeid(ht).name(), &ht, ht.N, ht.M);  //基本信息
//    for (int i = 0; i < ht.M; i++)                                  //输出桶编号
//        printf("  %4d  ", i);
//    printf("\n");
//    for (int i = 0; i < ht.M; i++)  //输出所有元素
//        if (ht.ht[i])
//            printf("-<%04d>-", ht.ht[i]->key);  //演示用，仅适用于int
//        else if (ht.lazyRemoval->test(i))
//            printf("-<xxxx>-");
//        else
//            printf("--------");
//    printf("\n");
//    for (int i = 0; i < ht.M; i++)  //输出所有元素
//        if (ht.ht[i])
//            printf("    %c   ", ht.ht[i]->value);  //演示用，仅适用于char
//        //      if (ht.ht[i]) printf("%8s", ht.ht[i]->value); //针对Huffman编码中使用的散列表
//        else if (ht.lazyRemoval->test(i))
//            printf(" <xxxx> ");
//        else
//            printf("        ");
//    printf("\n");
//}


///******************************************************************************************
// * Huffman（超）字符
// ******************************************************************************************/
// void UniPrint::p(HuffChar& e) { printf("[%c]:%-5d", e.ch, e.weight); }


//#define ROOT 0
//#define L_CHILD 1
//#define R_CHILD -1*L_CHILD

///******************************************************************************************
// * 打印输出PQ_ComplHeap
// ******************************************************************************************/
// template <typename T> //元素类型
// void UniPrint::p(PQ_ComplHeap<T> & pq) { //引用
//   printf("%s[%d]*%d:\n", typeid (pq).name(), &pq, pq.size()); //基本信息
//   int branchType[256]; //最深256层 <= 2^256 = 1.16*10^77
//   printComplHeap((Vector<T> &) pq, pq.size(), 0, 0, ROOT, branchType); //树状结构
//   printf("\n");
//}

///******************************************************************************************
// * 递归打印输出
// ******************************************************************************************/
// template <typename T> //元素类型
// static void printComplHeap(Vector<T>& elem, int n, int k, int depth, int type, int* bType) {
//   if (k >= n) return; //递归基
//   bType[depth] = type;
//   printComplHeap(elem, n, RChild (k), depth + 1, R_CHILD, bType); //右子树（在上）
//   print(elem[k]); ParentValid (k) && (elem[Parent (k) ] < elem[k]) ? printf("X") : printf(" ");
//   printf("*"); for (int i = 0; i < depth; i++) //根据相邻各层
//      if (bType[i] + bType[i+1]) //的拐向是否一致，即可确定
//         printf("      "); //是否应该
//      else  printf("│    "); //打印横线
//   switch (type) {
//      case  R_CHILD  :  printf("┌─");  break;
//      case  L_CHILD  :  printf("└─");  break;
//      default        :  printf("──");  break; //root
//   }
//   print(elem[k]); ParentValid (k) && (elem[Parent (k) ] < elem[k]) ? printf("X") : printf(" ");
//   printf("\n"); printComplHeap(elem, n, LChild (k), depth + 1, L_CHILD, bType); //左子树（在下）
//}

///******************************************************************************************
// * 打印输出PQ_LeftHeap
// ******************************************************************************************/
// template <typename T> //元素类型
// void UniPrint::p(PQ_LeftHeap<T> & lh) { //引用
//   p((BinTree<T>&) lh);
//}

///******************************************************************************************
// * 打印输出PQ_List
// ******************************************************************************************/
// template <typename T> //元素类型
// void UniPrint::p(PQ_List<T> & pq) { //引用
//   printf("%s*%d:\n", typeid (pq).name(), pq.size()); //基本信息
//   p((List<T> &) pq); printf("\n");
//}

///******************************************************************************************
// * Quadlist
// ******************************************************************************************/

// template <typename T> //元素类型
// void UniPrint::p(Quadlist<T>& q) { //引用
//   printf("%s[%d]*%03d: ", typeid (q).name(), &q, q.size()); //基本信息
//   if (q.size() <= 0) {  printf("\n"); return;  }
//   QuadlistNode<T>* curr = q.first()->pred; //当前层之header
//   QuadlistNode<T>* base = q.first(); //当前节点所在
//   while (base->below) base = base->below; //塔底
//   while (base->pred) base = base->pred; //底层之header
//   for (int i = 0; i < q.size(); i++) { //对于当前层的每一节点
//      curr = curr->succ; //curr
//      QuadlistNode<T>* proj = curr; //找到与curr对应的
//      while (proj->below) proj = proj->below; //塔底节点（投影）
//      while ((base = base->succ) != proj) //移动base直到proj，期间不断
//         printf("------------"); //延长水平联接线
//      print(curr->entry); //最后，输出当前层的当前词条
//   }
//   printf("\n");
//}


///******************************************************************************************
// * Skiplist
// ******************************************************************************************/

// template <typename K, typename V> //e、value
// void UniPrint::p(Skiplist<K, V>& s) { //引用
//   printf("%s[%d]*%d*%d:\n", typeid (s).name(), &s, s.level(), s.size()); //基本信息
//   s.traverse (print); //通过print()遍历输出所有元素
//   printf("\n");
//}

/******************************************************************************************
 * 向量、列表等支持traverse()遍历操作的线性结构
 ******************************************************************************************/
// template <typename T>
// void UniPrint::p(T& s) {
//    printf("%s[%d]*%d:\n", typeid(s).name(), &s, s.size()); // 基本信息
//    s.traverse(print); // 通过print()遍历输出所有元素
//    printf("\n");
//}
