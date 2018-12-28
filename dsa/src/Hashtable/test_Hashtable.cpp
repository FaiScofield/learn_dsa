
#include "Hashtable.h"
#include "../_share/util.h"
#include "../UniPrint/print.h"

#include<iostream>

using namespace std;


/******************************************************************************************
 * 测试散列表
 ******************************************************************************************/
template <typename K, typename V> // key、value
void testHashtable(int n) {
    Hashtable<K, V> ht(n);
//    print(ht);
    while (ht.size() < 4 * n) {
        printf("\n");
        switch (dice(3)) {
        case 0: { // 查找，成功率 <= 33.3%
            K key = dice((K) n * 12); // [0, 3n)范围内的key
            printf("Searching "); print(key); printf("(%04lu) :\n", hashCode (key));
            V* pValue = ht.get (key);
            pValue ? (void) printf("Found with "), print(*pValue) : (void) printf("Not found");
            printf("\n");
            break;
        }
        case 1: { // 删除，成功率 <= 33.3%
            K key = dice((K) n * 12); // [0, 3n)范围内的key
            printf("Removing "); print(key); printf("(%04lu) :\n", hashCode (key));
            ht.remove(key) ?
                (void)printf("Done\n"), print(ht) :
                (void)printf("Entry not exists\n");
            break;
        }
        default: {// 插入，成功率 == 100%
            K key = dice ((K) n * 12); V v = (V) 'A' + dice (26); // 在[0, 2n)*['A'~'Z']范围内的词条
            printf("Inserting <"); print(key); printf("(%04lu)", hashCode (key)); printf(","); print(v); printf(">\n");
            ht.put(key, v) ?
                (void) printf("Done\n"), print(ht) :
                (void) printf("Dup key\n");
            break;
        }
        } // switch
    } // while
    while (ht.size() > 0) {
        printf("\n");
        K key = dice((K) n * 12); // [0, 3n)范围内的key
        printf("Removing "); print(key); printf(" :\n");
        ht.remove (key) ?
            (void) printf("Done\n"), print(ht) :
            (void) printf("Entry not exists\n");
    }
}

/******************************************************************************************
 * 主程序
 ******************************************************************************************/
int main (int argc, char* argv[]) {
    if (2 > argc) {
        printf("Usage: %s <size of test>\a\a\n", argv[0]);
        return 1;
    }
    srand((unsigned int) time(NULL)); // 设置随机种子
    testHashtable<int, char> (atoi(argv[1])); // 元素类型可以在这里任意选择
    return 0;
}
