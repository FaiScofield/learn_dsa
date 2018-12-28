/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#include <limits.h>
#include <iostream>

using namespace std;

// 求数组最大值算法（迭代版）
// O(1) + O(n) * O(1) + O(1) = O(n+2) = O(n)
int maxI(int A[], int n) {
    int m = INT_MIN;             // 初始化最大值纪录，O(1)
    for (int i = 0; i < n; i++)  // 对全部共O(n)个元素，逐一
        m = max(m, A[i]);         // 比较并更新，O(1)
    return m;                    // 返回最大值，O(1)
}

// 数组求最大值算法（线性递归版）
// O(1) * 递归深度 = O(1) * (n+1) = O(n)
int maxR(int A[], int n) {
    if (2 > n)           // 平凡情况，递归基
        return A[n-1];    // 直接（非递归式）计算
    else                 // 一般情况，递归：在前n-1项中的最大值与第n-1项之间，取大者
        return max(maxR(A, n-1), A[n-1]);
}

// 计算数组区间A[lo, hi)的最大值（二分递归）
// 以中位单元为界，将原区间一分为二：A[lo, mi)和A[mi, hi)
int maxR(int A[], int lo, int hi) {
    if (lo >= hi)
        return -1;
    if (lo + 1 == hi)   // 如遇递归基（区间长度已降至1），则
        return A[lo];   // 直接返回该元素
    else {
        // 否则（一般情况下lo + 1 < hi），则递归地
        // 以中位单元为界，将原区间一分为二：A[lo, mi)和A[mi, hi)
        int mi = (lo + hi) >> 1;
        // 计算子区间的最大值，再从中取大者
        return max(maxR(A, lo, mi), maxR(A, mi, hi));
    }
}

// 计算数组区间A[lo, hi)的最大值A[x1]和次大值A[x2]（迭代版）
// best = worst = O(2n-3)
void max2I(int A[], int lo, int hi, int& x1, int& x2)
{
    for (int i=lo+1, x1=lo; i<hi; ++i)  // find A[x1]
        if (A[x1] < A[i]) x1 = i;       // hi - lo - 1 = n-1
    for (int i=lo+1, x2=lo; i<x1; ++i)  // find A[x2] in A[lo, x1)
        if (A[x2] < A[i]) x2 = i;       // x1 - lo - 1
    for (int i=x1+1; i<hi; ++i)         // find A[x2] in A(x1, hi)
        if (A[x2] < A[i]) x2 = i;       // hi - x1 - 1


}

// 计算数组区间A[lo, hi)的最大值A[x1]和次大值A[x2]（索引记录版）
// best  = 1 + (n-2)*1 = O(n-1)
// worst = 1 + (n-2)*2 = O(2n-3)
void max2II(int A[], int lo, int hi, int& x1, int& x2)
{
    if (A[x1=lo] < A[x2=lo+1]) swap(x1, x2);
    for (int i=lo+2; i<hi; ++i) {
        if (A[x2] < A[i])
            if (A[x1] < A[x2=i])
                swap(x1, x2);
    }
}

// 计算数组区间A[lo, hi)的最大值A[x1]和次大值A[x2]（二分递归版）
// T(n) = 2 * T(n/2) + 2 <= 5n/3 - 2
void max2(int A[], int lo, int hi, int& x1, int& x2)
{
    if (lo+2 == hi) {
        (A[lo] < A[lo+1]) ?
                    x1 = lo + 1, x2 = lo :
                x1 = lo, x2 = lo + 1;
        return;
    }
    if (lo+3 == hi) {
        max2II(A, lo, hi, x1, x2);
    }

    int mi = (lo + hi) >> 1;
    int x1L, x2L, x1R, x2R;
    max2II(A, lo, mi, x1L, x2L);
    max2II(A, lo, mi, x1R, x2R);

    if (A[x1L] > A[x1R]) {
        x1 = x1L;
        x2 = (A[x2L] > A[x1R]) ? x2L : x1R;
    } else {
        x1 = x1R;
        x2 = (A[x1L] > A[x2R]) ? x1L : x2R;
    }
}

