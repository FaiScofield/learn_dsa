#include <iostream>

using namespace std;


bool flag = true;

int climbStairs(int n) {
    if (2 >= n) return n;

    int res[n+1];
    res[1] = 1;
    res[2] = 2;
    for (int i=3; i<=n; ++i)
        res[i] = res[i-1] + res[i-2];

    return res[n];
}

int main(int argc, char *argv[])
{
    int n;
    cout << "Please input the tatal number of stairs: ";
    cin >> n;
    cout << "Tatal ways of climbing the stairs: " << climbStairs(n) << endl;

    return 0;
}

