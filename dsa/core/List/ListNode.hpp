/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#ifndef LIST_NODE_HPP
#define LIST_NODE_HPP

namespace dsa
{

#define ListNodePosi(T) dsa::ListNode<T>*

// 列表节点模板类（以双向链表形式实现）
template <typename T>
struct ListNode {

    // 成员, 数值、前驱、后继
    T data;
    ListNodePosi(T) prev;
    ListNodePosi(T) next;

    // 构造函数
    ListNode(): prev(nullptr), next(nullptr) {}
    ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) : data(e), prev(p), next(s) {}

    // 将e紧靠当前节点之前插入于当前节点所属列表（设有哨兵头节点header）
    ListNodePosi(T) insertAsPrev(const T& e)
    {
        ListNodePosi(T) x = new ListNode(e, prev, this);  // 创建新节点
        prev->next = x;
        prev = x;  // 设置正向链接
        return x;  // 返回新节点的位置
    }

    // 将e紧随当前节点之后插入于当前节点所属列表（设有哨兵尾节点trailer）
    ListNodePosi(T) insertAsNext(T const& e)
    {
        ListNodePosi(T) x = new ListNode(e, this, next);  // 创建新节点
        next->prev = x;
        next = x;  // 设置逆向链接
        return x;  // 返回新节点的位置
    }
};

}  // namespace dsa

#endif
