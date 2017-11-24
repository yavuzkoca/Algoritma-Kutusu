#include "GraphCreator.h"

#include <iostream>

using namespace std;

int main(){
	GraphCreator graph(10, 0.2, false, true, 20);
	graph.random_initialize();
	graph.print_graph();
	graph.create_node_indices();
	graph.print_node_indices();
	for(int i = 0; i < 10; ++i){
		cout << graph(i,0);
		for(int j = 1; j < 10; ++j){
			cout << "\t" << graph(i, j);
		}
		cout << endl;
	}
}