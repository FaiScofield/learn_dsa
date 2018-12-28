/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#include "ListNode.h"

// 将e紧随当前节点之后插入于当前节点所属列表（设有哨兵尾节点trailer）
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e) {
    ListNodePosi(T) x = new ListNode(e, this, succ); // 创建新节点
    succ->pred = x; succ = x; // 设置逆向链接
    return x; // 返回新节点的位置
}

// 将e紧靠当前节点之前插入于当前节点所属列表（设有哨兵头节点header）
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) {
    ListNodePosi(T) x = new ListNode(e, pred, this); // 创建新节点
    pred->succ = x; pred = x; // 设置正向链接
    return x; // 返回新节点的位置
}