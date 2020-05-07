#include "Stack.h"
#include <iostream>

using namespace std;



// 十进制正整数n到base进制的转换（递归版）
// 0 < n, 1 < base <= 16，新进制下的数位符号，可视base取值范围适当扩充
// 新进制下由高到低的各数位，自顶而下保存于栈S中
void convert(Stack<char>& S, int n, int base) {
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    if (0 < n) {                    // 在尚有余数之前，反复地
        S.push(digit[n%base]);      // 逆向记录当前最低位，
        convert(S, n/base, base);   // 再通过递归得到所有更高位
    }
}


/******************************************************************************************
 * 进制转换
 ******************************************************************************************/
int main (int argc, char* argv[]) {
    // 参数检查
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <integer> <base>" << endl;
        return -1;
    }
    for (int i = 1; i < argc; i += 2) {
//        system("cls");
        int n = atoi(argv[i]); // 待转换的十进制数
        if (0 >= n) {
            cout << "But " << n << " is not a positive integer" << endl;
            return -2;
        }
        int base = atoi(argv[i+1]); // 目标进制
        if (2 > base || base > 16) {
            cout << "But " << base << " is not between 2 and 16" << endl;
            return -2;
        }

        Stack<char> S; // 用栈记录转换得到的各数位
        convert(S, n, base); // 进制转换
        printf("%d_(10) = ", n);
        while (!S.empty())
            printf("%c", S.pop()); // 逆序输出栈内数位，即正确结果

        printf("_(%d)\n", base);
    }

    return 0;
}
