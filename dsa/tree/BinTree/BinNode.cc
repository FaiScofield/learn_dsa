#include "BinNode.h"
#include "../Stack/Stack.h"
#include "../Queue/Queue.h"

/******************************************************************************************
 * BinNode状态与性质的判断
 ******************************************************************************************/
#define IsRoot(x) (! ((x).parent))
#define IsLChild(x) (! IsRoot(x) && (& (x) == (x).parent->lc))
#define IsRChild(x) (! IsRoot(x) && (& (x) == (x).parent->rc))
#define HasParent(x) (! IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x)) //至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) //同时拥有两个孩子
#define IsLeaf(x) (! HasChild(x))

/******************************************************************************************
 * 与BinNode具有特定关系的节点及指针
 ******************************************************************************************/
#define sibling(p) /*兄弟*/ \
    (IsLChild(*p) ? p->parent->rc : p->parent->lc)

#define uncle(x) /*叔叔*/ \
    (IsLChild(* (x->parent)) ? x->parent->parent->rc : x->parent->parent->lc)

#define FromParentTo(x) /*来自父亲的引用*/ \
    (IsRoot(x) ? _root : (IsLChild(x) ? x.parent->lc : x.parent->rc))

#define HeightUpdated(x) /*高度更新常规条件*/ \
        (x.height == 1 + max(stature(x.lc), stature(x.rc)))
#define Balanced(x) (stature(x.lc) == stature(x.rc)) // 理想平衡条件
#define BalFac(x) (stature(x.lc) - stature(x.rc)) // 平衡因子
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2)) // AVL平衡条件

/******************************************************************************************
 * 红黑树
 ******************************************************************************************/
#define IsBlack(p) (!p || (RB_BLACK == p->color)) // 外部节点也视作黑节点
#define IsRed(p) (!IsBlack(p)) // 非黑即红
#define BlackHeightUpdated(x) (/*RedBlack高度更新条件*/ \
    (stature(x.lc) == stature(x.rc)) && \
    (x.height == (IsRed(& x) ? stature(x.lc) : stature(x.lc) + 1)) \
)

// 统计当前节点后代总数，即以其为根的子树规模
// O(n)
template <typename T>
int BinNode<T>::size() {
    int s = 1; // 计入本身
    if (lc) s += lc->size(); // 递归计入左子树规模
    if (rc) s += rc->size(); // 递归计入右子树规模
    return s;
}

// 将e作为当前节点的左孩子插入二叉树
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{ return lc = new BinNode(e, this); }

// 将e作为当前节点的右孩子插入二叉树
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{ return rc = new BinNode(e, this); }


// 定位节点v的直接后继
template <typename T>
BinNodePosi(T) BinNode<T>::succ() {
    BinNodePosi(T) s = this; // 记录后继的临时变量
    if (rc) { // 若有右孩子，则直接后继必在右子树中，具体地就是
        s = rc; // 右子树中
        while (HasLChild(*s)) s = s->lc; // 最靠左（最小）的节点
    } else { // 否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是
        while (IsRChild(*s)) s = s->parent; // 逆向地沿右向分支，不断朝左上方移动
        s = s->parent; // 最后再朝右上方移动一步，即抵达直接后继（如果存在）
    }
    return s;
}



// 二叉树先序遍历算法统一入口
template <typename T> template <typename VST>
void BinNode<T>::travPre(VST& visit) {
   switch (rand() % 3) { // 此处暂随机选择以做测试，共三种选择
      case 1: travPre_I1(this, visit); break;   // 迭代版#1
      case 2: travPre_I2(this, visit); break;   // 迭代版#2
      default: travPre_R(this, visit); break;   // 递归版
   }
}

// 二叉树先序遍历算法（迭代版#1）
template <typename T, typename VST> // 元素类型、操作器
void travPre_I1(BinNodePosi(T) x, VST& visit) {
    Stack<BinNodePosi(T)> S;    // 辅助栈
    if (x) S.push (x);          // 根节点入栈
    while (!S.empty()) {        // 在栈变空之前反复循环
        x = S.pop(); visit(x->data); // 弹出并访问当前节点，其非空孩子的入栈次序为先右后左
        if (HasRChild(*x)) S.push(x->rc);
        if (HasLChild(*x)) S.push(x->lc);
    }
}

// 二叉树先序遍历算法（迭代版#2）
template <typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST& visit) {
    Stack<BinNodePosi(T)> S; // 辅助栈
    while (true) {
        visitAlongLeftBranch(x, visit, S); // 从当前节点出发，逐批访问
        if (S.empty()) break; // 直到栈空
        x = S.pop(); // 弹出下一子树的根
    }
}

// 从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
template <typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S) {
    while (x) {
        visit(x->data); // 访问当前节点
        if (x->rc) S.push(x->rc);  // 右孩子入栈暂存（可优化：通过判断，避免空的右孩子入栈）
        x = x->lc;      // 沿左分支深入一层
    }
}

// 二叉树先序遍历算法（递归版）
// O(n)
template <typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit) {
    if (!x) return;
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}


// 二叉树中序遍历算法统一入口
template <typename T> template <typename VST> // 元素类型、操作器
void BinNode<T>::travIn (VST& visit) {
    switch (rand() % 5) { // 此处暂随机选择以做测试，共五种选择
        case 1: travIn_I1(this, visit); break;  // 迭代版#1
        case 2: travIn_I2(this, visit); break;  // 迭代版#2
        case 3: travIn_I3(this, visit); break;  // 迭代版#3
        case 4: travIn_I4(this, visit); break;  // 迭代版#4
        default: travIn_R(this, visit); break;  // 递归版
    }
}

// 从当前节点出发，沿左分支不断深入，直至没有左分支的节点
template <typename T>
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S) {
    while (x) { // 当前节点入栈后随即向左侧分支深入，迭代直到无左孩子
        S.push(x);
        x = x->lc;
    }
}

// 二叉树中序遍历算法（迭代版#1）
// O(n)
template <typename T, typename VST> // 元素类型、操作器
void travIn_I1(BinNodePosi(T) x, VST& visit) {
    Stack<BinNodePosi(T)> S; // 辅助栈
    while (true) {
        goAlongLeftBranch(x, S); // 从当前节点出发，逐批入栈
        if (S.empty()) break; // 直至所有节点处理完毕
        x = S.pop(); visit(x->data); // 弹出栈顶节点并访问之
        x = x->rc; // 转向右子树
    }
}


// 二叉树中序遍历算法（迭代版#2）
template <typename T, typename VST> // 元素类型、操作器
void travIn_I2(BinNodePosi(T) x, VST& visit) {
    Stack<BinNodePosi(T)> S; // 辅助栈
    while (true) {
        if (x) {
            S.push(x);          // 根节点进栈
            x = x->lc;          // 深入遍历左子树
        }
        else if (!S.empty()) {
            x = S.pop();        // 尚未访问的最低祖先节点退栈
            visit(x->data);     // 访问该祖先节点
            x = x->rc;          // 遍历祖先的右子树
        } else
            break;
    }
}

// 二叉树中序遍历算法（迭代版#3，无需辅助栈）
template <typename T, typename VST> // 元素类型、操作器
void travIn_I3(BinNodePosi(T) x, VST& visit) {
    bool backtrack = false; // 前一步是否刚从右子树回溯——省去栈，仅O(1)辅助空间
    while (true) {
        // 若有左子树且不是刚刚回溯，则深入遍历左子树
        if (!backtrack && HasLChild(*x))
            x = x->lc;
        // 否则——无左子树或刚刚回溯（相当于无左子树）
        else {
            visit(x->data);         // 访问该节点
            if (HasRChild(*x)) {    // 若其右子树非空，则
                x = x->rc;          // 深入右子树继续遍历
                backtrack = false;  // 并关闭回溯标志
            } else {                // 若右子树空，则
                if (!(x = x->succ())) break; // 回溯（含抵达末节点时的退出返回）
                backtrack = true;   // 并设置回溯标志
            }
        }
    }
}


// 二叉树中序遍历（迭代版#4，无需栈或标志位）
template <typename T, typename VST> //元素类型、操作器
void travIn_I4(BinNodePosi(T) x, VST& visit) {
   while (true)
      if (HasLChild (*x)) // 若有左子树，则
         x = x->lc; // 深入遍历左子树
      else { // 否则
         visit (x->data); // 访问当前节点，并
         while (!HasRChild (*x)) // 不断地在无右分支处
            if (!(x = x->succ())) return; // 回溯至直接后继（在没有后继的末节点处，直接退出）
            else visit(x->data); // 访问新的当前节点
         x = x->rc; //（直至有右分支处）转向非空的右子树
      }
}

// 二叉树中序遍历算法（递归版）
template <typename T, typename VST> // 元素类型、操作器
void travIn_R(BinNodePosi(T) x, VST& visit) {
    if (!x) return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}



// 二叉树后序遍历算法统一入口
template <typename T> template <typename VST> // 元素类型、操作器
void BinNode<T>::travPost(VST& visit) {
   switch (rand() % 2) { // 此处暂随机选择以做测试，共两种选择
      case 1: travPost_I(this, visit); break;   // 迭代版
      default: travPost_R(this, visit); break;  // 递归版
   }
}
// 二叉树后序遍历算法（递归版）
template <typename T, typename VST> // 元素类型、操作器
void travPost_R(BinNodePosi(T) x, VST& visit) {
   if (!x) return;
   travPost_R(x->lc, visit);
   travPost_R(x->rc, visit);
   visit(x->data);
}

// 在以S栈顶节点为根的子树中，找到最高左侧可见叶节点
template <typename T>
static void gotoHLVFL(Stack<BinNodePosi(T)>& S) { // 沿途所遇节点依次入栈
    while (BinNodePosi(T) x = S.top()) // 自顶而下，反复检查当前节点（即栈顶）
        if (HasLChild (*x)) { // 尽可能向左
            if (HasRChild (*x)) S.push(x->rc); // 若有右孩子，优先入栈
            S.push(x->lc); // 然后才转至左孩子
        } else // 实不得已
            S.push(x->rc); // 才向右
    S.pop(); // 返回之前，弹出栈顶的空节点
}

// 二叉树的后序遍历（迭代版）
template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit) {
    Stack<BinNodePosi(T)> S; // 辅助栈
    if (x) S.push(x); // 根节点入栈
    while (!S.empty()) {
        if (S.top() != x->parent) // 若栈顶非当前节点之父（则必为其右兄），此时需
            gotoHLVFL(S); // 在以其右兄为根之子树中，找到HLVFL（相当于递归深入其中）
        x = S.pop(); visit(x->data); // 弹出栈顶（即前一节点之后继），并访问之
    }
}

// 二叉树层次遍历算法
template <typename T> template <typename VST> // 元素类型、操作器
void BinNode<T>::travLevel(VST& visit) {
    Queue<BinNodePosi(T)> Q;    // 辅助队列
    Q.enqueue(this);            // 根节点入队
    while (!Q.empty()) {        // 在队列再次变空之前，反复迭代
        BinNodePosi(T) x = Q.dequeue(); visit(x->data); // 取出队首节点并访问之
        if (HasLChild(*x)) Q.enqueue(x->lc); // 左孩子入队
        if (HasRChild(*x)) Q.enqueue(x->rc); // 右孩子入队
    }
}



// 逆时针旋转
template <typename T>
BinNodePosi(T) BinNode<T>::zag() {
    BinNodePosi(T) rChild = rc;
    rChild->parent = this->parent;
    if (rChild->parent)
        ((this == rChild->parent->lc) ? rChild->parent->lc : rChild->parent->rc) = rChild;
    rc = rChild->lc;
    if (rc) rc->parent = this;
    rChild->lc = this;
    this->parent = rChild;
    return rChild;
}


// 顺时针旋转
template <typename T>
BinNodePosi(T) BinNode<T>::zig() {
    BinNodePosi(T) lChild = lc;
    lChild->parent = this->parent;
    if (lChild->parent)
        ((this == lChild->parent->rc) ? lChild->parent->rc : lChild->parent->lc) = lChild;
    lc = lChild->rc;
    if (lc) lc->parent = this;
    lChild->rc = this;
    this->parent = lChild;
    return lChild;
}


// 通过zag旋转调整，将子树x拉伸成最左侧通路
template <typename T>
void stretchByZag (BinNodePosi(T) & x) {
    int c = 0; // 记录旋转次数
    int h = 0;
    BinNodePosi(T) p = x; while (p->rc) p = p->rc; // 最大节点，必是子树最终的根
    while (x->lc) x = x->lc; x->height = h++; // 转至初始最左侧通路的末端
    for (; x != p; x = x->parent, x->height = h++) { // 若x右子树已空，则上升一层
        while (x->rc) { // 否则，反复地
            x->zag(); // 以x为轴做zag旋转
            c++;
        }
    } // 直到抵达子树的根
    printf ("\nh = %d, c = %d\n\n", h, c);
}

// 通过zig旋转调整，将子树x拉伸成最右侧通路
template <typename T>
void stretchByZig (BinNodePosi(T) & x, int h) {
    int c = 0;
    for (BinNodePosi(T) v = x; v; v = v->rc) {
        while (v->lc) {
            v = v->zig();
            c++;
        }
        v->height = --h;
    }
    while (x->parent) x = x->parent;
    printf ("\nh = %d, c = %d\n\n", h, c);
}
