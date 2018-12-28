#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// 删除无序表时，可将待删除元素的值替换为表末元素的值，再删去表末元素即可
int main(int argc, char *argv[])
{
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(10);
    nums.push_back(101);
    nums.push_back(111);
    nums.push_back(11);
    nums.push_back(15);
    nums.push_back(81);
    nums.push_back(51);
    nums.push_back(41);
    nums.push_back(31);
    nums.push_back(91);
    nums.push_back(551);
    nums.push_back(521);
    nums.push_back(121);
    nums.push_back(781);
    nums.push_back(1111);
    vector<int> nums2(nums);

    auto t1 = chrono::steady_clock::now();
    auto iter = nums.begin() + 5;
    nums.erase(iter);
    auto t2 = chrono::steady_clock::now();
    double dt = chrono::duration<double, ratio<1,1000000>>(t2-t1).count();
    cout << "time cost for erase: " << dt << endl;
    for (auto& n:nums) cout << n << ", "; cout << endl;


    t1 = chrono::steady_clock::now();
    int tmp = nums2[5];
    iter = nums.end();
    nums2[5] = *iter;
    nums2.pop_back();
    t2 = chrono::steady_clock::now();
    dt = chrono::duration<double, ratio<1,1000000>>(t2-t1).count();
    cout << "time cost for erase: " << dt << endl;
    for (auto& n:nums2) cout << n << ", "; cout << endl;

    return 0;
}
