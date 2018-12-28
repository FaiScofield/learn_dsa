#ifndef SHOWSTRINGMATCH_H
#define SHOWSTRINGMATCH_H

#include <stdio.h>
#include <string.h>


#define printString(s) { for (size_t m = strlen(s), k = 0; k < m; k++) printf("%c  ", (s)[k]); }


/******************************************************************************************
 * 显示Next[]表，供演示分析
 ******************************************************************************************/
void printNext(int* N, int offset, int length) {
    for (int i = 0; i < length; i++) printf("%3d", i);
    printf("\n");
    for (int i = 0; i < offset; i++) printf("   ");
    for (int i = 0; i < length; i++) printf("%3d", N[i]);
    printf("\n\n");
}

/******************************************************************************************
 * 显示bc[]表，供演示分析
 ******************************************************************************************/
void printBC(int* bc) {
    printf("\n-- bc[] Table ---------------\n");
    for (size_t j = 0; j < 256; j++)
        if (0 <= bc[j]) printf("%3c", (char) j);
    printf("\n");
    for (size_t j = 0; j < 256; j++)
        if (0 <= bc[j]) printf("%3d", bc[j]);
    printf("\n\n");
}

/******************************************************************************************
 * 显示GS[]表，供演示分析
 ******************************************************************************************/
void printGS(char* P, int* GS) {
    printf("-- gs[] Table ---------------\n");
    for (size_t m = strlen (P), j = 0; j < m; j++)
        printf("%3ld", j);
    printf("\n  ");
    printString(P); printf("\n");
    for (size_t m = strlen (P), j = 0; j < m; j++)
        printf("%3d", GS[j]);
    printf("\n\n");
}

/******************************************************************************************
 * Text     :  0   1   2   .   .   .   i   i+1 .   .   .   i+j .   .   n-1
 *             ------------------------|-------------------|------------
 * Pattern  :                          0   1   .   .   .   j   .   .
 *                                     |-------------------|
 ******************************************************************************************
 * 动态显示匹配进展
 * i为P相对于T的起始位置，j为P的当前字符
 ******************************************************************************************/
void showProgress(char* T, char* P, int i, int j) {
    static int step = 0; // 操作计数器
    printf("\n-- Step %2d: --\n", ++step);
    for (size_t n = strlen(T), t = 0; t < n; t++) printf("%3ld", t);
    printf("\n  "); printString(T); printf("\n");
    if (0 <= i + j) {
        for (int t = 0; t < i + j; t++) printf("%3c", ' ');
        printf("%3c", '|'); printf("\n  ");
    }
    for (int t = 0; t < i; t++) printf("%3c", ' ');
    printString(P); printf("\n");
}

#endif // SHOWSTRINGMATCH_H
