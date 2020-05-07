/******************************************************************************************
 * Test of PQ_ComplHeap & PQ_LeftHeap
 ******************************************************************************************/
#include "PQ_ComplHeap.h"
#include "PQ_LeftHeap.h"
#include "PQ_List.h"
#include "../_share/util.h"
#include "../UniPrint/print.h"

#include <unistd.h>
#include <iostream>
using namespace std;

#define DSA_PQ_COMPLHEAP

/******************************************************************************************
 * 针对基于列表、向量以及左式堆实现的优先级队列，做过程统一的测试
 ******************************************************************************************/
template <typename PQ, typename T> // 堆类型、词条类型
void testHeap(int n) {
    T* A = new T[2*n/3]; // 创建容量为2*n/3的数组，并
    for (int i = 0; i < 2*n/3; i++)
        A[i] = dice((T) 3*n); // 在其中随机生成2*n/3个词条
    printf("%d random keys created:\n", 2*n/3);

    for (int i = 0; i < 2*n/3; i++) { print(A[i]); printf(" "); }
    printf("\n");

    printf("Heap created from above:\n");
    PQ heap(A+n/6, n/3); // 批量建堆（PQ_ComplHeap实现了Robert Floyd算法）
    delete[] A;
    print(heap); sleep(1);

    while (heap.size() < n) { // 随机测试
        if (dice(100) < 70) { // 70%概率插入新词条
            T e = dice((T) 3*n);
            printf("Inserting "); print(e); printf (" ...\n");
            heap.insert(e);
            printf("Insertion done\n");
        } else { // 30%概率摘除最大词条
            if (!heap.empty()) {
                printf("Deleting max ...\n");
                T e = heap.delMax();
                printf("Deletion done with "); print(e); printf("\n");
            }
        }
        print(heap); sleep(1);
    }
    while (!heap.empty()) { // 清空
        T e = heap.delMax();
        printf("Deletion done with "); print(e); printf("\n");
        print(heap); sleep(1);
    }
}

/******************************************************************************************
 * 优先级队列测试
 ******************************************************************************************/
int main (int argc, char* argv[]) {
    if (2 > argc) {
        printf("Usage: %s <size of test>\a\a\n", argv[0]);
        return 1;
    }
    srand((unsigned int) time(NULL));

#if defined(DSA_PQ_LEFTHEAP)
   testHeap<PQ_LeftHeap<int>, int> (atoi(argv[1])); // 词条类型可以在这里任意选择
#elif defined(DSA_PQ_COMPLHEAP)
   testHeap<PQ_ComplHeap<int>, int> (atoi(argv[1])); // 词条类型可以在这里任意选择
#elif defined(DSA_PQ_LIST)
   testHeap<PQ_List<int>, int> (atoi(argv[1])); // 词条类型可以在这里任意选择
#else
    printf("PQ type not defined yet\n");
#endif

    return 0;
}
