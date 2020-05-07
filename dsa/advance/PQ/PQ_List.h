#ifndef PQ_LIST_H
#define PQ_LIST_H

#include "PQ.h" // 引入优先级队列ADT
#include "../List/List.h" // 引入列表

// 基于列表实现的优先级队列
template <typename T> class PQ_List : public PQ<T>, public List<T>
{
    friend class UniPrint; // 演示输出使用，否则不必设置友类

public:
    PQ_List() { } // 默认构造
    PQ_List(T* E, int n ) { while (0 < n--) this->insertAsFirst((E[n])); } // 批量构造
    void insert(T e) { this->insertAsLast(e); }       // 直接将新元素插至队列末尾
    T getMax() { return this->selectMax()->data; }    // 取出优先级最高的元素
    T delMax() { return this->remove(this->selectMax()); }  // 删除优先级最高的元素
}; // PQ_List



#endif // PQ_LIST_H
