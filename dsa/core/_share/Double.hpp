#ifndef DOUBLE_HPP
#define DOUBLE_HPP

#include "../List/List.hpp"
#include "../Vector/Vector.hpp"

namespace dsa {
// 函数对象：倍增一个T类对象
template <typename T>
struct Double {
    virtual void operator()(T& e) { e *= 2; }  // 假设T可直接倍增
};

// 统一加倍向量中的各元素
template <typename T>
void double_fun(Vector<T>& V)
{
    V.traverse(Double<T>());  // 以Double<T>()为基本操作进行遍历
}

// 统一加倍列表中的各元素
template <typename T>
void double_fun(List<T>& L)
{
    L.traverse(Double<T>());  // 以Double<T>()为基本操作进行遍历
}

}

#endif  // DOUBLE_HPP
