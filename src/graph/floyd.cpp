#include "MGraph.h"
#include "MGraph.h"
#include <math.h>

using namespace std;

#define MAXVEX 9

typedef int Patharc[MAXVEX][MAXVEX];        // index for shortest route
typedef int ShortPathTable[MAXVEX][MAXVEX]; // sum of weight to a vertex

/**
 * @brief ShortestPathFloyd
 * @param G     graph
 * @param S     Start vertex
 * @param P     path index
 * @param D     short path table
 */
void ShortestPathFloyd(MGraph G, int S, Patharc* P, ShortPathTable* D)
{
    int k, min;

    // initialization
    for (size_t i=0; i<G.numVertexes; ++i) {
        (*P)[i][j] = i;
        (*D)[i][j] = G.arc[S][i];
    }

    // get the shortest route from (S)tart to end
    for (size_t k=0; k<G.numVertexes; ++k) {
        for (size_t i=0; i<G.numVertexes; ++i) {
            for (size_t j=0; j<G.numVertexes; ++j) {
                if ( (*D)[i][j] > (*D)[i][k] + (*D)[k][j] ) {
                    (*D)[i][j] = (*D)[i][k] + (*D)[k][j];
                    (*P)[i][j] = (*P)[i][k];    // (*P)[i][j] ?
                }

}
