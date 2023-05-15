#ifndef ATD_GRAPH_DATA_H
#define ATD_GRAPH_DATA_H
#include "dinamic_array.h"

typedef char Type;
class GraphNode{
public:
	Type data;
	DinArray<Type> neighbours;
	explicit GraphNode(Type new_data){data = new_data; neighbours.clear();}
};

class Graph{
public:
	DinArray<GraphNode*> nodes;
	void add_node(Type new_data);
	void del_node(Type del_data);
	GraphNode* get_node(Type get_data);
	void add_link(Type data_from, Type data_to);
	void del_link(Type data_from, Type data_to);
	void print();
};

void Graph::add_node(Type new_data) {
	auto new_node = new GraphNode(new_data);
	nodes.append(new_node);
}

GraphNode* Graph::get_node(Type get_data) {
	for(int idx = 0; idx < nodes.size(); idx++){
		if(nodes[idx]->data == get_data){
			return nodes[idx];
		}
	}
	return nullptr;
}

void Graph::add_link(Type data_from, Type data_to) {
	auto node_from = get_node(data_from);
	auto node_to = get_node(data_to);

	if(node_from == nullptr){
		add_node(data_from);
		node_from = get_node(data_from);
	}

	if(node_to == nullptr){
		add_node(data_to);
	}

	node_from->neighbours.append(data_to);
}

void Graph::del_link(Type data_from, Type data_to) {
	auto node_from = get_node(data_from);
	auto node_to = get_node(data_to);

	if(node_from == nullptr){
		return;
	}

	if(node_to == nullptr){
		return;
	}

	node_from->neighbours.pop_at(node_from->neighbours.find(data_to));
}

void Graph::del_node(Type del_data) {
	auto del_node = get_node(del_data);
	for(int idx = 0; idx < nodes.size(); idx++){
		del_link(del_data, nodes[idx]->data);
		del_link(nodes[idx]->data, del_data);
	}
	nodes.pop_at(nodes.find(del_node));
	delete del_node;
}

void Graph::print() {
	for(int idx = 0; idx < nodes.size(); idx++){
		std::cout << "Node: " << nodes[idx]->data << std::endl;
		std::cout << "Links: ";
		for(int j = 0; j < nodes[idx]->neighbours.size(); j++){
			std::cout << nodes[idx]->neighbours[j];
			std::cout << ", ";
		}
		std::cout << std::endl;
	}
}


#endif //ATD_GRAPH_DATA_H
