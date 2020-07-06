#include "graph.h"


void Graph::initialize_graph(unsigned num){
    adjacency_matrix.clear();
    no_of_edges = 0;
    adjacency_matrix.resize(num,{});
}

void Graph::edge_construction(Edge edge) {
    auto &literal_1 = adjacency_matrix[edge.v1];
    auto &literal_2 = adjacency_matrix[edge.v2];
    literal_1.push_back(edge.v2);
    literal_2.push_back(edge.v1);
    no_of_edges ++;
}
