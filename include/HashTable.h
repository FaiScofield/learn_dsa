#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <math.h>

#define HASH_SIZE 12

typedef struct {
    int *elem;  // 数据元素的基址，动态分配数组
    int count;  // 当前数据元素的个数
}HashTable;

// 初始化hash表
int initHashTable(HashTable *H)
{
    H->count = HASH_SIZE;
    H->elem = (int *)malloc(HASH_SIZE * sizeof(int));

    if (!H->elem)
        return -1;

    for (int i=0; i<HASH_SIZE; ++i)
        H->elem[i] = nan;

    return 0;
}

// 使用除留余数法结算hash地址
int hash(int key)
{
    return key % HASH_SIZE;
}

// 插入关键字到hash表中
void insertHash(HashTable *H, int key)
{
    int addr = hash(key);
    while (H->elem[addr] != nan)        // 如果不为空，说明冲突出现
        addr = (addr + 1) % HASH_SIZE;  // 用开放定址法的线性探测解决冲突

    H->elem[addr] = key;
}

// hash表查找关键字
int searchHash(HashTable *H, int key, int *addr)
{
    *addr = hash(key);
    while (H->elem[*addr] != key) {     // 出现冲突
        *addr = (*addr + 1) % HASH_SIZE;
        // 查找至最后一个元素，或回到原点，说明key值不存在此表内
        if (H->elem[*addr] == nan || *addr == hash(key))
            return -1;
    }

    return 0;
}


#endif // HASHTABLE_H
