//AVL Tree


#include <iostream> 
#include <queue>
#include <stack>
#include <ctime>


class Tree_Exception : public std::exception
{
public:
	Tree_Exception(const char* const& msg) : exception(msg)
	{}
};

Tree_Exception ALREADY_EXISTS("Node with this key already exists");
Tree_Exception DOES_NOT_EXISTS("Node does not exist");

typedef double T;
T GEN = 0;

class NodeTree {
protected:
	T data;
	int key;
	NodeTree* left_child;
	NodeTree* right_child;
	int height;
	int bf; // balance factor = diiference between hights of left and right subtrees


public:
	NodeTree(int key, NodeTree* left_child = nullptr, NodeTree* right_child = nullptr, int height = 0, int bf = 0);
	NodeTree(const NodeTree& node);
	~NodeTree();
	void update(); // updates balance factor and height

	friend class Tree;
};

typedef std::stack<NodeTree**> node_stack;


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

	void balance(node_stack stack);
	void l_rotate(NodeTree** node);
	void r_rotate(NodeTree** node);
	void lr_rotate(NodeTree** node);
	void rl_rotate(NodeTree** node);
};

NodeTree::NodeTree(int key, NodeTree* left_child, NodeTree* right_child, int height, int bf) {

	this->data = GEN;
	this->key = key;
	this->left_child = left_child;
	this->right_child = right_child;
	this->bf = bf;
	this->height = height;

	++GEN;
}

NodeTree::NodeTree(const NodeTree& node) {
	data = node.data;
	key = node.key;
	bf = node.bf;
	height = node.height;
	left_child = node.left_child;
	right_child = node.right_child;
}

NodeTree::~NodeTree() {
	data = NULL;
	left_child = nullptr;
	right_child = nullptr;
}

void NodeTree::update() {
	int lheight = 1 + (left_child == nullptr ? -1 : left_child->height);
	int rheight = 1 + (right_child == nullptr ? -1 : right_child->height);
	bf = lheight - rheight;
	height = lheight > rheight ? lheight : rheight;
}


Tree::~Tree() {
	root = nullptr;
}

void Tree::add(int new_key) {
	NodeTree* new_node = new NodeTree(new_key);
	NodeTree** temp = &root;
	node_stack stack;
	while (*temp != nullptr) {
		if ((*temp)->key == new_key) throw ALREADY_EXISTS;
		stack.push(temp);
		((*temp)->key > new_key) ? temp = &((*temp)->left_child) : temp = &((*temp)->right_child);
	}
	*temp = new_node;
	balance(stack);
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
	node_stack stack;
	while (*temp != nullptr) {
		if ((*temp)->key == del_key) {

			if ((*temp)->left_child == nullptr && (*temp)->right_child == nullptr) {
				*temp = nullptr;
				balance(stack);
				return;
			}
			// 1 child
			if ((*temp)->left_child != nullptr && (*temp)->right_child == nullptr) {
				*temp = (*temp)->left_child;
				balance(stack);
				return;
			}
			if ((*temp)->right_child != nullptr && (*temp)->left_child == nullptr) {
				*temp = (*temp)->right_child;
				balance(stack);
				return;
			}
			// 2 children
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

		stack.push(temp);

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

void Tree::balance(node_stack stack) {
	NodeTree** temp;
	while (!stack.empty()) {
		temp = stack.top();

		//std::cout << (*temp)->key << " " << (*temp)->height << " " << (*temp)->bf << std::endl;

		(*temp)->update();

		//std::cout << (*temp)->key << " " << (*temp)->height << " " << (*temp)->bf << std::endl;

		if ((*temp)->bf < -1) {
			(*temp)->right_child->bf <= 0 ? l_rotate(temp) : rl_rotate(temp);
			stack.~stack();
			return;
		}
		else if ((*temp)->bf > 1) {
			(*temp)->left_child->bf >= 0 ? r_rotate(temp) : lr_rotate(temp);
			stack.~stack();
			return;
		}
		stack.pop();
	}
}


void Tree::l_rotate(NodeTree** node) {
	NodeTree* child = (*node)->right_child;

	(*node)->right_child = child->left_child;
	child->left_child = *node;
	*node = child;
	(*node)->left_child->update();
	(*node)->update();
}

void Tree::r_rotate(NodeTree** node) {
	NodeTree* child = (*node)->left_child;

	(*node)->left_child = child->right_child;
	child->right_child = *node;
	*node = child;
	(*node)->right_child->update();
	(*node)->update();
}

void Tree::lr_rotate(NodeTree** node) {
	l_rotate(&((*node)->left_child));
	r_rotate(node);
}

void Tree::rl_rotate(NodeTree** node){
	r_rotate(&((*node)->right_child));
	l_rotate(node);
}



//void Tree::print_tree() {
//	std::cout << "The tree: \n";
//	std::cout << (root == nullptr ? NULL : root->key) << std::endl;
//	std::cout << (root->left_child == nullptr ? NULL : root->left_child->key) << " " << (root->right_child == nullptr ? NULL : root->right_child->key) << std::endl;
//	std::cout << (root->left_child->left_child == nullptr ? NULL : root->left_child->left_child->key) << " " << (root->left_child->right_child == nullptr ? NULL : root->left_child->right_child->key) << " " << (root->right_child->left_child == nullptr ? NULL : root->right_child->left_child->key) << " " << (root->right_child->right_child == nullptr ? NULL : root->right_child->right_child->key) << std::endl;
//}


int main() {
	clock_t big_start = clock();
	const int iter = 10000;
	Tree A;
	int values[iter];

	for (int i = 0; i < iter; ++i) {
		int rand = std::rand();
		values[i] = rand;

		clock_t start = clock();
		try {
			A.add(rand);
		}
		catch (const Tree_Exception& e) {
			std::cerr << e.what() << std::endl;
		}
		clock_t end = clock();

		double seconds = (double)(end - start);
		std::cout << seconds << std::endl;


	}

	std::cout << "\nDelete:\n\n";

	for (int i = 0; i < iter; ++i) {
		int rand = std::rand() % iter;

		int value = values[rand];

		clock_t start = clock();
		try {
			A.del_by_key(value);
		}
		catch (const Tree_Exception& e) {
			std::cerr << e.what() << std::endl;
		}
		clock_t end = clock();

		double seconds = (double)(end - start);
		std::cout << seconds << std::endl;

	}
	clock_t big_end = clock();
	double seconds = (double)(big_end - big_start) / CLOCKS_PER_SEC;
	std::cout << seconds << std::endl;

	return 0;
}