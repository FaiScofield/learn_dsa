#ifndef HALF_HPP
#define HALF_HPP

#include "../List/List.hpp"
#include "../Vector/Vector.hpp"

namespace dsa {
// 函数对象：减半一个T类对象
template <typename T> struct Half
{
    virtual void operator() (T& e) { e /= 2; }  // 假设T可直接减半
};

// 统一减半列表中的各元素
template <typename T> void half(List<T> & L)
{
    L.traverse(Half<T>());  // 以Half<T>()为基本操作进行遍历
}

// 统一减半向量中的各元素
template <typename T> void half(Vector<T>& V)
{
    V.traverse(Half<T>());  // 以Half<T>()为基本操作进行遍历
}

}
#endif // HALF_HPP
