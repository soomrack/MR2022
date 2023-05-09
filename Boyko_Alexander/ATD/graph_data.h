#ifndef ATD_GRAPH_DATA_H
#define ATD_GRAPH_DATA_H
#include "linked_list.h"

typedef char Type;
class GraphNode{
public:
	Type data;
	LinkedList<GraphNode*> neighbours;
	explicit GraphNode(Type new_data){data = new_data;}
};


class Graph{
public:
	LinkedList<GraphNode*> nodes;
	void add_node(Type new_data, LinkedList<GraphNode*> link_to, LinkedList<GraphNode*> link_from);
};

void Graph::add_node(Type new_data, LinkedList<GraphNode*> link_to, LinkedList<GraphNode*> link_from) {
	auto new_node = new GraphNode(new_data);
	int to_size = link_to.size();
	int from_size = link_from.size();
	if(to_size){
		new_node->neighbours = link_to;
	}
	if(from_size){
		auto current_node = link_from.get_head();
		while(current_node != nullptr){
			current_node->data->neighbours.push_tail(new_node);
			current_node = current_node->next;
		}
	}
}


#endif //ATD_GRAPH_DATA_H
