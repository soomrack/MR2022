// �������� ������� �������
#include <iostream> 
#include <list>



typedef double T;
unsigned int KEY = 0;

class NodeGraph {
protected:
	unsigned int key;
	T value;
	std::list<NodeGraph*> edges;
	

public:
	NodeGraph(T value);
	~NodeGraph();

	void print_node();

	friend class Graph;
};

class Graph {
protected:
	unsigned int size = 0;
	std::list<NodeGraph*> nodes;

public:
	Graph() = default;

	~Graph();

	void add_node(T new_value);
	void add_edge(NodeGraph* from, NodeGraph* to, bool two_sides = 1);
	void add_edge(unsigned int key_from, unsigned int key_to, bool two_sides = 1);
	void del_node(unsigned int key);


	NodeGraph* find_by_key(unsigned int key);

	void print_graph();
};


NodeGraph::NodeGraph(T value) {
	this->key = KEY;
	this->value = value;

	++KEY;
}

NodeGraph::~NodeGraph() {
	std::list<NodeGraph*>::iterator idx;
	for (NodeGraph* temp : edges) {
		idx = (temp->edges).begin();
		for (NodeGraph* check : temp->edges) {
			if (check->key == key) {
				temp->edges.erase(idx);
				break;
			}
			++idx;
		}
	}
	edges.clear();
	key = NULL;

}

void NodeGraph::print_node() {
	std::cout << "NodeGraph " << key << " with value " << value << " is linked to:\n";
	for (NodeGraph* temp : edges) {
		std::cout << temp->key << " ";
	}
	std::cout << "\n";
}

Graph::~Graph() {
	size = 0;
	nodes.clear();
}

void Graph::add_node(T value) { // ��������� �� �������
	for (NodeGraph* temp : nodes) {
		if (temp->value == value) return; // ������
	}
	NodeGraph* new_node = new NodeGraph(value);
	nodes.push_back(new_node);
}

void Graph::add_edge(NodeGraph* from, NodeGraph* to, bool two_sides) {
	from->edges.push_back(to);
	if (two_sides) to->edges.push_back(from);
}

void Graph::add_edge(unsigned int key_from, unsigned int key_to, bool two_sides) {
	NodeGraph* from = find_by_key(key_from);
	NodeGraph* to = find_by_key(key_to);
	add_edge(from, to, two_sides);
}

NodeGraph* Graph::find_by_key(unsigned int key) {
	for (NodeGraph* temp : nodes) {
		if (temp->key == key) return temp;
	}
	// �������� ������
}

void Graph::del_node(unsigned int key) {
	NodeGraph* del_node = find_by_key(key);
	std::list<NodeGraph*>::iterator node_idx, edge_idx, idx_to_del;
	node_idx = nodes.begin();;
	for (NodeGraph* temp : nodes) {
		if (temp == del_node) {
			idx_to_del = node_idx;
		}
		edge_idx = (temp->edges).begin();
		for (NodeGraph* check : temp->edges) {
			if (check->key == key) {
				temp->edges.erase(edge_idx);
				break;
			}
			++edge_idx;
		}
		++node_idx;
	}
	nodes.erase(idx_to_del);
}

void Graph::print_graph() {
	for (NodeGraph* temp : nodes) {
		temp->print_node();
	}
}


int main() {
	Graph A;
	A.add_node(10);
	A.add_node(5);
	A.add_node(33);
	A.add_node(98);

	A.add_edge(1, 2);
	A.add_edge(1, 0);
	A.add_edge(1, 3);

	A.del_node(0);

	A.print_graph();

	return 0;
}