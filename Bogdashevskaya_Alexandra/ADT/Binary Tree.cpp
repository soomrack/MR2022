#include <iostream> 
#include <queue>

class Tree_Exception : public std::exception
{
public:
	Tree_Exception(const char* const& msg) : exception(msg)
	{}
};

Tree_Exception ALREADY_EXISTS("Node with this key already exists\n");
Tree_Exception DOES_NOT_EXISTS("Node does not exist\n");

typedef double T;
unsigned int GENKEY = 0;

class NodeTree {
protected: 
	T data;
	int key;
	NodeTree* left_child;
	NodeTree* right_child;

public:
	NodeTree(int key, NodeTree* left_child = nullptr, NodeTree* right_child = nullptr);
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

	void add(int new_key);

	void del_by_data(T del_data);
	void del_by_key(int del_key);

	T get_data(int key);
	int get_key(T data);

	void print_tree();
};

NodeTree::NodeTree(int key, NodeTree* left_child, NodeTree* right_child) {

	this->data = GENKEY;
	this->key = key;
	this->left_child = left_child;
	this->right_child = right_child;

	++GENKEY;
}

NodeTree::NodeTree(const NodeTree& node) {
	data = node.data;
	key = node.key;
	left_child = node.left_child;
	right_child = node.right_child;
}

NodeTree::~NodeTree() {
	data = NULL;
	left_child = nullptr;
	right_child = nullptr;
}


Tree::~Tree() {
	root = nullptr;
}

void Tree::add(int new_key) {
	NodeTree* new_node = new NodeTree(new_key);
	NodeTree** temp = &root;
	while(*temp != nullptr) {
		if ((* temp)->key == new_key) throw ALREADY_EXISTS;
		((*temp)->key > new_key) ? temp = &((*temp)->left_child) : temp = &((*temp)->right_child);
	} 
	*temp = new_node;
	}


T Tree::get_data(int key) {
	if (root == nullptr) throw DOES_NOT_EXISTS;
	NodeTree** temp = &root;
	while (temp != nullptr) {
		if ((*temp)->key == key) {
			return (*temp)->data;
		}
		if ((*temp)->key > key) {
			temp = &((*temp)->left_child);
		}
		else {
			temp = &((*temp)->right_child);
		}
	}
	throw DOES_NOT_EXISTS;
}

int Tree::get_key(T data) {
	if (root == nullptr) throw DOES_NOT_EXISTS;
	T result = NULL;
	NodeTree* temp = root;
	std::queue<NodeTree*> queue;
	queue.push(temp);

	while (!queue.empty()) {
		temp = queue.front();
		queue.pop();
		if (temp->data == data) {
			return temp->key;
		}
		if (temp->left_child != nullptr) queue.push(temp->left_child);
		if (temp->right_child != nullptr) queue.push(temp->right_child);
	}
	throw DOES_NOT_EXISTS;
}



void Tree::del_by_key(int del_key) {
	NodeTree** temp = &root;
	while (temp != nullptr) { 
		if ((*temp)->key == del_key) {
			if ((*temp)->left_child == nullptr && (*temp)->right_child == nullptr) {
				temp = nullptr;
				return;
			}
			// один ребенок - заменяем родителя на ребенка
			if ((*temp)->left_child != nullptr && (*temp)->right_child == nullptr) {
				*temp = (*temp)->left_child;
				return;
			}
			if ((*temp)->right_child != nullptr && (*temp)->left_child == nullptr) {
				*temp = (*temp)->right_child;
				return;
			}
			// 2 ребенка - заменяем на крайнего, заменяем значение и рекурсивно вызываем удаление
			NodeTree* change = (*temp)->left_child;
			while (change->right_child != nullptr) {
				change = change->right_child;
			}
			int change_key = change->key;
			T change_data = change->data;
			del_by_key(change_key);
			(*temp)->key = change_key;
			(*temp)->data = change_data;
			return;
		}
		if ((*temp)->key > del_key) {
			temp = &((*temp)->left_child);
		}
		else {
			temp = &((*temp)->right_child);
		}
	}
	throw DOES_NOT_EXISTS;
}

void Tree::del_by_data(T del_data) {
	del_by_key(get_key(del_data));
}



void Tree::print_tree() {
	std::cout << (root == nullptr ? NULL : root->key) << std::endl;
	std::cout << (root->left_child == nullptr ? NULL : root->left_child->key) << " " << (root->right_child == nullptr ? NULL : root->right_child->key) << std::endl;
	std::cout << (root->left_child->left_child == nullptr ? NULL : root->left_child->left_child->key) << " " << (root->left_child->right_child == nullptr ? NULL : root->left_child->right_child->key) << " " << (root->right_child->left_child == nullptr ? NULL : root->right_child->left_child->key) << " " << (root->right_child->right_child == nullptr ? NULL : root->right_child->right_child->key) << std::endl;
}


int main() {
	Tree A;
	A.add(5);
	A.add(3);
	A.add(7);
	A.add(2);
	A.add(1);
	try {
		A.del_by_key(2);
	}
	catch (const Tree_Exception& e) {
		std::cerr << e.what() << std::endl;
	}
	A.print_tree();

	return 0;
}