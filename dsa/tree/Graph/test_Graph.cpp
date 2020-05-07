/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

/******************************************************************************************
 * Test of Graph
 ******************************************************************************************/

#include "Graph.h"
#include "GraphMatrix.h"
#include "../_share/util.h"
#include "../UniPrint/print.h"

#include <iostream>
#include <string.h>

using namespace std;



/******************************************************************************************
 * 生成由v个顶点、e条边构成的随机图
 ******************************************************************************************/
template <typename Tv, typename Te> // 顶点类型、边类型
void randomGraph(GraphMatrix<Tv, Te>& g, int n, int e) {
    assert(0 < e && e <= n*(n-1));
    // 顶点
    while (g.n < n) {
        Tv vertex =(Tv)('A' + dice(26)); printf("Inserting vertex <"); print(vertex); printf("> ... ");
        g.insert(vertex); printf("done\n");
    }
    // 边
    while (g.e < e) {
        int i = dice(g.n-1), j = dice(g.n-1);
        Te e = dice((Te) 3*n);
        printf("Inserting edge(%d, %d) = ", i, j); print(e); printf(" ...");
        if (g.exists(i, j))
            printf("already exists\n");
        else {
            g.insert(e, e, i, j);
            printf("done\n");
        }
    }

    for (int i = 0; i < n; i++) g.vertex(i) = 'A' + i;
//    print(g);
}

/******************************************************************************************
 * 从命令行（文件重定向）中导入图
 ******************************************************************************************/
void importGraph(GraphMatrix<char, int> & g) {
    int n; scanf("%d\n", &n); printf("%d vertices found.\n", n);
    // 插入v个顶点
    for (int i = 0; i < n; i++) {
        char vertex; scanf("%c", &vertex); printf("Inserting vertex "); print(vertex); printf(" ... ");
        g.insert(vertex); printf("done\n");
    }
    // 插入边
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int edge; scanf("%d", &edge);
            if (0 > edge) continue;
            printf("Inserting edge (%d, %d) = ", i, j); print(edge); printf(" ... ");
            g.insert(edge, edge, i, j); printf("done\n");
        }
}

/******************************************************************************************
 * 图结构的统一测试
 ******************************************************************************************/
int main(int argc, char* argv[]) {
    if (2 > argc) {
        printf("Usage: %s -random <n> <e> | -import <n> <e> < <path>\a\a\n", argv[0]);
        return -1;
    }

    // -import < ../dsa/_input/Graph_Matrix/graph.prim.0009+0028.txt > ../dsa/_output/Graph_Matrix/graph.prim.0009+0028.txt
    // -random 13 29 > ../dsa/_output/Graph_Matrix/graph.random.0013+0029.001.txt


    srand((unsigned int) time(NULL));

    GraphMatrix<char, int> g;
    if (!strcmp("-random", argv[1]))
        randomGraph<char, int>(g, atoi(argv[2]), atoi(argv[3])); // 顶点以字符编号，边为整数权重
    else if (!strcmp("-import", argv[1]))
        importGraph(g); // 从命令行（文件重定向）中导入图
    else return -1;

    printf("\n"); print(g);

//    printf("=== BFS\n");
//    g.bfs(0); print(g);

//    printf("=== BFS (PFS)\n");
//    g.pfs(0, BfsPU<char, int>()); print(g);

//    printf("=== DFS\n");
//    g.dfs(0); print(g);

//    printf("=== DFS (PFS)\n");
//    g.pfs(0, DfsPU<char, int>()); print(g);

//    printf("=== TopoSort\n");
//    Stack<char>* ts = g.tSort(0);  print(*ts); print(g); release(ts);

//    printf("=== BCC\n");
//    g.bcc(0); print(g);

//    printf("=== Prim\n");
//    g.prim(0); print(g);

//    printf("=== Prim (PFS)\n");
//    g.pfs(0, PrimPU<char, int>()); print(g);

//    printf("=== Dijkstra\n");
//    g.dijkstra(0); print(g);

//    printf("=== Dijkstra (PFS)\n");
//    g.pfs(0, DijkstraPU<char, int>()); print(g);

    return 0;
}
