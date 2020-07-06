#include <vector>
using namespace std;
class graph 
{
#define INDEFINITE   (~(0x1<<31))
private:
	unsigned int vertices_number;
	vector<vector<unsigned int>> adjaceny_matrix;
	vector<unsigned> edge;
public:
	void initialize_graph(unsigned int no_of_vertices);
	void clear_all_edges();
	void edge_construction(unsigned int vertices_1, unsigned int vertices_2);
	void bellman_ford(unsigned int src_node, unsigned int dest_node);
};
