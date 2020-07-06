#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <set>
#include <list>

struct Edge{
    unsigned v1,v2;
};

typedef std::vector<unsigned> Vertex_vector;
typedef std::list<unsigned > Vertex_Adjacency_list;
typedef std::vector<Vertex_Adjacency_list> Adjacency_Traversal_list;

struct Graph{
    std::size_t no_of_edges;
    Adjacency_Traversal_list adjacency_matrix;
    void initialize_graph(unsigned vertices_number);
    void edge_construction(Edge edge);
    void clear(unsigned vertex);
};

#endif
  
