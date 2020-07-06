
#include <algorithm>
#include <iostream>
#include <memory>
#include "graph.h"

void *APPROX_VC_1(void *input)
{
    Graph g = *(const Graph *)input; 
    VertexVec &C = *new VertexVec(); 


    while(g.edge_num > 0){
        auto v = std::max_element(
                g.adjacency.begin(),g.adjacency.end(),
                [](VertexList &l1, VertexList &l2)->bool{ return l1.size()<l2.size(); }
        );
        unsigned i = (unsigned)(v-g.adjacency.begin()); 
        C.push_back(i);
        g.clear(i);
    }
    std::sort( C.begin(), C.end(), std::less<int>());
    return &C;

}

