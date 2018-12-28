#ifndef CRC_H
#define CRC_H

#include "../Vector/Vector.h"
#include "../List/List.h"
#include "../UniPrint/print.h"

// 函数对象：累计T类对象的特征（比如总和），以便校验对象集合
template <typename T> struct Crc {
    T& c;
    Crc(T& crc) : c(crc) {}
    virtual void operator() (T& e) { c += e; } // 假设T可直接相加
};


// 统计向量的特征（所有元素之和）
template <typename T> void crc(Vector<T> & V) {
    T crc = 0;
    V.traverse(Crc<T>(crc)); // 以crc为基本操作进行遍历
    printf("CRC =");
    print(crc);
    printf("\n" ); // 输出统计得到的特征
}

// 统计列表的特征（所有元素总和）
template <typename T> void crc(List<T> & L) {
    T crc = 0;
    L.traverse(Crc<T>(crc)); // 以crc为基本操作进行遍历
    printf("CRC =");
    print(crc);
    printf("\n"); // 输出统计得到的特征
}

#endif // CRC_H
