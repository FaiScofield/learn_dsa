/*****************
 * 求两字符串的最长公共子序列LCS
 * 难点:
 * 1) 可能有多个最长子序列
 * 2) 可能出现歧义（同一个字母出现多次，均可以被记录）
 * 解决方法：
 * 1) 递归，从后往前，减而治之, O(2^n) or O(2^m)
 * 2) 动态规划 O(n*m)
 ****************/


#include <iostream>
#include <string.h>
#include <chrono>

using namespace std;

// 递归版
int LCS_Iter(string s1, string s2)
{
    int m = s1.size(), n = s2.size();
    if (m < 1 || n < 1) return 0;

    int a = m - 1, b = n - 1;
    int res = 0;
    string ss1, ss2;
    if (a>=0 && b>=0) {
        if (s1[a] == s2[b]) {
            res++;
            ss1 = s1.substr(0, a);
            ss2 = s2.substr(0, b);
            res += LCS_Iter(ss1, ss2);
        }
        else {
            ss1 = s1.substr(0, a+1);
            ss2 = s2.substr(0, b);
            int r1 = LCS_Iter(ss1, ss2);
            string ss3 = s1.substr(0, a);
            string ss4 = s2.substr(0, b+1);
            int r2 = LCS_Iter(ss3, ss4);
            res += max(r1, r2);
        }
    }

    return res;
}

// 动态规划（迭代版）
int LCS(string s1, string s2, string& res)
{
    int m = s1.size(), n = s2.size();
    if (m < 1 || n < 1) return 0;

    // LCS: make the table
    int a[m+1][n+1];
    for (int i=0; i<m+1; ++i) {
        for (int j=0; j<n+1; ++j) {
            // init
            if (i==0 || j==0) {
                a[i][j] = 0;
                continue;
            }

            if ( s1[i-1] == s2[j-1] )
                a[i][j] = a[i-1][j-1] + 1;
            else
                a[i][j] = max(a[i-1][j], a[i][j-1]);
        }
    }

    // output table a
    cout << "- - ";
    for (int i=0; i<n; ++i)
        cout << s2[i] << " ";
    cout << endl;
    for (int i=0; i<m+1; ++i) {
        for (int j=0; j<n+1; ++j) {
            if (i==0 && j==0)
                cout << "- ";
            else if (j == 0)
                cout << s1[i-1] << " ";

            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    // get result
    int x = a[m][n];
    int last_j = n;
    string tmpstr;
    for (int i=m; i>=0; --i) {
        for (int j=last_j; j>=0; --j) {
            if (a[i][j] == x) {
                if (a[i-1][j-1] == x-1 && a[i][j-1] == x-1 && a[i-1][j] == x-1) {
                    tmpstr.push_back(s1[i-1]);
                    last_j = j - 1;
                    x--;
                    break;
                } else
                    continue;
            } else
                break;
        }
    }
    // reverse res
    for (int i=tmpstr.size()-1; i>=0; --i)
        res.push_back(tmpstr[i]);

    return a[m][n];
}


int main(int argc, char *argv[])
{
    string res;
//    string str2 = "advantage", str1 = "didactical";
//    string str1 = "ababila", str2 = "alibaba";
    string str1 = "caaafsdfsdfdfgdfgdt", str2 = "asfhsigfsrhidgdh";

    auto t1 = chrono::steady_clock::now();
    int n = LCS(str1, str2, res);
    auto t2 = chrono::steady_clock::now();
    double dt = chrono::duration<double, ratio<1,1000>>(t2-t1).count();

    t1 = chrono::steady_clock::now();
    int m = LCS_Iter(str1, str2);
    t2 = chrono::steady_clock::now();
    double dt2 = chrono::duration<double, ratio<1,1>>(t2-t1).count();

    cout << "The longest common subsequence bewteen \"" << str1 << "\" and \"" << str2
         << "\" is: " << endl << n << ", " << res << ", cost time: "<< dt << " ms" << endl;
    cout << "Iteration version: " << endl << m << ", cost time: "<< dt2 << " s" << endl;

    return 0;
}
