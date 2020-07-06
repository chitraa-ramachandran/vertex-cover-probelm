#include <iostream>
#include <sstream>
#include "graph.h"
using std::toupper;
int main(int argc, char** argv)
{
	char command,character_input;
	int no_of_vertices, src_node,dest_node;
	string edge_stream, standard_input;
	char prev_choice = ' ';
	graph graph_builder;
	unsigned int vertices_1, vertices_2, temp;
	while (getline(cin, standard_input))
	{
		istringstream stream_string(standard_input);
		while (stream_string >> command) 
		{
			command = (toupper(command));
			try
			{
				switch (command)
				{
				case 'S':
				{
					stream_string >> src_node;
					stream_string >> dest_node;
					graph_builder.bellman_ford(src_node, dest_node);
					break;
				}
				case 'V':
					if (prev_choice == 'V')
					{
						throw "Vertices inuput must be followed by edge input";
					}
					else
					{
						stream_string >> no_of_vertices;
						if (no_of_vertices <= 0)
						{
							throw "Number of vertices should be of positive number";
						}
						graph_builder.initialize_graph(no_of_vertices);
						prev_choice = 'V';
						break;
					}
				case 'E':
				{
					if (prev_choice == 'E')
					{
						throw "Vertices and Edges come one after another";
					}
					else
					{
						graph_builder.clear_all_edges();
						stream_string >> edge_stream;
						istringstream edge_stream_character(edge_stream);
						edge_stream_character >> character_input;
						while (character_input != '}') 
						{
							edge_stream_character >> character_input;
							if (character_input == '}')  break;
							edge_stream_character >> temp;
							vertices_1 = temp;
							edge_stream_character >> character_input;
							edge_stream_character >> temp;
							vertices_2 = temp;
							graph_builder.edge_construction(vertices_1, vertices_2);
							edge_stream_character >> character_input;
							edge_stream_character >> character_input;
							prev_choice = 'E';
						}
						break;
					}
				}
				}
			}
			catch (const char* err)
			{
				std::cerr << "Error:" << err << endl;
			}

		}
	}
	return 0;
}
