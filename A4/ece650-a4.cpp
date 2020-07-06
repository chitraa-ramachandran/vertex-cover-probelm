#include <iostream>
#include <sstream>
#include "graph.h"
#include "minvc.h"

using std::toupper;

int main(int argc, char **argv)
{
    Graph &graph_builder = *new Graph();
    char character_input;
    string standard_input;
    unsigned int no_of_vertices = 0;
    string edge_stream;
    char prev_choice = ' ';

    while (getline(cin, standard_input))  
   {
        istringstream stream_string(standard_input);
        while (stream_string >> character_input) 
       {
            character_input=(toupper(character_input));
	    try
	    {
            switch (character_input)
            {
                case 'V' :
                    if (prev_choice == 'V')
                    {
                        cerr << "Error: V must be followed by E only.\n";
                        break;
                    }
                    else
                    {
                        stream_string >> no_of_vertices;
			if(no_of_vertices <= 0)
				{
					throw "Invalid number of vertices";
				}		
                        graph_builder.initialize_graph(no_of_vertices);
                        prev_choice = 'V';
                        break;

                    }

                case 'E' :
                {
                    unsigned int flag_Entry = 0;
                    if ( prev_choice == 'E')
                    {
                        cerr << "Error: V and E always occur together.\n ";
                        break;
                    }
                    else
                    {
                        stream_string >> edge_stream;
                        istringstream edge_stream_character(edge_stream);
                        char edg_char;
                        unsigned int temp = 0;
                        unsigned int v1;
                        unsigned int v2;

                        edge_stream_character >> edg_char;

                        while (edg_char != '}') 
                        {
                            edge_stream_character >> edg_char;
                            if (edg_char == '}')
                            {
                                flag_Entry = 1;
                                break;
                            }
                            else
                            {

                                edge_stream_character >> temp;
                                v1 = temp;
                                edge_stream_character >> edg_char;

                                edge_stream_character >> temp;
                                v2 = temp;

                                edge_stream_character >> edg_char;
                                edge_stream_character >> edg_char;
                                if (v1 >= no_of_vertices || v2 >= no_of_vertices)
                                {
                                    cerr << "Error: Vertex out of range.\n";
				    graph_builder.adjacency_matrix.clear();
                                    break;
                                }
                                graph_builder.edge_construction({v1,v2});
                            }

                        }
                        if(flag_Entry == 1)
                        {
                            prev_choice = 'E';
                            break;
                        }
			Minimum_Vertex_Cover(graph_builder);
                        prev_choice = 'E';
                        break;
                    }
                }

            }
}
		catch (const char* err)
               {
                cerr << "Error:" << err << endl;
		}
        }

    }
return 0;
}
