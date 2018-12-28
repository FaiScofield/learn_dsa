#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_set>

using namespace std;

int uniqueMorseRepresentations(vector<string>& words) {
    string dic[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",
                    ".---","-.-",".-..","--","-.","---",".--.","--.-",".-.",
                    "...","-","..-","...-",".--","-..-","-.--","--.."};

    vector<string> translation;
    int res = 0;

    // ascii a-z: 97-122
    auto iter = words.begin();
    for (; iter != words.end(); ++iter) {
        // 转成摩斯码
        string morseCode;
        for (int i=0; i<(*iter).size(); ++i) {
            int index = (*iter)[i] - 'a';
            morseCode += dic[index];
        }

        // 重复性检查
        auto ite = translation.begin();
        bool repFlag = false;
        for (; ite != translation.end(); ++ite) {
            if (*ite == morseCode) {
                repFlag = true;
                break;
            }
        }

        // 不重复的话加1
        if (!repFlag) {
            translation.push_back(morseCode);
            res++;
        }
    }

    return res;
}

// 用无序集合来存储转换后的摩斯码，可省略重复性检查额步骤
int uniqueMorseRepresentations_best(vector<string>& words) {
    vector<string> d = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." };
    unordered_set<string> s;
    for (auto& word : words) {
        string code;
        for (auto& c : word) code += d[c - 'a'];
        s.insert(code);
    }

    return s.size();
}

int main(int argc, char *argv[])
{
    vector<string> words = {"gin", "zen", "gig", "msg"};

    auto t1 = chrono::steady_clock::now();
    int res = uniqueMorseRepresentations(words);
//    int res = uniqueMorseRepresentations_best(words);
    auto t2 = chrono::steady_clock::now();
    double dt = chrono::duration_cast<chrono::duration<double> >(t2-t1).count();

    cout << "leetcode 804 answer: " << res << ", cost time: " << 1000000*dt << "us" << endl;

    return 0;
}
