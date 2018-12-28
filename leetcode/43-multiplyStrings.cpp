#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_set>
#include <math.h>
#include <cstdlib>

using namespace std;


string multiply_best(string num1, string num2) {
    string res;
    int n1 = num1.size(), n2 = num2.size();
    int k = n1 + n2 - 2, carry = 0; // carry进位

    // 两数之间的各个位数相乘
    vector<int> v(n1+n2, 0);
    for (int i=0; i<n1; ++i) {
        for (int j=0; j<n2; ++j)
            v[k-i-j] += (num1[i] - '0') * (num2[j] - '0');
    }

    // 调整进位
    for (int i=0; i<n1+n2; ++i) {
        v[i] += carry;
        carry = v[i] / 10;
        v[i] %= 10;
    }

    // 去掉开头的0
    int i = n1 + n2 - 1;    // last index in v[i]
    while (v[i] == 0) --i;
    if (i < 0) return "0";
    while (i >= 0) res.push_back(v[i--] + '0');

    return res;
}

int main(int argc, char *argv[])
{
    string s1 = "498828660196";
    string s2 = "840477629533";    // ""419254329864656431168468"" 10^220

    cout << multiply_best(s1, s2) << endl;
    return 0;
}

