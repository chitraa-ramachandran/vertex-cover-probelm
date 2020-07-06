#include <algorithm>
#include <iostream>
#include <memory>
#include "graph.h"
#include "minisat/core/Solver.h"

void Minimum_Vertex_Cover(Graph &graph)
{
Graph &graph_builder = graph;
Vertex_vector &C = *new Vertex_vector();


    unsigned int k = 0;
    unsigned int low = 0;
    unsigned int high = graph_builder.adjacency_matrix.size();
    bool satisfy;
    k=(high+low)/2;
    while (low<=high)
    {
        std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
        std::vector<std::vector<Minisat::Lit>> ncrossk_matrix(graph_builder.adjacency_matrix.size());
        for (unsigned int i = 0; i < graph_builder.adjacency_matrix.size(); i++)
            for (unsigned int j = 0; j < k; j++) {
                Minisat::Lit literal_builder = Minisat::mkLit(solver->newVar());
                ncrossk_matrix[i].push_back(literal_builder);
            }
        // first condition
        for (unsigned int i = 0; i < k; i++) {
            Minisat::vec<Minisat::Lit> saved_literal;
            for (unsigned int j = 0; j < graph_builder.adjacency_matrix.size(); j++) {
                saved_literal.push(ncrossk_matrix[j][i]);
            }
            solver->addClause(saved_literal);
        }

// second condition
        for (unsigned int m = 0; m < graph_builder.adjacency_matrix.size(); m++)
            for (unsigned int p = 0; p < k; p++)
                for (unsigned int q = p + 1; q < k; q++) {
                    solver->addClause(~ncrossk_matrix[m][p], ~ncrossk_matrix[m][q]);
                }
//third condition
        for (unsigned int m = 0; m < k; m++)
            for (unsigned int p = 0; p < graph_builder.adjacency_matrix.size(); p++)
                for (unsigned int q = p + 1; q < graph_builder.adjacency_matrix.size(); q++) {
                    solver->addClause(~ncrossk_matrix[p][m], ~ncrossk_matrix[q][m]);
                }


//forth condition
        for(unsigned v1 = 0 ; v1 < graph_builder.adjacency_matrix.size(); ++v1) {
            for (auto v2 : graph_builder.adjacency_matrix[v1]) {
                if(v2 < v1) continue;
                Minisat::vec<Minisat::Lit> edge_literal;
                for (unsigned int w = 0; w < k; w++) {
                    edge_literal.push(ncrossk_matrix[v1][w]);
                    edge_literal.push(ncrossk_matrix[v2][w]);
                }

                solver->addClause(edge_literal);
            }
        }
        satisfy = solver->solve();
        if (satisfy )
        {
            C.clear();
            for ( unsigned int i = 0; i < graph_builder.adjacency_matrix.size(); i++)
                for ( unsigned int j =0; j < k; j++)
                    if ( Minisat::toInt(solver->modelValue(ncrossk_matrix[i][j])) == 0)
                    {
                        C.push_back(i);
                    }

            high = k-1;
        }
        else {
            solver.reset(new Minisat::Solver());
            low =k+1;
        }
        k = (high+low)/2;
    }
    std::sort( C.begin(), C.end(), std::less<int>());
    for (unsigned j=0; j < C.size(); j++){
            std::cout<<C[j];
            if(j + 1 != C.size()){
                std::cout<<' ';
            }
        }
        std::cout<<std::endl;



}
