#include "graph.h"
#include "iostream"
void graph::initialize_graph(unsigned int no_of_vertices)
{
	int iter = 0;
	edge.clear();
	vertices_number = no_of_vertices;
	adjaceny_matrix.clear();
	adjaceny_matrix.resize(vertices_number);
	for (auto& i : adjaceny_matrix)
	{
		iter++;
		i.resize(vertices_number, INDEFINITE);
	}
}
void graph::clear_all_edges() 
{
	int count=0;
	for (auto& i : adjaceny_matrix)
		for (auto& j : i)
		{
			j = INDEFINITE;
			count++;
		}
	edge.clear();
}
void graph::edge_construction(unsigned int vertices_1, unsigned int vertices_2)
{
	if (vertices_1 == vertices_2)
		throw "self loop is not allowed!";
	else if (vertices_1 >= vertices_number || vertices_2 >= vertices_number)
		throw "The vertex number should be between the range of 0 to vertex_number-1 given";
	else
	{
		adjaceny_matrix[vertices_1][vertices_2] = 1;
		adjaceny_matrix[vertices_2][vertices_1] = 1;
	}
}
int minimum_distance(unsigned int current_dist, unsigned int minimum_distance)
{
	if (current_dist == INDEFINITE)
	{
		return INDEFINITE;
	}
	else
	{
		return minimum_distance + current_dist;
	}
}
void graph::bellman_ford(unsigned int src_node, unsigned int dest_node) 
{
	edge.clear();
	unsigned int new_dist,min,k;
	unsigned int visited[vertices_number], dist[vertices_number];
	if (src_node >= vertices_number || dest_node >= vertices_number)
	{
		throw "The vertex number should be between the range of 0 to vertex_number-1 given";
	}
	for (unsigned int i = 0; i < vertices_number; i++) {
		visited[i] = 0;
		dist[i] = adjaceny_matrix[src_node][i];
	}
	visited[src_node] = 1;
	dist[src_node] = 0;
	for (unsigned int i = 1; i < vertices_number; i++) 
	{
		min = INDEFINITE;
	    k = 0;
		for (unsigned int j = 0; j < vertices_number; j++)
		{
			if (visited[j] == 0 && dist[j] < min) 
			{
				min = dist[j];
				k = j;
			}
		}
		visited[k] = 1;
		for (unsigned int j = 0; j < vertices_number; j++)
		{
			new_dist = minimum_distance(adjaceny_matrix[k][j], min);
			if (visited[j] == 0 && (new_dist < dist[j])) 
			{
				dist[j] = new_dist;
			}
		}
	}
	if (dist[dest_node] == INDEFINITE)
	{
		throw "There is no path to this destination!";
	}
	unsigned int ver = dest_node;
	while (dist[ver] > 0) {
		edge.push_back(ver);
		for (size_t i = 0; i < vertices_number; ++i)
		{
			if (adjaceny_matrix[ver][i] < INDEFINITE &&
				dist[i] + adjaceny_matrix[ver][i] == dist[ver])
			{
				ver = i;
				break;
			}
		}
	}
	edge.push_back(ver);
	for (auto mk = edge.rbegin(); mk != edge.rend(); mk++)
	{
		std::cout << *mk;
		if (mk != edge.rend() - 1) {
			std::cout << "-";
		}
		else
			std::cout << "\n";
	}
}

