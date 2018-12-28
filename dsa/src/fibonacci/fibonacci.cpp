/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/
#include "fibonacci.h"

#include <time.h>
#include <iostream>

using namespace std;

//long  fibI (long n); //迭代版
//long  fib (long n); //二分递归版
//long  fib (long n, long& f); //线性递归版

// 计算Fibonacci数列的第n项（二分递归版）
// 低效的根源在于各递归实例被大量的重复调用
// phi = (1+sqrt(5))/2 = 1.618, 耗时最长, O(phi^n) = O(2^n)
unsigned long int fib(int n) {
    return (2 > n) ?
           (unsigned long int) n :  // 若到达递归基，直接取值
           fib(n-1) + fib(n-2);     // 否则，递归计算前两项，其和即为正解
}

/***
 * 防止重复调用的解决办法:
 * A. memoization 记忆法，将fibonacci各项计算的结果记录在表格里，防止重复计算
 * B.dynamic programming 动态规划（重点）. 颠倒计算方向，自顶而下递归，即变成迭代法
 * 动态规划还可用于求接最长公共子序列问题LCS（重点）
**/

// 计算Fibonacci数列的第n项（迭代版）(B)
// O(n)
unsigned long int fib_I(int n) {
    unsigned long int last = 1, curr = 0; // 初始化：fib(-1)、fib(0)
    while (0 < n--) {   // 依据原始定义，通过n次加法和减法计算fib(n)
        curr += last;
        last = curr - last;
    }
    return curr;
}

// 计算Fibonacci数列第n项（线性递归版）：入口形式fib(n, prev)
// 用辅助变量记录前一项，返回数列的当前项，O(n)
unsigned long int fib(int n, unsigned long int& prev) {
    // 若到达递归基，则直接取值：fib(-1) = 1, fib(0) = 0
    if (0 == n) {
        prev = 1;
        return 0;
    }
    // 否则递归计算前两项,其和即为正解
    else {
        unsigned long int prevPrev;
        prev = fib(n-1, prevPrev);
        return prevPrev + prev;
    }
}


int main(int argc, char* argv[]) { //测试FIB
    // 检查参数
    if (2 > argc) {
        fprintf(stderr, "Usage: %s <rank>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);

    // 依次计算Fibonacci数列各项
    printf("\n------------- class Fib -------------\n");
    Fib f(0);
    for (int i = 0; i < n; i++, f.next())
        printf("fib(%2d) = %ld\n", i, f.get());
    for (int i = 0; i <= n; i++, f.prev())
        printf("fib(%2d) = %ld\n", n-i, f.get());

    printf("\n------------- Iteration -------------\n");
    for (int i = 0; i <= n; i++)
        printf("fib(%2d) = %ld\n", i, fib_I(i));

    printf("\n------------- Linear Recursion -------------\n");
    for (int i = 0; i <= n; i++) {
        unsigned long int f;
        printf("fib(%2d) = %ld\n", i, fib(i, f));
    }

    printf("\n------------- Binary Recursion -------------\n");
    for (int i = 0; i <= n; i++)
        printf("fib(%2d) = %ld\n", i, fib(long(i)));

    return 0;
}

