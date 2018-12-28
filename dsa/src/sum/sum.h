/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#ifndef SUM_H
#define SUM_H

int sumI(int A[], int n);
int sum(int A[], int n);
int sum(int A[], int lo, int hi);

// 数组求和算法（迭代版）
// O(1) + O(n)*O(1) + O(1) = O(n+2) = O(n)
int sumI(int A[], int n);

// 数组求和算法（线性递归版）
// O(1)*递归深度 = O(1)*(n+1) = O(n)
int sum(int A[], int n);

// 数组求和算法（二分递归版，入口为sum(A, 0, n-1)）
// O(hi - lo + 1)，线性正比于区间的长度
int sum(int A[], int lo, int hi);

#endif
