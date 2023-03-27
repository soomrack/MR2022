#include <iostream>  // попробовать через typedef

class Tree_Exception : public std::exception
{
public:
	Tree_Exception(const char* const& msg) : exception(msg)
	{}
};

Tree_Exception ALREADYEXISTS("Node with this value already exists\n");
Tree_Exception DOESNOTEXISTS("Node with this value does not exist\n");

typedef double T;

class Node {
protected:
	T value = NULL;
	Node* parent = nullptr;
	bool i_am_right_child;
	Node* left_child = nullptr;
	Node* right_child = nullptr;

public:
	Node(T value, bool right = NULL, Node* parent = nullptr, Node* left_child = nullptr, Node* right_child = nullptr);
	Node(const Node& node);
	~Node();

	friend class Tree;
};


class Tree {
protected:
	Node* root = nullptr;
	//unsigned int max_depth;  Нужно?

public:
	Tree() = default;
	~Tree();

	void add_node(T new_value);
	void delete_node(T del_value);

	void print_tree();
};

Node::Node(T value, bool right, Node* parent, Node* left_child, Node* right_child) {
	this->value = value;
	this->i_am_right_child = right;
	this->parent = parent;
	this->left_child = left_child;
	this->right_child = right_child;
}

Node::Node(const Node& node) {
	value = node.value;
	parent = node.parent;
	left_child = node.left_child;
	right_child = node.right_child;
}

Node::~Node() {
	parent = nullptr;
	left_child = nullptr;
	right_child = nullptr;
}


Tree::~Tree() {
	root = nullptr;
}

void Tree::add_node(T new_value) {
	Node* new_node = new Node(new_value);
	if (root == nullptr) {
		root = new_node;
		return;
	}
	Node* temp = root;
	while (true) {
		if (temp->value == new_value) throw ALREADYEXISTS;
		if (temp->value > new_value) {
			if (temp->left_child == nullptr) {
				new_node->parent = temp;
				new_node->i_am_right_child = 0;
				temp->left_child = new_node;
				return;
			}
			temp = temp->left_child;
			continue;
		}
		if (temp->value < new_value) {
			if (temp->right_child == nullptr) {
				new_node->parent = temp;
				new_node->i_am_right_child = 1;
				temp->right_child = new_node;
				return;
			}
			temp = temp->right_child;
			continue;
		}
	}
}

// нет детей - удаляем
// один ребенок - заменяем родителя на ребенка
// 2 ребенка - заменяем на крайнего, заменяем значение и рекурсивно вызываем удаление

// добавить проверку на рут

// Добавить проверку на отсутсиве значения

void Tree::delete_node(T del_value) {
	Node* temp = root;
	while (true) {
		if (temp->value == del_value) {
			// нет детей - просто удаляем
			if (temp->left_child == nullptr && temp->right_child == nullptr) {
				if (temp == root) {
					root = nullptr;
					return;
				}
				temp->i_am_right_child ? temp->parent->right_child = nullptr : temp->parent->left_child = nullptr;
				return;
			}
			// один ребенок - заменяем родителя на ребенка
			if (temp->left_child != nullptr && temp->right_child == nullptr) {
				if (temp == root) {
					root = temp->left_child;
					return;
				}
				Node* change = temp->left_child;
				temp->i_am_right_child ? temp->parent->right_child = change : temp->parent->left_child = change;
				change->parent = temp->parent;
				change->i_am_right_child = temp->i_am_right_child;
				return;
			}
			if (temp->right_child != nullptr && temp->left_child == nullptr) {
				if (temp == root) {
					root = temp->right_child;
					return;
				}
				Node* change = temp->right_child;
				temp->i_am_right_child ? temp->parent->right_child = change : temp->parent->left_child = change;
				change->parent = temp->parent;
				change->i_am_right_child = temp->i_am_right_child;
				return;
			}
			// 2 ребенка - заменяем на крайнего, заменяем значение и рекурсивно вызываем удаление
			Node* change = temp->left_child;
			while (change->right_child != nullptr) {
				change = change->right_child;
			}
			T change_value = change->value;
			delete_node(change_value);
			temp->value = change_value;
			return;
		}
		if (temp->value > del_value) {
			if (temp->left_child == nullptr) throw DOESNOTEXISTS;
			temp = temp->left_child;
		}
		if (temp->value < del_value) {
			if (temp->right_child == nullptr) throw DOESNOTEXISTS;
			temp = temp->right_child;
		}
	}
}


void Tree::print_tree() {
	std::cout << root->value << std::endl;
	std::cout << root->left_child->value << " " << root->right_child->value << std::endl;
	std::cout << root->left_child->left_child->value << " " << root->left_child->right_child->value << " " << root->right_child->left_child->value << " " << root->right_child->right_child->value << std::endl;
}


int main() {
	Tree A;
	A.add_node(5);
	A.add_node(3);
	A.add_node(7);
	A.add_node(1);
	A.add_node(4);
	A.add_node(6);
	try {
		A.add_node(7);
	}
	catch (const Tree_Exception& e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		A.delete_node(5);
	}
	catch (const Tree_Exception& e) {
		std::cerr << e.what() << std::endl;
	}

	A.print_tree();


	return 0;
}