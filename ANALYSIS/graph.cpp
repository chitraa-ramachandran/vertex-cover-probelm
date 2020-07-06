#include "graph.h"
#include <algorithm>

void Graph::initialize(unsigned n){
    adjacency.clear();
    edge_num = 0;
    adjacency.resize(n,{});
}

void Graph::add_edge(Edge e) {
    auto &l1 = adjacency[e.v1];
    auto &l2 = adjacency[e.v2];
    l1.push_back(e.v2);
    l2.push_back(e.v1);
    edge_num ++;
}

void Graph::clear(unsigned v){
    if(v >= adjacency.size()) return;
    for(auto u : adjacency[v]){
        auto &l2 = adjacency[u];
        auto i2 = std::find(l2.begin(),l2.end(),v);
        if(i2 != l2.end()){
            l2.erase(i2);
            --edge_num;
        }
    }
    adjacency[v].clear();
}



