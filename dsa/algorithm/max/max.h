/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#ifndef MAX_H
#define MAX_H

// 求数组最大值算法（迭代版）
// O(1) + O(n) * O(1) + O(1) = O(n+2) = O(n)
int maxI(int A[], int n);

// 数组求最大值算法（线性递归版）
// O(1) * 递归深度 = O(1) * (n+1) = O(n)
int maxR(int A[], int n);

// 计算数组区间A[lo, hi)的最大值（二分递归）
// 以中位单元为界，将原区间一分为二：A[lo, mi)和A[mi, hi)
int maxR(int A[], int lo, int hi);

// 计算数组区间A[lo, hi)的最大值A[x1]和次大值A[x2]（迭代版）
// best = worst = O(2n-3)
void max2I(int A[], int lo, int hi, int& x1, int& x2);

// 计算数组区间A[lo, hi)的最大值A[x1]和次大值A[x2]（索引记录版）
// best  = 1 + (n-2)*1 = O(n-1)
// worst = 1 + (n-2)*2 = O(2n-3)
void max2II(int A[], int lo, int hi, int& x1, int& x2);

// 计算数组区间A[lo, hi)的最大值A[x1]和次大值A[x2]（二分递归版）
// T(n) = 2 * T(n/2) + 2 <= 5n/3 - 2
void max2(int A[], int lo, int hi, int& x1, int& x2);

#endif
