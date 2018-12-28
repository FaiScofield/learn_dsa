#ifndef INCREASE_H
#define INCREASE_H

#include "../Vector/Vector.h"
#include "../List/List.h"

// 函数对象：递增一个T类对象
template <typename T> struct Increase
{
    virtual void operator() (T& e) { e++; }  // 假设T可直接递增或已重载++
};

// 统一递增列表中的各元素
template <typename T> void increase(List<T>& L)
{
    L.traverse(Increase<T>());  // 以Increase<T>()为基本操作进行遍历
}

// 统一递增向量中的各元素
template <typename T> void increase(Vector<T>& V)
{
    V.traverse(Increase<T>());  // 以Increase<T>()为基本操作进行遍历
}



#endif
