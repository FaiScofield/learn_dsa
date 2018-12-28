#ifndef STRING_H
#define STRING_H

// #include "../Vector/Vector.h"
#include "showStringMatch.h"
#include <limits>
#include <iostream>

// 串匹配算法（Brute-force-1）, O(n*m)
int match_bf_I(char *P, char *T) {
    //  n >> m
    size_t n = strlen(T), i = 0;    // 文本串长度、当前接受比对字符的位置
    size_t m = strlen(P), j = 0;    // 模式串长度、当前接受比对字符的位置
    while (j < m && i < n) {        // 自左向右逐个比对字符
        if (T[i] == P[j]) { ++i; ++j; } // 若匹配则转到下一对字符
        else { i -= j - 1; j = 0; } // 否则文本串回退、模式串复位
    }

    return i - j;
}

// 串匹配算法（Brute-force-2）, O(n*m)
int match_bf_II(char* P, char* T) {
    size_t n = strlen(T), i = 0; // 文本串长度、与模式串首字符的对齐位置
    size_t m = strlen(P), j; // 模式串长度、当前接受比对字符的位置
    for (i = 0; i < n - m + 1; i++) { // 文本串从第i个字符起，与
        for (j = 0; j < m; j++) { // 模式串中对应的字符逐个比对
            if (T[i+j] != P[j])
                break; // 若失配，模式串整体右移一个字符，再做一轮比对
        }
        if (j >= m) break; // 找到匹配子串
    }
    return i; // 如何通过返回值，判断匹配结果？
}

/////////////////////////////////////////
/* KMP Algorithm */
// 构造模式串P的next表（改进版本）, O(m)
int* buildNext(char* P) {
    size_t m = strlen(P), j = 0; // “主”串指针
    int* Next = new int[m]; // next表
    int t = Next[0] = -1;   // 模式串指针
    while (j < m - 1)
        if (0 > t || P[j] == P[t]) { // 匹配
//            Next[j] = (P[++j] != P[++t] ? t : Next[t]); // 注意此句与未改进之前的区别
            Next[++j] = ++t;
        } else // 失配
            t = Next[t];
    printf("Next lookup table:\n  "); printString(P); printf("\n");
    printNext(Next, 0, strlen(P));
    return Next;
}

// KMP算法 O(n)
int match_kmp(char* P, char* T) {
    int* next = buildNext(P); // 构造next表
    int n = (int)strlen(T), i = 0; // 文本串指针
    int m = (int)strlen(P), j = 0; // 模式串指针
    while (j < m  && i < n) { // 自左向右逐个比对字符
      showProgress(T, P, i - j, j);
//      printNext(next, i - j, strlen(P));
      if (0 > j || T[i] == P[j]) // 若匹配，或P已移出最左侧（两个判断的次序不可交换）
         { i ++;  j ++; } // 则转到下一字符
      else // 否则
         j = next[j]; // 模式串右移（注意：文本串不用回退）
    }
    delete [] next; // 释放next表
    return i - j;
}


// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
//  Boyer-Moore算法
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
// void     ShowProgress (String, String,  int,  int);
#define  CARD_CHAR_SET     256   // Cardinality of charactor set

// int*     suffixes (String);
// int*     BuildGS (String); // 构造Good Suffix Shift表


// 构造Bad Charactor Shift表：O(m + 256)
int* buildBC(char* P) {
    int* bc = new int[256];                         // BC表，与字符表等长, ASCII(0-255)码字符表
    for (size_t j = 0; j < 256; j ++) bc[j] = -1;   // 初始化：首先假设所有字符均未在P中出现
    for (size_t m = strlen(P), j = 0; j < m; j++)   // 自左向右扫描模式串P
        bc[P[j]] = j;                               // 将字符P[j]的BC项更新为j（单调递增）——画家算法(后来覆盖以往)
    printBC(bc);
    return bc;
}

// 构造最大匹配后缀长度表：O(m)
int* buildSS(char* P) {
    int m = strlen(P); int* ss = new int[m];                // Suffix Size表
    ss[m-1]  =  m;                                          // 对最后一个字符而言，与之匹配的最长后缀就是整个P串
    // 以下，从倒数第二个字符起自右向左扫描P，依次计算出ss[]其余各项
    for (int lo = m - 1, hi = m - 1, j = lo - 1; j >= 0; j --)
        if ((lo < j) && (ss[m - hi + j - 1] <= j - lo))     // 情况一
            ss[j] =  ss[m - hi + j - 1];                    // 直接利用此前已计算出的ss[]
        else {                                              // 情况二
            hi = j; lo = std::min (lo, hi);
        while ((0 <= lo) && (P[lo] == P[m - hi + lo - 1]))  // 二重循环？
            lo--;                                           // 逐个对比处于(lo, hi]前端的字符
        ss[j] = hi - lo;
      }
    printf("-- ss[] Table -------\n");
    for (int i = 0; i < m; i ++) printf("%3d", i);
    printf("\n  ");
    printString(P); printf("\n");
    for (int i = 0; i < m; i ++) printf("%3d", ss[i]);
    printf("\n\n");
    return ss;
}

// 构造好后缀(Good Suffix)位移量表：O(m)
int* buildGS(char* P) {
    int* ss = buildSS(P);                       // Suffix Size table
    size_t m = strlen(P); int* gs = new int[m]; // Good Suffix shift table
    for (size_t j=0; j<m; j++) gs[j] = m;       // 初始化
    for (size_t i=0, j=m-1; j<UINT64_MAX; j--)  // 逆向逐一扫描各字符P[j]
        if (j + 1 == ss[j])                     // 若P[0, j] = P[m - j - 1, m)，则
            while (i < m - j - 1)               // 对于P[m - j - 1]左侧的每个字符P[i]而言（二重循环？）
                gs[i++] = m - j - 1;            // m - j - 1都是gs[i]的一种选择
    for (size_t j=0; j<m-1; j++)                // 画家算法：正向扫描P[]各字符，gs[j]不断递减，直至最小
        gs[m - ss[j] - 1] = m - j - 1;          // m - j - 1必是其gs[m - ss[j] - 1]值的一种选择
    printGS(P, gs);
    delete [] ss; return gs;
}

// Boyer-Morre算法(简化版，只考虑Bad Character Shift)
int match_bm_I(char* P, char* T) {
    int* bc = buildBC(P);       // 预处理
    size_t n = strlen(T), i = 0;// 文本串长度、与模式串首字符的对齐位置
    size_t m = strlen(P);       // 模式串长度
    while (n >= i + m) {        // 在到达最右端前，不断右移模式串（可能不止一个字符）
      int j = m - 1;            // 从模式串最末尾的字符开始
      while (P[j] == T[i+j])    // 自右向左比对
         if (0 > --j) break;
      showProgress(T, P, i, j);
      if (j < 0)                // 若极大匹配后缀 == 整个模式串，则说明已经完全匹配，故
         break;                 // 返回匹配位置
      else                      // 否则，根据BC表
         i += std::max(1, j - bc[T[i+j]]); // 相应地移动模式串，使得T[i+j]与P[bc[T[i+j]]]对齐
    }
    delete [] bc;               // 销毁BC表
    return i;
}

// Boyer-Morre算法（完全版，兼顾Bad Character与Good Suffix）
int match_bm_II(char* P, char* T) {
    int* bc = buildBC(P); int* gs = buildGS(P); // 构造BC表和GS表
    size_t i = 0;                               // 模式串相对于文本串的起始位置（初始时与文本串左对齐）
    while (strlen(T) >= i + strlen(P)) {        // 不断右移（距离可能不止一个字符）模式串
        int j = strlen(P) - 1;                  // 从模式串最末尾的字符开始
        while (P[j] == T[i + j])                // 自右向左比对
            if (0 > --j) break;
        showProgress(T, P, i, j);
        printf("\n");
        if (0 > j)                              // 若极大匹配后缀 == 整个模式串（说明已经完全匹配）
            break;                              // 返回匹配位置
        else                                    // 否则，适当地移动模式串
            i += std::max(gs[j], j - bc[ T[i + j] ]); // 位移量根据BC表和GS表选择大者
    }
    delete [] gs; delete [] bc;                 // 销毁GS表和BC表
    return i;
}

#endif //  STRING_H
