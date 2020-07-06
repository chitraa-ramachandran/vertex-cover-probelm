#include "graph.h"
#include "avc1.h"
#include "avc2.h"
#include "minvc.h"
#include <pthread.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <memory>
#include <unistd.h>
#include <ctime>

using namespace std;
static void *(* algorithm[])(void *) = {APPROX_VC_3, APPROX_VC_1, APPROX_VC_2}; 
static const char *names[] = {"CNF-SAT-VC: ","APPROX-VC-1: ", "APPROX-VC-2: "};
void run_algorithm(Graph &graph)
{ //  clockid_t cid;
    pthread_t threads[3];
    VertexVec *output[3];
    int satisfiability;
    for(size_t i = 0; i < 3;++i) {
        satisfiability = pthread_create(&threads[i], nullptr, algorithm[i], &graph);
        if (satisfiability)
        { std::cout<<"error occured";
         exit(1); /*error happens here*/
}    }

    for(size_t i = 0; i < 3;++i) {

        pthread_join(threads[i],(void **)&output[i]);
        cout<<names[i];
        if(!output[i]) continue;
        VertexVec &C = *output[i];
        /* print the output */
        for (unsigned j=0; j < C.size(); j++){
            cout<<C[j];
            if(j + 1 != C.size()){
                cout<<',';
            }
        }
        cout << endl;
    }

    for(size_t i = 0; i < 3;++i) {
        delete(output[i]);
    }
}

void *du_inputoutput_thread(void *){
    Graph &graph = *new Graph(); //why new Graph()? why create a reference? & means reference which is only another name of the object
    char choice_made;
    string line;
    unsigned int vertices_num = 0;
    string edge_input;
    char pre_choice = '0';

    while (getline(cin, line)) {
        istringstream input_string(line);
        while (input_string >> choice_made) {
            switch (choice_made)
            {
                case 'V' :
                    if (pre_choice == 'V')
                    {
                        cerr << "Error: the first character is repeated.\n";
                        break;
                    }
                    else
                    {
                        input_string >> vertices_num;
                        graph.initialize(vertices_num);
                        pre_choice = 'V';

                        break;
                    }
                case 'E' :
                {
                    unsigned int flag_Entry = 0;
                    if ( pre_choice == 'E')
                    {
                        cerr << "Error: the first character is repeated.\n ";
                        break;
                    }
                    else
                    {
                        input_string >> edge_input;
                        istringstream input_string_edge(edge_input);
                        char edge_char;
                        unsigned int vertice_elem = 0;
                        unsigned int v1;
                        unsigned int v2;

                        input_string_edge >> edge_char;

                        while (edge_char != '}') {
                            input_string_edge >> edge_char;
                            if (edge_char == '}')
                            {
                                flag_Entry = 1;
                                break;
                            }
                            else
                            {

                                input_string_edge >> vertice_elem;
                                v1 = vertice_elem;
                                input_string_edge >> edge_char;
                                input_string_edge >> vertice_elem;
                                v2 = vertice_elem;

                                input_string_edge >> edge_char;
                                input_string_edge >> edge_char;

                                graph.add_edge({v1,v2});
                                if (v1 > vertices_num || v2 > vertices_num)
                                {
                                    cerr << "Error: point order out of range.\n";
                                    break;
                                }

                            }

                        }
                        if(flag_Entry == 1)
                        {
                            pre_choice = 'E';
                            break;
                        }
                        run_algorithm(graph);
                        pre_choice = 'E';
                        break;

                    }
                }

            }

        }

    }
    return nullptr;

}

int main(int argc, char **argv)
{   //clockid_t cid;
    int satisfiability;
    pthread_t inputoutput_thread;
    srand(time(nullptr)); // srand() in main functoin to ensure the unique random value of each time
    satisfiability = pthread_create(&inputoutput_thread, nullptr, du_inputoutput_thread, nullptr);
    if (satisfiability) return 1;
     pthread_join(inputoutput_thread,NULL);

    pthread_exit(0);
    return 1;
}















