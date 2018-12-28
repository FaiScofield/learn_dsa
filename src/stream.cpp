#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
    string s = "I love = xiao. wen wen.";
    stringstream ss(s);

    string a, b;
//    while (a != )
    ss >> a;
    cout << a << endl;
    ss >> b;
    cout << b << endl;
    ss >> a;
    cout << a << endl;

    // file
    ifstream f;
    f.open("a.txt");
    string data1, data2, data3;
    string v1, v2, v3;

    f >> data1 >> data2 >> data3;
//    f >> data1 >> data2 >> data3;
    if (data1 == "building") v1 = data3;

    cout << data1 << " " << data2 << " " << data3 << endl;
    f.close();

    return 0;
}

