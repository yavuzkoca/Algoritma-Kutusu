#include <vector>

struct connection{
	int A, B, weight;
};

int partition(std::vector<connection> &, int, int);
void qckSort(std::vector<connection> &, int, int);

class GraphCreator{
private:
	std::vector<connection> graph;
	int number_of_nodes;
	int *node_indices;
	bool weighted;
	bool directed;
	double connection_prob;
	int max_weight;
public:
	GraphCreator();
	GraphCreator(const GraphCreator &);
	GraphCreator(int, double, bool, bool, int);
	void create_node_indices();
	void print_node_indices();
	void random_initialize();
	void print_graph();
	void save_graph(const char *);
	void load_graph(const char *);
	int operator()(const int &, const int &);
	void set_connection_prob(double prob){ connection_prob = prob; }
	void set_max_weight(int weight){ max_weight = weight; }
	int get_number_of_connections(){ return graph.size(); }
	~GraphCreator();
};