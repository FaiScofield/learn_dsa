#include <iostream>
#include <vector>

using namespace std;

#define taxStart 3500

vector<unsigned int> taxLevel = {0, 1500, 4500, 9000, 35000, 55000, 80000};
vector<unsigned int> taxRatio = {3, 10, 20, 25, 30, 35, 45};
vector<unsigned int> deduction = {0, 105, 555, 1005, 2755, 5505, 13505};

// 计算收入对应的纳税等级
int getTaxLevel(unsigned int n)
{
    unsigned int m = n - taxStart;  // 应纳税所得额
    int k = taxRatio.size();        // 纳税等级总数

    if (0 == m) return 0;
    for (int i=0; i<k-1; ++i)
        if (m > taxLevel[i] && m <= taxLevel[i+1])
            return i;

    if (m > taxLevel[k-1])
        return k-1;
}


unsigned int tax(unsigned int income)
{
    int l = getTaxLevel(income);
    unsigned int res = (income - taxStart) * taxRatio[l]/100 - deduction[l];

    return res;
}



int main(int argc, char *argv[])
{
    unsigned int income = 14000;

    cout << "tax for income: " << income << " is: " << tax(income) << endl;

    return 0;
}
