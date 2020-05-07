/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

/******************************************************************************************
 * Test of queue
 ******************************************************************************************/
#include "Queue.h"
#include "../UniPrint/print.h"
#include "../_share/util.h"

int testID = 0; // 测试编号

/******************************************************************************************
* 测试栈
******************************************************************************************/
template <typename T>
void testQueue(int n) {
    Queue<T> Q;
    printf ("\n  ==== Test %2d. Growing queue\n", testID++);
    while (Q.size() < n) {
        (Q.empty() || 30<dice(100)) ?
        Q.enqueue(dice((T)2*n)) : // 70%入队
        (void)Q.dequeue(); // 30%出队
        PRINT(Q);
    }
    printf ("\n  ==== Test %2d. Shrinking queue\n", testID++);
    while (!Q.empty()) {
        70 < dice(100) ?
        Q.enqueue(dice((T)2*n)) : // 30%入队
        (void)Q.dequeue(); // 70%出队
        PRINT(Q);
    }
}

/******************************************************************************************
 * 测试队列
 ******************************************************************************************/
int main (int argc, char* argv[]) {
    if (2 > argc) {
        printf ("Usage: %s <size of test>\a\a\n", argv[0]);
        return 1;
    }
    srand((unsigned int)time(NULL));

    testQueue<int>(atoi(argv[1]));

    return 0;
}
