/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#include <time.h>
#include <iostream>

using namespace std;

#include "../random/shuffle.h"
#include "../UniPrint/print_int_array.h"
#include "../reverse/reverse.h"
#include "../max/max.h"

/*******************************************************************************
 * 测试SUM
 *******************************************************************************/
int main(int argc, char* argv[]) {
    int n = (1 < argc) ? atoi(argv[1]) : 7;
    int* A = (int*) malloc(n * sizeof(int));

    srand((unsigned int) time(NULL));
    for(int i = 0; i < n; i++) A[i] = i;
    shuffle(A, n); print_int(A, n);    // 创建长度为n的随机整数数组
    printf("MaxI  = %d\n", maxI(A, n));
    printf("MaxR1 = %d\n", maxR(A, n));
    printf("MaxR2 = %d\n\n", maxR(A, 0, n-1));

    reverse(A, n); print_int(A, n);          // 倒置：一般形式的递归入口
    printf("MaxI  = %d\n", maxI(A, n));
    printf("MaxR1 = %d\n", maxR(A, n));
    printf("MaxR2 = %d\n\n", maxR(A, 0, n-1));

    free(A);
    printf("Test done.\a\n");

    return 0;
}

