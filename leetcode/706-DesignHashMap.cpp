#include <iostream>
#include <vector>

using namespace std;

struct MyList {
    int key;
    int value;
    MyList *next;
    MyList() { key = value = -1; next = NULL; }
};

class MyHashMap {
public:
    /** Initialize your data structure here. */
    MyHashMap() {
        data = new int[1000000];
        for (int i=0; i<1000000; ++i)
            data[i] = -1;
    }

    /** value will always be positive. */
    void put(int key, int value) {
        if (key < 0 || key > 10000)
            return;
        data[key] = value;
    }

    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        return data[key];
    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        data[key] = -1;
    }

    int hash(int key) {
        return key % 1000000;
    }

private:
    int* data;
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap obj = new MyHashMap();
 * obj.put(key,value);
 * int param_2 = obj.get(key);
 * obj.remove(key);
 */


int main(int argc, char *argv[])
{
    MyHashMap hashMap;
    hashMap.put(1, 1);
    hashMap.put(2, 2);
    hashMap.get(1);             // returns 1
    hashMap.get(3);             // returns -1 (not found)
    hashMap.put(2, 1);          // update the existing value
    hashMap.get(2);             // returns 1
    hashMap.remove(2);          // remove the mapping for 2
    hashMap.get(2);             // returns -1 (not found)


    return 0;
}
