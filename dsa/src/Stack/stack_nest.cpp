#include "Stack.h"
#include <string.h>
#include <iostream>

using namespace std;

// 表达式括号匹配检查，可兼顾三种括号
bool paren(const char exp[], int lo, int hi) {
    Stack<char> S; // 使用栈记录已发现但尚未匹配的左括号
    // 逐一检查当前字符
    for (int i = lo; i <= hi; i++) {
        // 左括号直接进栈；右括号若与栈顶失配，则表达式必不匹配
        switch (exp[i]) {
        case '(': case '[': case '{': S.push (exp[i]); break;
        case ')': if ((S.empty()) || ('(' != S.pop())) return false; break;
        case ']': if ((S.empty()) || ('[' != S.pop())) return false; break;
        case '}': if ((S.empty()) || ('{' != S.pop())) return false; break;
        default: break; // 非括号字符一律忽略
        }
//        displayProgress(exp, i, S);
    }
    return S.empty(); // 整个表达式扫描过后，栈中若仍残留（左）括号，则不匹配；否则（栈空）匹配
}



/******************************************************************************************
 * 检查表达式括号是否匹配
 ******************************************************************************************/
int main (int argc, char* argv[]) {
// 检查参数
    if (2 > argc) { // 至少要提供一个待检查的字符串
        fprintf(stderr, "\nUsage: %s <string#1> <string#2> ... \n", argv[0]);
        fprintf(stderr, "For example %s (a[i-1][j+1])+a[i+1][j-1])*2\n", argv[0]);
        return -1;
    }
    // 逐一检查各串是否匹配
    for (int i = 1; i < argc; i++) {
        char* s = argv[i];
        printf("\n检查：%s\n", s);
        paren(s, 0, strlen(s)-1) ?
            printf("\n%s: 匹配\n", s) :
            printf("\n%s: 不匹配\n", s);
    }

    return 0;
}
