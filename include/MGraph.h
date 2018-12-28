#ifndef MGRAPH_H
#define MGRAPH_H

#include <vector>

#define MAXNUM 10

struct vertex {
    unsigned int id;
    bool actived;
};


struct edge {
    unsigned int from, to;
    double weight;
    unsigned int in_degree, out_degree;
};


struct Node {
    unsigned int data;
    unsigned int in, out;
    Node* first;
};


class MGraph
{
    int type;
    unsigned int numVertexes, numEdges;
    std::vector<vertex> vertexes;
    std::vector<edge> edges;
    int arc[MAXNUM][MAXNUM];

    MGraph();
    void addVertex(vertex v) { vertexes.push_back(v); }
    void addEdge(edge e) { edges.push_back(e); }
};

#endif // MGRAPH_H
