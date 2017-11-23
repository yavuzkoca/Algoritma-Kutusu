#include <queue>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <random>

using namespace std;

// TODO: Option to create trees

struct connection{
	int A, B, weight;
};

class GraphCreator{
private:
	vector<connection> graph;
	int number_of_nodes;
	string representation;
	bool weighted;
	bool directed;
	double connection_prob;
	int max_weight;
public:
	GraphCreator(int, double, bool, bool, int);
	void random_initialize();
	void print_graph();
	int get_number_of_connections(){ return graph.size(); }
	~GraphCreator(){};
};

GraphCreator::GraphCreator(int number_of_nodes, double connection_prob, bool directed=false, bool weighted=false, int max_weight=0){
	this->graph = graph;
	this->number_of_nodes = number_of_nodes;
	this->representation = representation;
	this->weighted = weighted;
	this->directed = directed;
	this->connection_prob = connection_prob;
	this->max_weight = max_weight;
	cout << "Successfully initialized the graph." << endl;
}

void GraphCreator::random_initialize(){
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> dist_real(0,1);
	uniform_int_distribution<int> dist_int(1, max_weight);
	double prob;
	int weight;
	graph.clear();
	if(directed && weighted){
		for(int i = 1; i < number_of_nodes; ++i){
			for(int j = 0; j < number_of_nodes; ++j){
				prob = dist_real(gen);
				weight = dist_int(gen);
				connection road;
				road.A = i; road.B = j; road.weight = weight;
				if(prob < connection_prob) graph.push_back(road);
			}
		}
	}
	else if(directed && !weighted){
		for(int i = 1; i < number_of_nodes; ++i){
			for(int j = 0; j < number_of_nodes; ++j){
				prob = dist_real(gen);
				connection road;
				road.A = i; road.B = j;
				if(prob < connection_prob) graph.push_back(road);
			}
		}
	}
	else if(!directed && weighted){
		for(int i = 1; i < number_of_nodes; ++i){
			for(int j = 0; j < i; ++j){
				prob = dist_real(gen);
				weight = dist_int(gen);
				connection road;
				road.A = i; road.B = j; road.weight = weight;
				if(prob < connection_prob){
					graph.push_back(road);
					road.A = j; road.B = i;
					graph.push_back(road);
				}
			}
		}
	}
	else{
		for(int i = 1; i < number_of_nodes; ++i){
			for(int j = 0; j < i; ++j){
				prob = dist_real(gen);
				connection road;
				road.A = i; road.B = j;
				if(prob < connection_prob){
					graph.push_back(road);
					road.A = j; road.B = i;
					graph.push_back(road);
				}
			}
		}
	}
}

void GraphCreator::print_graph(){
	if(graph.size() == 0) cout << "The graph is empty." << endl;
	else{
		if(!weighted){
			for(int i = 0; i < graph.size(); ++i){
				cout << "(" << graph[i].A << ", " << graph[i].B << ")" << endl;
			}
		}
		else{
			for(int i = 0; i < graph.size(); ++i){
				cout << "(" << graph[i].A << ", " << graph[i].B << ")" << " -> " << graph[i].weight << endl;
			}
		}
	}
}
/*
namespace Matrix{
	void random_graph_initializer(bool **graph, const int &number_of_nodes){
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<double> dist(0,1);
		double prob;
	    for(int i = 0; i < number_of_nodes; ++i){
	    	for(int j = 0; j < number_of_nodes; ++j){
	    		prob = dist(gen);
	    		graph[i][j] = prob < CONNECTION_PROB ? true : false;
	    	}
	    }
	}

	void print_graph(bool **graph, const int &number_of_nodes){
		for(int i = 0; i < number_of_nodes; ++i){
			cout << int(graph[i][0]);
			for(int j = 0; j < number_of_nodes; ++j){
				cout << ' ' << int(graph[i][j]);
			}
			cout << endl;
		}
	}

	bool **create_graph(const int &num_nodes){
		bool **graph = new bool*[num_nodes];
		for(int i = 0; i < num_nodes; ++i) graph[i] = new bool[num_nodes];
		return graph;
	}

	void delete_graph(bool **graph, const int &num_nodes){
		for(int i = 0; i < num_nodes; ++i) delete[] graph[i];
		delete[] graph;
	}
}

namespace List{
	void random_graph_initializer(vector< pair<int,int> > &graph, const int &number_of_nodes){
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<double> dist(0,1);
		double prob;
		for(int i = 0; i < number_of_nodes; ++i){
			for(int j = 0; j < number_of_nodes; ++j){
				prob = dist(gen);
				if(prob < CONNECTION_PROB){
					pair<int, int> road;
					road.first = i;
					road.second = j;
					graph.push_back(road);
				}
			}
		}
	}

	void save_graph(vector< pair<int,int> > &graph, const int &number_of_nodes, const char *PATH){
		FILE *graph_file;
		graph_file = fopen(PATH, "w");
		fprintf(graph_file, "%d", number_of_nodes);
		for(int i = 0; i < graph.size(); ++i)
			fprintf(graph_file, "\n%d %d", graph[i].first, graph[i].second);
		fclose(graph_file);
	}

	int load_graph(vector< pair<int,int> > &graph, const char *PATH){
		FILE *graph_file = fopen(PATH, "r");
		int number_of_nodes;
		if(graph_file != NULL){
			fscanf(graph_file, "%d", &number_of_nodes);
			while( !feof(graph_file) ){
				int a, b;
				fscanf(graph_file, "%d %d", &a, &b);
				pair<int, int> road;
				road.first = a;
				road.second = b;
				graph.push_back(road);
			}
			fclose(graph_file);
		}
		else cout << "Unable to open the file." << endl;
		return number_of_nodes;
	}

	void print_graph(vector< pair<int,int> > &graph){
		if(graph.size() == 0) cout << "The graph is empty." << endl;
		for(int i = 0; i < graph.size(); ++i){
			cout << "(" << graph[i].first << ", " << graph[i].second << ")" << endl;
		}
	}
}*/

int main(){

	int num_nodes = 10;

	GraphCreator graph(num_nodes, 0.1, false, true, 20);
	graph.random_initialize();
	graph.print_graph();

	GraphCreator graph2(num_nodes, 0.1, true, true, 20);
	graph2.random_initialize();
	graph2.print_graph();

	cout << sizeof(long int) << endl;

	return EXIT_SUCCESS;
}