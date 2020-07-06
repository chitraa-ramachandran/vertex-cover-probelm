#include <algorithm>
#include <iostream>
#include <memory>
#include "graph.h"
#include "minisat/core/Solver.h"
void *APPROX_VC_3(void *gp)
{
    const Graph &graph_input_string = *(const Graph *)gp;
    VertexVec &C = *new VertexVec();
    unsigned int k = 0;
    unsigned int l = 0;
    unsigned int h = graph_input_string.adjacency.size();
    bool res;
    k=(h+l)/2;

    while (l<=h)
    {

        std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
        std::vector<std::vector<Minisat::Lit>> nk_matrix(graph_input_string.adjacency.size());
        for (unsigned int i = 0; i < graph_input_string.adjacency.size(); i++)
            for (unsigned int j = 0; j < k; j++) {
                Minisat::Lit l = Minisat::mkLit(solver->newVar());
                nk_matrix[i].push_back(l);
            }
        for (unsigned int i = 0; i < k; i++) {
            Minisat::vec<Minisat::Lit> save_literal;
            for (unsigned int j = 0; j < graph_input_string.adjacency.size(); j++) {
                save_literal.push(nk_matrix[j][i]);
            }
            solver->addClause(save_literal);
        }
        for (unsigned int m = 0; m < graph_input_string.adjacency.size(); m++)
            for (unsigned int p = 0; p < k; p++)
                for (unsigned int q = p + 1; q < k; q++) {
                    solver->addClause(~nk_matrix[m][p], ~nk_matrix[m][q]);
                }
        for (unsigned int m = 0; m < k; m++)
            for (unsigned int p = 0; p < graph_input_string.adjacency.size(); p++)
                for (unsigned int q = p + 1; q < graph_input_string.adjacency.size(); q++) {
                    solver->addClause(~nk_matrix[p][m], ~nk_matrix[q][m]);
                }
        for(unsigned v1 = 0 ; v1 < graph_input_string.adjacency.size(); ++v1) {
            for (auto v2 : graph_input_string.adjacency[v1]) {
                if(v2 < v1) continue;
                Minisat::vec<Minisat::Lit> edge_lit;
                for (unsigned int w = 0; w < k; w++) {
                    edge_lit.push(nk_matrix[v1][w]);
                    edge_lit.push(nk_matrix[v2][w]);
                }

                solver->addClause(edge_lit);
            }
        }
        res = solver->solve();
        if (res )
        {
            C.clear();
            for ( unsigned int i = 0; i < graph_input_string.adjacency.size(); i++)
                for ( unsigned int j =0; j < k; j++)
                    if ( Minisat::toInt(solver->modelValue(nk_matrix[i][j])) == 0)
                    {
                        C.push_back(i);
                    }

            h = k-1;
        }
        else {
            solver.reset(new Minisat::Solver());
            l =k+1;
        }
        k = (h+l)/2;
    }
    std::sort( C.begin(), C.end(), std::less<int>());
return &C;


}

