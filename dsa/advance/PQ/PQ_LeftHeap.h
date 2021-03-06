#ifndef PQ_LEFTHEAP_H
#define PQ_LEFTHEAP_H

#include "../_share/util.h"
#include "../PQ/PQ.h" // 引入优先级队列ADT
#include "../BinTree/BinTree.h" // 引入二叉树节点模板类

// 基于二叉树，以左式堆形式实现的PQ
template <typename T>
class PQ_LeftHeap : public PQ<T>, public BinTree<T>
{
    friend class UniPrint; // 演示输出使用，否则不必设置友类

public:
    PQ_LeftHeap() { } // 默认构造
    PQ_LeftHeap(T* E, int n) // 批量构造：可改进为Floyd建堆算法
    { for (int i = 0; i < n; i++) insert(E[i]); }

    // 按照比较器确定的优先级次序插入元素
    void insert(T e) {
        BinNodePosi(T) v = new BinNode<T>(e); // 为e创建一个二叉树节点
        this->_root = merge(this->_root, v); // 通过合并完成新节点的插入
    //    this->_root->parent = NULL; // 既然此时堆非空，还需相应设置父子链接
        this->_size++; // 更新规模
    }

    // 获取非空左式堆中优先级最高的词条
    T getMax() {
        return this->_root->data; // 按照此处约定，堆顶即优先级最高的词条
    }

    // 基于合并操作的词条删除算法（当前队列非空）
    T delMax() {
        BinNodePosi(T) lHeap = this->_root->lc; // 左子堆
        BinNodePosi(T) rHeap = this->_root->rc; // 右子堆
        T e = this->_root->data; delete this->_root; this->_size--; // 删除根节点
        this->_root = merge(lHeap, rHeap); // 原左右子堆合并
    //    if (this->_root) this->_root->parent = NULL; // 若堆非空，还需相应设置父子链接
        return e; // 返回原根节点的数据项
    }
}; // PQ_LeftHeap


// 根据相对优先级确定适宜的方式，合并以a和b为根节点的两个左式堆
// 本算法只实现结构上的合并，堆的规模须由上层调用者负责更新
template <typename T>
static BinNodePosi(T) merge(BinNodePosi(T) a, BinNodePosi(T) b) {
    if (!a) return b; // 退化情况
    if (!b) return a; // 退化情况
    if (lt(a->data, b->data)) swap(a, b); // 一般情况：首先确保b不大
    a->rc = merge(a->rc, b); // 将a的右子堆，与b合并
    a->rc->parent = a; // 并更新父子关系
    if (!a->lc || a->lc->npl < a->rc->npl) // 若有必要
        swap(a->lc, a->rc); // 交换a的左、右子堆，以确保右子堆的npl不大
    a->npl = a->rc ? a->rc->npl + 1 : 1; // 更新a的npl
    return a; // 返回合并后的堆顶
}

#endif //  PQ_LEFTHEAP_H
