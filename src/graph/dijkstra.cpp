#include "MGraph.h"
#include <math.h>

using namespace std;

#define MAXVEX 9

typedef int Patharc[MAXVEX];        // index for shortest route
typedef int ShortPathTable[MAXVEX]; // sum of weight to a vertex

/**
 * @brief ShortestPathDijkstra
 * @param G     graph
 * @param S     Start vertex
 * @param P     path index
 * @param D     short path table
 */
void ShortestPathDijkstra(MGraph G, int S, Patharc* P, ShortPathTable* D)
{
    int k, min;
    int final[MAXVEX];  // 1 when done

    // initialization
    for (size_t i=0; i<G.numVertexes; ++i) {
        final[i] = 0;
        (*P)[i] = 0;
        (*D)[i] = G.arc[S][i];
    }
    (*D)[S] = 0;
    final[S] = 1;

    // get the shortest route from (S)tart to end
    for (size_t i=1; i<G.numVertexes; ++i) {
        min = INFINITY;
        for (size_t j=0; j<G.numVertexes; ++j) {
            if (!final[j] && (*D)[j] < min) {
                k = j;
                min = (*D)[j];
            }
        }
        final[k] = 1;

        // overwrite the shortest route and distance
        for (size_t l=0; l<G.numVertexes; ++l) {
            if ( !final[l] && (min + G.arc[k][l] < (*D)[l]) ) {
                (*D)[l] = min + G.arc[k][l];
                (*P)[l] = k;    // front index
            }
        }
    }
}
