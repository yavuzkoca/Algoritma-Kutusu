#include "GraphCreator.h"

#include <iostream>
#include <random>

#include <stdlib.h>

using namespace std;

int partition(vector<connection> &graph, int beg, int end){

	mt19937 gen;
	gen.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist(beg, end);

	int pivot_index = dist(gen);
	connection pivot = graph[pivot_index];

	int lil, big;
	connection temp;

	graph[pivot_index] = graph[beg];
	graph[beg] = pivot;

	lil = beg + 1;
	big = end;

	while(lil != big){
		if(graph[lil].A < pivot.A){
			++lil;
		}
		else{
			temp = graph[lil];
			graph[lil] = graph[big];
			graph[big] = temp;
			--big;
		}
	}
	if(graph[lil].A > pivot.A){
		--big;
		--lil;
	}
	graph[beg] = graph[lil];
	graph[lil] = pivot;
	return lil;
}

void qckSort(vector<connection> &graph, int beg, int end){
	if(beg < end){
		int pivot_index = partition(graph, beg, end);
		qckSort(graph, beg, pivot_index - 1);
		qckSort(graph, pivot_index + 1, end);
	}
}

GraphCreator::GraphCreator(){
	connection_prob = -1;
	node_indices = NULL;
	cout << "Successfully initialized the graph." << endl;
}

GraphCreator::GraphCreator(const GraphCreator &graph_in){
	node_indices = NULL;
	this->number_of_nodes = graph_in.number_of_nodes;
	this->weighted = graph_in.weighted;
	this->directed = graph_in.directed;
	this->connection_prob = graph_in.connection_prob;
	this->max_weight = graph_in.max_weight;
	cout << "Successfully initialized the graph." << endl;
}

GraphCreator::GraphCreator(int number_of_nodes, double connection_prob, bool directed=false, bool weighted=false, int max_weight=-1){
	node_indices = NULL;
	this->number_of_nodes = number_of_nodes;
	this->weighted = weighted;
	this->directed = directed;
	this->connection_prob = connection_prob;
	this->max_weight = max_weight;
	cout << "Successfully initialized the graph." << endl;
}

void GraphCreator::create_node_indices(){
	if(node_indices != NULL) delete[] node_indices;
	node_indices = new int[number_of_nodes];
	for(int i = 0; i < number_of_nodes; ++i) node_indices[i] = -1;
	int node = -1;
	for(int i = 0; i < graph.size(); ++i){
		if( graph[i].A != node ){
			node = graph[i].A;
			node_indices[node] = i;
		}
	}
}

void GraphCreator::print_node_indices(){
	if(node_indices == NULL){
		cout << "ERROR(Printing node indices): To print them first you must create the node indices." << endl;
		return;
	}
	for(int i = 0; i < number_of_nodes; ++i) cout << node_indices[i] << endl;
}

void GraphCreator::random_initialize(){
	if( connection_prob == double(-1) ){
		cout << "ERROR: You must set a connection probability before random initialize." << endl;
		return;
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> dist_real(0,1);
	uniform_int_distribution<int> dist_int(1, max_weight);
	double prob;
	int weight;
	graph.clear();
	if(directed && weighted){
		if( max_weight == -1 ){
			cout << "ERROR: You must set a max connection weight before weighted random initialization." << endl;
			return;
		}
		for(int i = 0; i < number_of_nodes; ++i){
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
		for(int i = 0; i < number_of_nodes; ++i){
			for(int j = 0; j < number_of_nodes; ++j){
				prob = dist_real(gen);
				connection road;
				road.A = i; road.B = j;
				if(prob < connection_prob) graph.push_back(road);
			}
		}
	}
	else if(!directed && weighted){
		if( max_weight == -1 ){
			cout << "ERROR: You must set a max connection weight before weighted random initialization." << endl;
			return;
		}
		for(int i = 0; i < number_of_nodes; ++i){
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
		for(int i = 0; i < number_of_nodes; ++i){
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
	qckSort(graph, 0, graph.size() - 1);
}

void GraphCreator::add_connection(const int &A, const int &B){
	if(A == B){
		cout << "ERROR(Adding connection): You cannot connect a node to itself." << endl;
		return;
	}
	if(node_indices[A] == -1){
		connection new_connection;
		new_connection.A = A; new_connection.B = B;
		graph.push_back(new_connection);
		if(directed){
			new_connection.A = B; new_connection.B = A;
			graph.push_back(new_connection);
		}
	}
	if(A == number_of_nodes -1){
		bool exists = false;
		for(int k = node_indices[A]; k < graph.size(); ++k){
			if( graph[k].B == B ){
				exists = true;
				break;
			}
		}
		if(!exists){
			connection new_connection;
			new_connection.A = A; new_connection.B = B;
			graph.push_back(new_connection);
			if(directed){
				new_connection.A = B; new_connection.B = A;
				graph.push_back(new_connection);
			}
		}
	}
	else{
		int end = A + 1;
		while(node_indices[end] == -1){
			++end;
		}
		bool exists = false;
		for(int k = node_indices[A]; k < node_indices[end]; ++k){
			if( graph[k].B == B ){
				exists = true;
				break;
			}
		}
		if(!exists){
			connection new_connection;
			new_connection.A = A; new_connection.B = B;
			graph.push_back(new_connection);
			if(directed){
				new_connection.A = B; new_connection.B = A;
				graph.push_back(new_connection);
			}
		}
	}
	qckSort(graph, 0, graph.size() - 1);
	create_node_indices();
}

void GraphCreator::add_connection(const int &A, const int &B, const int &weight){
	if(A == B){
		cout << "ERROR(Adding connection): You cannot connect a node to itself." << endl;
		return;
	}
	if(node_indices[A] == -1){
		connection new_connection;
		new_connection.A = A; new_connection.B = B; new_connection.weight = weight;
		graph.push_back(new_connection);
		if(directed){
			new_connection.A = B; new_connection.B = A;
			graph.push_back(new_connection);
		}
	}
	if(A == number_of_nodes -1){
		bool exists = false;
		for(int k = node_indices[A]; k < graph.size(); ++k){
			if( graph[k].B == B ){
				graph[k].weight = weight;
				exists = true;
				break;
			}
		}
		if(!exists){
			connection new_connection;
			new_connection.A = A; new_connection.B = B; new_connection.weight = weight;
			graph.push_back(new_connection);
			if(directed){
				new_connection.A = B; new_connection.B = A;
				graph.push_back(new_connection);
			}
		}
	}
	else{
		int end = A + 1;
		while(node_indices[end] == -1){
			++end;
		}
		bool exists = false;
		for(int k = node_indices[A]; k < node_indices[end]; ++k){
			if( graph[k].B == B ){
				graph[k].weight = weight;
				exists = true;
				break;
			}
		}
		if(!exists){
			connection new_connection;
			new_connection.A = A; new_connection.B = B; new_connection.weight = weight;
			graph.push_back(new_connection);
			if(directed){
				new_connection.A = B; new_connection.B = A;
				graph.push_back(new_connection);
			}
		}
	}
	qckSort(graph, 0, graph.size() - 1);
	create_node_indices();
}

bool GraphCreator::remove_connection_pseudo(const int &A, const int &B){ // TODO: MIRROR ERASE BOTH WAYS
	if(node_indices[A] == -1) return false; // There is no connection from A node
	bool erased = false; int k=-2;
	if(A == number_of_nodes - 1){ // If A is the last node
		for(k = node_indices[A]; k < graph.size(); ++k){ // Start from the start of from A connections go until the end
			if( graph[k].B == B ){ // If found a connection from A to B
				graph[k].weight = 0; erased = true; break; // Delete the connection also set erased flag to true
			}
		}
		if(!erased) return false;
		// If not erased return because you already looked for every node possible and couldn't find a match
	}

	if(!erased){ // If not erased look for the end of the from A connections
		int end = A + 1; // Start from the next node
		while(node_indices[end++] == -1); // While that node does not exist look for the next from node connections
		--end;
		for(k = node_indices[A]; k < node_indices[end]; ++k){ // Start from the begining of from A connections to their end
			if( graph[k].B == B ){ // If total match
				graph[k].weight = 0; erased = true; break; // Remove the connection
			}
		}
		if(!erased) return false; // If couldn't find a connection then no match found
	}
	if(graph[node_indices[A]].A != A){ // If the is no from A connections left then set the node index to -1
		node_indices[A] = -1;
	}
	for(int k = A + 1; k < number_of_nodes; ++k){ // For all nodes after the removed shift the indices
		if(node_indices[k] != -1) --node_indices[k];
	}
	return true; // Removed
}


bool GraphCreator::remove_connection_real(const int &A, const int &B){ // TODO: MIRROR ERASE BOTH WAYS
	if(node_indices[A] == -1) return false; // There is no connection from A node
	bool erased = false; int k=-2;
	if(A == number_of_nodes - 1){ // If A is the last node
		for(k = node_indices[A]; k < graph.size(); ++k){ // Start from the start of from A connections go until the end
			if( graph[k].B == B ){ // If found a connection from A to B
				graph.erase(graph.begin() + k); erased = true; break; // Delete the connection also set erased flag to true
			}
		}
		if(!erased) return false;
		// If not erased return because you already looked for every node possible and couldn't find a match
	}

	if(!erased){ // If not erased look for the end of the from A connections
		int end = A + 1; // Start from the next node
		while(node_indices[end++] == -1); // While that node does not exist look for the next from node connections
		--end;
		for(k = node_indices[A]; k < node_indices[end]; ++k){ // Start from the begining of from A connections to their end
			if( graph[k].B == B ){ // If total match
				graph.erase(graph.begin() + k); erased = true; break; // Remove the connection
			}
		}
		if(!erased) return false; // If couldn't find a connection then no match found
	}
	if(graph[node_indices[A]].A != A){ // If the is no from A connections left then set the node index to -1
		node_indices[A] = -1;
	}
	for(int k = A + 1; k < number_of_nodes; ++k){ // For all nodes after the removed shift the indices
		if(node_indices[k] != -1) --node_indices[k];
	}
	return true; // Removed
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

void GraphCreator::save_graph(const char *PATH){
	FILE *graph_file = fopen(PATH, "w");
	if(graph_file != NULL){
		fprintf(graph_file, "%d %d %d", number_of_nodes, int(weighted), int(directed));
		if(weighted){
			for(int i = 0; i < graph.size(); ++i){
				fprintf(graph_file, "\n%d %d %d", graph[i].A, graph[i].B, graph[i].weight);
			}
		}
		else{
			for(int i = 0; i < graph.size(); ++i){
				fprintf(graph_file, "\n%d %d", graph[i].A, graph[i].B);
			}
		}
		fclose(graph_file);
	}
	else{
		cout << "ERROR: Couldn't open the file to save it. Graph is not saved!" << endl;
	}
}

void GraphCreator::load_graph(const char *PATH){
	FILE *graph_file = fopen(PATH, "r");
	if(graph_file != NULL){
		int temp_weighted, temp_directed;
		fscanf(graph_file, "%d %d %d", &number_of_nodes, &temp_weighted, &temp_directed);
		weighted = temp_weighted == 1 ? true : false;
		directed = temp_directed == 1 ? true : false;
		if(weighted){
			while(!feof(graph_file)){
				connection new_connection;
				fscanf(graph_file, "%d %d %d", &new_connection.A, &new_connection.B, &new_connection.weight);
				graph.push_back(new_connection);
			}
		}
		else{
			while(!feof(graph_file)){
				connection new_connection;
				fscanf(graph_file, "%d %d", &new_connection.A, &new_connection.B);
				graph.push_back(new_connection);
			}
		}
		fclose(graph_file);
	}
	else{
		cout << "ERROR: Couldn't open the file to load it. Graph is not loaded!" << endl;
	}
	qckSort(graph, 0, graph.size() - 1);
}

void GraphCreator::print_graph_as_matrix(){
	for(int i = 0; i < number_of_nodes; ++i){
		cout << this->operator()(i, 0);
		for(int j = 1; j < number_of_nodes; ++j){
			cout << "\t" << this->operator()(i, j);
		}
		cout << endl;
	}
	cout << endl;
}

int GraphCreator::operator()(const int &i, const int &j){
	if(node_indices[i] == -1) return 0;
	if(i == number_of_nodes -1){
		for(int k = node_indices[i]; k < graph.size(); ++k){
			if( graph[k].B == j ) return weighted ? graph[k].weight : 1;
		}
		return 0;
	}
	int end = i + 1;
	while(node_indices[end] == -1){
		++end;
	}
	for(int k = node_indices[i]; k < node_indices[end]; ++k){
		if( graph[k].B == j ) return weighted ? graph[k].weight : 1;
	}
	return 0;
}

GraphCreator::~GraphCreator(){
	if(node_indices != NULL) delete[] node_indices;
}