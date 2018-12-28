#include "MGraph.h"
#include <iostream>
#include <math.h>

using namespace std;

MGraph::MGraph(): numVertexes(9)
{
    for (size_t i=0; i<numVertexes; ++i) {
        for (size_t j=0; j<numVertexes; ++j) {
            if (i==j)
                arc[i][j] = 0;
            else
                arc[i][j] = INFINITY;
        }
    }
    arc[0][1] = arc[1][0] = 1;
    arc[0][2] = arc[2][0] = 5;
    arc[1][2] = arc[2][1] = 3;
    arc[1][3] = arc[3][1] = 7;
    arc[1][4] = arc[4][1] = 5;
    arc[2][4] = arc[4][2] = 1;
    arc[2][5] = arc[5][2] = 7;
    arc[3][6] = arc[6][3] = 3;
    arc[4][5] = arc[5][4] = 3;
    arc[4][6] = arc[6][4] = 6;
    arc[4][7] = arc[7][4] = 9;
    arc[5][7] = arc[7][5] = 5;
    arc[6][7] = arc[7][6] = 2;
    arc[6][8] = arc[8][6] = 7;
    arc[7][8] = arc[8][7] = 4;
}
