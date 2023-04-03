#include <iostream> 
#include <queue>

class Tree_Exception : public std::exception
{
public:
	Tree_Exception(const char* const& msg) : exception(msg)
	{}
};

Tree_Exception ALREADY_EXISTS("Node with this value already exists\n");
Tree_Exception DOES_NOT_EXISTS("Node does not exist\n");

typedef double T;
unsigned int GENKEY = 0;

class NodeTree {
protected: 
	unsigned int key;
	T value;
	NodeTree* left_child;
	NodeTree* right_child;

public:
	NodeTree(T value, NodeTree* left_child = nullptr, NodeTree* right_child = nullptr);
	NodeTree(const NodeTree& node);
	~NodeTree();

	friend class Tree;
};


class Tree {
protected:
	NodeTree* root = nullptr;

public:
	Tree() = default;
	~Tree();

	void add(T new_value);

	void del_by_key(unsigned int del_key);
	void del_by_value(T del_value);

	unsigned int get_key(T value);
	T get_value(unsigned int key);

	void print_tree();
};

NodeTree::NodeTree(T value, NodeTree* left_child, NodeTree* right_child) {

	this->key = GENKEY;
	this->value = value;
	this->left_child = left_child;
	this->right_child = right_child;

	++GENKEY;
}

NodeTree::NodeTree(const NodeTree& node) {
	key = node.key;
	value = node.value;
	left_child = node.left_child;
	right_child = node.right_child;
}

NodeTree::~NodeTree() {
	key = NULL;
	left_child = nullptr;
	right_child = nullptr;
}


Tree::~Tree() {
	root = nullptr;
}

void Tree::add(T new_value) {
	NodeTree* new_node = new NodeTree(new_value);
	NodeTree** temp = &root;
	while(*temp != nullptr) {
		if ((* temp)->value == new_value) throw ALREADY_EXISTS;
		if ((*temp)->value > new_value) temp = &((*temp)->left_child);
		else temp = &((*temp)->right_child);
	} 
	*temp = new_node;
	}


unsigned int Tree::get_key(T value) {
	if (root == nullptr) throw DOES_NOT_EXISTS;
	NodeTree* temp = root;
	while (temp->value != value) {
		if (temp->value > value) {
			if (temp->left_child == nullptr) throw DOES_NOT_EXISTS;
			temp = temp->left_child;
		}
		else {
			if (temp->right_child == nullptr) throw DOES_NOT_EXISTS;
			temp = temp->right_child;
		}
	}
	return temp->key;
}

T Tree::get_value(unsigned int key) {
	if (root == nullptr) throw DOES_NOT_EXISTS;
	T result = NULL;
	NodeTree* temp = root;
	std::queue<NodeTree*> queue;
	queue.push(temp);

	while (!queue.empty()) {
		temp = queue.front();
		queue.pop();
		if (temp->key == key) {
			return temp->value;
		}
		if (temp->left_child != nullptr) queue.push(temp->left_child);
		if (temp->right_child != nullptr) queue.push(temp->right_child);
	}
	throw DOES_NOT_EXISTS;
}



void Tree::del_by_value(T del_value) {
	NodeTree** parent = nullptr;
	NodeTree** temp = &root;
	bool is_right_child = NULL;
	while ((*temp)->value != del_value) {
		if ((*temp)->value > del_value) {
			if ((*temp)->left_child == nullptr) throw DOES_NOT_EXISTS;
			parent = temp;
			temp = &((*temp)->left_child);
			is_right_child = 0;
		}
		if ((*temp)->value < del_value) {
			if ((*temp)->right_child == nullptr) throw DOES_NOT_EXISTS;
			parent = temp;
			temp = &((*temp)->right_child);
			is_right_child = 1;
		}
	}
	if ((*temp)->left_child == nullptr && (*temp)->right_child == nullptr) {
		if ((*temp) == root) {
			root = nullptr;
			return;
		}
		is_right_child ? (*parent)->right_child = nullptr : (*parent)->left_child = nullptr;
		return;
	}
	// один ребенок - заменяем родителя на ребенка
	if ((*temp)->left_child != nullptr && (*temp)->right_child == nullptr) {
		if ((*temp) == root) {
			root = (*temp)->left_child;
			return;
		}
		is_right_child ? (*parent)->right_child = (*temp)->left_child : (*parent)->left_child = (*temp)->left_child;
		return;
	}
	if ((*temp)->right_child != nullptr && (*temp)->left_child == nullptr) {
		if ((*temp) == root) {
			root = (*temp)->right_child;
			return;
		}
		is_right_child ? (*parent)->right_child = (*temp)->right_child : (*parent)->left_child = (*temp)->right_child;
		return;
	}
	// 2 ребенка - заменяем на крайнего, заменяем значение и рекурсивно вызываем удаление
	NodeTree* change = (*temp)->left_child;
	while (change->right_child != nullptr) {
		change = change->right_child;
	}
	T change_value = change->value;
	unsigned int change_key = change->key;
	del_by_value(change_value);
	(*temp)->value = change_value;
	(*temp)->key = change_key;
	return;
}

void Tree::del_by_key(unsigned int del_key) {
	del_by_value(get_value(del_key));
}



void Tree::print_tree() {
	std::cout << root->value << std::endl;
	std::cout << root->left_child->value << " " << root->right_child->value << std::endl;
	std::cout << root->left_child->left_child->value << " " << root->left_child->right_child->value << " " << root->right_child->left_child->value << " " << root->right_child->right_child->value << std::endl;
}


//int main() {
//	Tree A;
//	A.add(5);
//	A.add(3);
//	A.add(7);
//	A.add(1);
//	try {
//		A.del_by_key(0);
//	}
//	catch (const Tree_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//	A.print_tree();
//
//	return 0;
//}