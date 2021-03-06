/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#ifndef BUBBLE_H
#define BUBBLE_H

#include "../_share/util.h"
#include "../UniPrint/print_int_array.h"

// 起泡排序算法（版本0）：0 <= n
// 蛮力算法，不能及时提前退出，总是必须做n-1趟扫描交换
void bubblesort (int A[], int n) {
   int cmp = 0, swp = 0;
   while (n--) { //在尚未确认已全局排序之前，逐趟进行扫描交换
      for (int i = 0; i < n; i++) { //自左向右逐对检查当前范围A[0, n)内的各相邻元素
         if (A[i] > A[i+1]) { //一旦A[i]与A[i+1]逆序，则
            swap (A[i], A[i+1]); //交换之，并
            swp++; printf("%3d: ", n); print_int(A, n, i, i + 2);
         }
         cmp++;
      }
   }
   printf ("#comparison = %d, #swap = %d\n", cmp, swp);
}

// 起泡排序算法（版本1A）：0 <= n
// 借助布尔型标志位sorted，可及时提前退出，而不致总是蛮力地做n-1趟扫描交换
void bubblesort1A (int A[], int n) {
   int cmp = 0, swp = 0;
   bool sorted = false; //整体排序标志，首先假定尚未排序
   while (!sorted) { //在尚未确认已全局排序之前，逐趟进行扫描交换
      sorted = true; //假定已经排序
      for (int i = 1; i < n; i++) { //自左向右逐对检查当前范围A[0, n)内的各相邻元素
         if (A[i - 1] > A[i]) { //一旦A[i - 1]与A[i]逆序，则
            swap (A[i - 1], A[i]); //交换之，并
            sorted = false; //因整体排序不能保证，需要清除排序标志
            swp++; printf ("%3d: ", n); print_int (A, n, i - 1, i + 1);
         }
         cmp++;
      }
      n--; //至此末元素必然就位，故可以缩短待排序序列的有效长度
   }
   printf ("#comparison = %d, #swap = %d\n", cmp, swp);
}

// 起泡排序算法（版本1B，与版本1A完全等价）：0 <= n
// 借助布尔型标志位sorted，可及时提前退出，而不致蛮力地做n-1趟扫描交换
// 对尾部有序（或接近有序）的输入，算法依然亦步亦趋地收敛，导致元素比较次数过多
void bubblesort1B (int A[], int n) {
   int cmp = 0, swp = 0;
   for (bool sorted = false; sorted = !sorted; n--) { //在尚未确认已全局排序之前，逐趟进行扫描交换
      for (int i = 1; i < n; i++) { //自左向右逐对检查当前范围A[0, n)内的各相邻元素
         if (A[i-1] > A[i]) { //一旦A[i-1]与A[i]逆序，则
            swap (A[i-1], A[i]); //交换之，并
            sorted = false; //因整体排序不能保证，需要清除排序标志
            swp++; printf ("%3d: ", n); print_int (A, n, i - 1, i + 1);
         }
         cmp++;
      }
   }
   printf ("#comparison = %d, #swap = %d\n", cmp, swp);
}

// 起泡排序算法（版本2）：0 <= n
// 借助整数m尽快地收缩待排序区间：既可提前退出，更可减少每趟（及所有）扫描交换中元素比较操作
// 对尾部有序（或接近有序）的输入，算法收敛的速度大大提高
// 元素交换的次数仅取决于输入序列，与版本0和版本1相同
void bubblesort2 (int A[], int n) {
   int cmp = 0, swp = 0;
   for (int m; 1 < n; n = m) { //在尚未确认已全局排序之前，逐趟进行扫描交换
      for (int i = m = 1; i < n; i++) { //自左向右逐对检查当前范围A[0, m)内的各相邻元素
         if (A[i-1] > A[i]) { //一旦A[i-1]与A[i]逆序，则
            swap (A[i-1], A[i]); //交换之，并
            m = i; //更新待排序区间的长度
            swp++; printf ("%3d: ", n); print_int (A, n, i - 1, i + 1);
         }
         cmp++;
      }
   }
   printf ("#comparison = %d, #swap = %d\n", cmp, swp);
}

#endif
