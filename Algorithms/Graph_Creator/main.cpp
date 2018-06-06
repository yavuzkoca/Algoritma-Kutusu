#include "GraphCreator.h"

#include <iostream>

using namespace std;

int main(){
	GraphCreator graph(4, 0.5, false, true, 10);
	graph.random_initialize();
	graph.print_graph();
	graph.create_node_indices();
	graph.print_graph_as_matrix();
	graph.add_connection(1, 2, 20);
	graph.print_graph();
	graph.print_node_indices();
	graph.print_graph_as_matrix();
	graph.remove_connection_pseudo(1,2);
	graph.print_graph();
	graph.print_node_indices();
	graph.print_graph_as_matrix();
}