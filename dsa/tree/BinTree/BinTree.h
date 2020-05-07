/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#ifndef BIN_TREE_H
#define BIN_TREE_H

#include "BinNode.h" // 引入二叉树节点类

template <typename T> class BinTree {
protected:
    int _size;               // 规模
    BinNodePosi(T) _root;    // 根节点

    // 更新节点x高度, 具体规则，因树而异
    int updateHeight(BinNodePosi(T) x) {
        return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
    }

    // 更新节点x及历代祖先高度
    void updateHeightAbove(BinNodePosi(T) x) {
        while (x) { // 从x出发，覆盖历代祖先. 可优化
            updateHeight(x);
            if (x->parent) x = x->parent;
            else break;
        }
    }

public:
    BinTree() : _size(0), _root(nullptr) {}         // 构造函数
    ~BinTree() { if (0 < _size) remove(_root); }    // 析构函数
    int size() const { return _size; }              // 规模
    bool empty() const { return !_root; }           // 判空
    BinNodePosi(T) root() const { return _root; }   // 树根

    // 将e当作根节点插入空的二叉树
    BinNodePosi(T) insertAsRoot(T const& e) {
        _size = 1;
        return _root = new BinNode<T>(e);
    }

    // e插入为x的左孩子
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e) {
        _size++;
        x->insertAsLC(e);
        updateHeightAbove(x);
        return x->lc;
    }

    // e插入为x的右孩子
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e) {
        _size++;
        x->insertAsRC(e);
        updateHeightAbove(x);
        return x->rc;
    }

    // 二叉树子树接入算法：将S当作节点x的左子树接入，S本身置空
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &S) {
        if (x->lc = S->_root) x->lc->parent = x; // 接入
        _size += S->_size; updateHeightAbove(x); // 更新全树规模与x所有祖先的高度
        S->_root = nullptr; S->_size = 0;
        delete(S); S = nullptr;

        return x; // 释放原树，返回接入位置
    }

    // 二叉树子树接入算法：将S当作节点x的右子树接入，S本身置空
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &S) {
        if (x->rc = S->_root) x->rc->parent = x; // 接入
        _size += S->_size; updateHeightAbove(x); // 更新全树规模与x所有祖先的高度
        S->_root = nullptr; S->_size = 0;
        delete(S); S = nullptr;

        return x; // 释放原树，返回接入位置
    }

    // 删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
    int remove(BinNodePosi(T) x) {
        // assert: x为二叉树中的合法位置
        if (!IsRoot(*x)) {
            FromParentTo(x) = nullptr; // 切断来自父节点的指针
            updateHeightAbove(x->parent); // 新祖先高度
        }
        int n = removeAt(x); _size -= n;
        return n; // 删除子树x，更新规模，返回删除节点总数
    }

    // 删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
    static int removeAt(BinNodePosi(T) x) {
        // assert: x为二叉树中的合法位置
        if(!x) return 0; // 递归基：空树
        int n = 1 + removeAt(x->lc) + removeAt(x->rc); // 递归释放左、右子树
        delete x; x = nullptr;
        return n; // 释放被摘除节点，并返回删除节点总数
    }

    // 二叉树子树分离算法：将子树x从当前树中摘除，将其封装为一棵独立子树返回
    BinTree<T>* secede(BinNodePosi(T) x) {
        // assert: x为二叉树中的合法位置
        BinTree<T>* S = new BinTree<T>;
        S->_root = x; S->_size = x->size();
        if (!IsRoot(*x)) {
            FromParentTo(x) = nullptr;      // 切断来自父节点的指针
            updateHeightAbove(x->parent); // 更新原树中所有祖先的高度
        } else
            _root = nullptr;
        x->parent = nullptr; // 新树以x为根
        _size -= S->_size;

        return S; // 更新规模，返回分离出来的子树
    }

// 操作器
    template <typename VST> void travLevel(VST& visit)  { if (_root) _root->travLevel(visit); } // 层次遍历
    template <typename VST> void travPre(VST& visit)    { if (_root) _root->travPre(visit); }   // 先序遍历
    template <typename VST> void travIn(VST& visit)     { if (_root) _root->travIn(visit); }    // 中序遍历
    template <typename VST> void travPost(VST& visit)   { if (_root) _root->travPost(visit); }  // 后序遍历

// 比较器
    bool operator <  (BinTree<T> const& t) { return _root && t._root && lt(_root, t._root); }
    bool operator <= (BinTree<T> const& t) { return _root && t._root && let(_root, t._root); }
    bool operator >  (BinTree<T> const& t) { return _root && t._root && !let(_root, t._root); }
    bool operator >= (BinTree<T> const& t) { return _root && t._root && !lt(_root, t._root); }
    bool operator == (BinTree<T> const& t) { return _root && t._root && (_root == t._root); }
    bool operator != (BinTree<T> const& t) { return _root && t._root && (_root != t._root); }

//    void stretchToLPath() { stretchByZag (_root); }         // 借助zag旋转，转化为左向单链
//    void stretchToRPath() { stretchByZig (_root, _size); }  // 借助zig旋转，转化为右向单链

}; // BinTree


#endif











