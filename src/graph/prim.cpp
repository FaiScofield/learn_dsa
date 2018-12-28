#include "MGraph.h"
#include <iostream>
#include <math.h>

#define MAXVEX 9

void MinSpanTreePrim(MGraph G)
{
    int min, k;
    int adjvex(MAXVEX);
    int lowcost(MAXVEX);

    // initialization
    for (int i=1; i<G.numVertexes; ++i) {
        lowcost[i] = G.arc[0][1];   // add all wight in line 0
        adjvex[i] = 0;              // index
    }

    // Min span tree
    for (int i=1; i<G.numVertexes; ++i) {
        min = INFINITY;
        j = 1;
        k = 0;

        while (j < G.numVertexes) {
            // find min weight in lowcost
            if (lowcost[j] != 0 && lowcost[j] < min) {
                min = lowcost[j];
                k = j;
            }
            ++j;
        }

        // print the min edge in current vertex
        printf("(%d, %d)", adjvex[k], k);
        lowcost[k] = 0;

        // all vertex
        for (int j=1; j<G.numVertexes; ++j) {
            lowcost[j] = G.arc[k][j];
            adjvex[j] = k;
        }
    }

}
