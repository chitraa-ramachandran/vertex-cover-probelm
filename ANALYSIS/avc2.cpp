
#include <algorithm>
#include <iostream>
#include <memory>
#include "graph.h"

void *APPROX_VC_2(void *input) 
{
    Graph g = *(const Graph *)input;
    VertexVec &C = * new VertexVec();

    while (g.edge_num > 0) {
        unsigned vertex1_pick = 0, vertex2_pick;
        {
            size_t randomno;
 	randomno = rand() % (g.edge_num * 2);
	while (g.adjacency[vertex1_pick].size() <= randomno) {
                randomno -= g.adjacency[vertex1_pick].size();
                ++vertex1_pick;
            }
            vertex2_pick = g.adjacency[vertex1_pick].front();
        }

        C.push_back(vertex1_pick);
        C.push_back(vertex2_pick);
        g.clear( vertex1_pick );
        g.clear( vertex2_pick );
    }
    std::sort( C.begin(), C.end(), std::less<int>());
return &C;
}
