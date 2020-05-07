/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

//#include "../_share/util.h"
#include "../UniPrint/print_int_array.h"


// 数组倒置（直接改造而得的迭代版）
// O(hi - lo + 1)
void reverseI(int* A, int lo, int hi)
{
next: //算法起始位置添加跳转标志
   if ( lo < hi ) {
      swap(A[lo], A[hi]);   // 交换A[lo]和A[hi]
      lo++; hi--;           // 收缩待倒置区间
      goto next;            // 跳转至算法体的起始位置，迭代地倒置A(lo, hi)
   }                        // else隐含了迭代的终止
}

// 数组倒置（规范整理之后的迭代版）
// O(hi - lo + 1)
void reverseII(int* A, int lo, int hi)
{
   while ( lo < hi )                // 用while替换跳转标志和if，完全等效
      swap(A[lo++], A[hi--]);       // 交换A[lo]和A[hi]，收缩待倒置区间
}

// 数组倒置（多递归基递归版）
// O(hi - lo + 1)
void reverseIII(int* A, int lo, int hi)
{
   if (lo < hi) {
      swap(A[lo], A[hi]);           // 交换A[lo]和A[hi]
      reverseIII(A, ++lo, --hi);    // 递归倒置A(lo, hi)
   }                                // else隐含了两种递归基
}

// 数组倒置（算法的初始入口，调用的可能是reverse()的递归版或迭代版）
// 由重载的入口启动递归或迭代算法
void reverse(int* A, int n)
{
    reverseII(A, 0, n-1);
}
