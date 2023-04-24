#ifndef ATD_GRAPH_DATA_H
#define ATD_GRAPH_DATA_H
#include "dinamic_array.h"

typedef char Type;
class GraphNode{
public:
	Type data;
	DinArray<GraphNode*> neighbours;
	explicit GraphNode(Type new_data){data = new_data;}
};


class Graph{
public:
	DinArray<GraphNode*> nodes;
	void add_node(Type new_data, DinArray<GraphNode*> link_to, DinArray<GraphNode*> link_from);
};

void Graph::add_node(Type new_data, DinArray<GraphNode*> link_to, DinArray<GraphNode*> link_from) {
	auto new_node = new GraphNode(new_data);
	int to_size = link_to.size();
	int from_size = link_from.size();
	if(to_size){
		new_node->neighbours = link_to;
	}
	if(from_size){
		for(int idx = 0; idx < to_size; idx++){
			link_from[idx]->neighbours.append(new_node);
		}
	}
}


#endif //ATD_GRAPH_DATA_H
