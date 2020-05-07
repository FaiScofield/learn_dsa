/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

int sumI (int A[], int n);
int sum (int A[], int n);
int sum (int A[], int lo, int hi);

// 数组求和算法（迭代版）
// O(1) + O(n)*O(1) + O(1) = O(n+2) = O(n)
int sumI (int A[], int n) {
    int sum = 0;                     // 初始化累计器，O(1)
    for (int i = 0; i < n; i++)    // 对全部共O(n)个元素，逐一
        sum += A[i];                  // 累计，O(1)
    return sum;                      // 返回累计值，O(1)
}

// 数组求和算法（线性递归版）
// O(1)*递归深度 = O(1)*(n+1) = O(n)
int sum(int A[], int n) {
    if (1 > n)                       // 平凡情况，递归基
        return 0;                     // 直接（非递归式）计算
    else                             // 一般情况
        return sum(A, n-1) + A[n-1];  // 递归：前 n-1 项之和，再累计第 n-1 项
}

// 数组求和算法（二分递归版，入口为sum(A, 0, n-1)）
// O(hi - lo + 1)，线性正比于区间的长度
int sum(int A[], int lo, int hi) {
    if (lo == hi)                                // 如遇递归基（区间长度已降至1），则
        return A[lo];                             // 直接返回该元素
    else {                                       // 否则（一般情况下lo < hi），则
        int mi = (lo + hi) >> 1;                  // 以居中单元为界，将原区间一分为二
        return sum(A, lo, mi) + sum(A, mi+1, hi); // 递归对各子数组求和，然后合计
    }
}
