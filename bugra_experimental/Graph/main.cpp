#include "GraphCreator.h"

int main(){
	GraphCreator graph(10, 0.1, true, true, 10);
	graph.random_initialize();
	graph.print_graph();
}