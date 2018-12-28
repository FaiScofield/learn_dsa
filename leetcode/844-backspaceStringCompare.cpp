#include <stack>
#include <string>
#include <iostream>

using namespace std;

bool backspaceCompare(string S, string T) {
    stack<char> sta1, sta2;
    for (int i=0; i<S.length(); ++i) {
        if (S[i] != '#')
            sta1.push(S[i]);
        else if (!sta1.empty())
            sta1.pop();
    }
    for (int i=0; i<T.length(); ++i) {
        if (T[i] != '#')
            sta2.push(T[i]);
        else if (!sta2.empty())
            sta2.pop();
    }

    if (sta1.size() != sta2.size()) return false;
    while (!sta1.empty() && !sta2.empty()) {
        if (sta1.top() != sta2.top())
            return false;
        sta1.pop(); sta2.pop();
    }

    return true;
}

int main(int argc, char *argv[])
{

    string S = "bxj##tw", T = "bxj###tw";
    cout << "Answer of 844 is: " << backspaceCompare(S, T) << endl;
    return 0;
}
