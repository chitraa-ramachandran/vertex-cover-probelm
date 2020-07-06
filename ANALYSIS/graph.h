#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <set>
#include <list>
struct Edge{
    unsigned v1,v2;
};
typedef std::vector<unsigned> VertexVec;
typedef std::list<unsigned > VertexList;
typedef std::vector<VertexList> Adjacency_List;

struct Graph{
    std::size_t edge_num;
    Adjacency_List adjacency;

    void initialize(unsigned num_vertices);
    void add_edge(Edge e);
    void clear(unsigned v);
};

#endif
