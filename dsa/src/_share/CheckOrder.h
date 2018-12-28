#ifndef CHECKORDER_H
#define CHECKORDER_H

#include "../Vector/Vector.h"
#include "../List/List.h"

// 函数对象：判断一个T类对象是否局部有序
template <typename T> struct CheckOrder {
    T pred;
    int& u;
    CheckOrder(int& unsorted, T& first) : pred(first), u(unsorted) { }
    virtual void operator() (T& e) { if (pred > e) u++; pred = e; }
};

// 判断向量是否整体有序
//template <typename T> void checkOrder(Vector<T>& V) {
//    int unsorted = 0; // 逆序计数器
//    V.traverse(CheckOrder<T>(unsorted, V[0])); // 进行遍历
//    if (0 < unsorted)
//        printf ("Unsorted with %d adjacent disordered pair(s)\n", unsorted);
//    else
//        printf ("Sorted\n");
//}
template <typename T> void checkOrder(Vector<T> & V) {
    if (0 < V.disordered())
        printf("Unsorted with %d adjacent disordered pair(s)\n", V.disordered());
    else
        printf("Sorted\n");
}

// 判断列表是否整体有序
//template <typename T> void checkOrder(List<T> & L) {
//    int unsorted = 0; //逆序计数器
//    L.traverse (CheckOrder<T> (unsorted, L.first()->data)); //进行遍历
//    if (0 < unsorted)
//      printf ("Unsorted with %d adjacent disordered pair(s)\n", unsorted);
//    else
//      printf ("Sorted\n");
//    printf ("DISORDERED = %d\n", L.disordered());
//}
template <typename T> void checkOrder(List<T> & L) {
    if (0 < L.disordered())
        printf("Unsorted with %d adjacent disordered pair(s)\n", L.disordered());
    else
        printf("Sorted\n");
}

#endif // CHECKORDER_H
