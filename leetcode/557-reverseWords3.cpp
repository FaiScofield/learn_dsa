#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string reverseWords(string s) {
    int num = 1;
    int size = s.length();
    for(int i=0; i<size; i++){
        if(s[i] == ' ')
            num++;
    }

    vector<string> str(num);

    int n=0;
    for(int i=0; i<size; i++){
        if (s[i] == ' ')
            n++;
        else {
            str[n].push_back(s[i]);
        }
    }


    string res;
    for(int i=0; i<num; i++){
        reverse(str[i].begin(), str[i].end());
        res += str[i] + " ";
    }
    res.pop_back();

    return res;
}

int main(int argc, char *argv[])
{
    string input = "Let's take LeetCode contest";
    string output = reverseWords(input);

    cout << "Answer of 557-reverseWords3: " << output << endl;
    return 0;
}
