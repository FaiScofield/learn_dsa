#ifndef DECREASE_H
#define DECREASE_H

#include "../List/List.h"
#include "../Vector/Vector.h"


// 函数对象：递减一个T类对象
template <typename T> struct Decrease
{
    virtual void operator() (T& e) { e--; }  // 假设T可直接递减或已重载--
};

// 统一递减列表中的各元素
template <typename T> void decrease(List<T>& L)
{
    L.traverse(Decrease<T>());  // 以Decrease<T>()为基本操作进行遍历
}

// 统一递减向量中的各元素
template <typename T> void decrease(Vector<T>& V)
{
    V.traverse(Decrease<T>());  // 以Decrease<T>()为基本操作进行遍历
}


#endif // DECREASE_H
