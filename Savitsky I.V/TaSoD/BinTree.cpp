#include <iostream>
using namespace std;
class Node {
public:
	int data;
	Node* left;
	Node* right;
	Node(int value) { left = nullptr; right = nullptr; data = value; }
};

class BinaryTree {
private:
	Node* root;
public:
	BinaryTree(int value);
	~BinaryTree();
	void Destroy(Node* node);
	void add(int data);
    void del(int data);
	bool search(Node*& curr, int data, Node*& parent);
    Node* getMin(Node* curr);
    void print_tree(Node* curr);
    void print();

};

BinaryTree::BinaryTree(int value) {
	root = new Node(value);
}

BinaryTree::~BinaryTree() {
	Destroy(root);
}

void BinaryTree::Destroy(Node* node)
{
	if (node)
	{
		Destroy(node->left);
		Destroy(node->right);
		delete node;
	}
}

void BinaryTree::add(int data) {
	Node* curr = root;
	while (curr && curr->data != data) {

		if (curr->data > data && curr->left == nullptr) { curr->left=new Node(data); return; }
		if (curr->data < data && curr->right == nullptr) { curr->right = new Node(data); return; }

		if (curr->data > data) curr = curr->left;
		else curr = curr->right;
	}
}



bool BinaryTree::search(Node*& curr, int data, Node*& parent) {
	
	while (curr && curr->data != data) {
        parent = curr;
		if (curr->data > data) curr = curr->left;
		else curr = curr->right;
	}
	return curr != NULL;
}

Node* BinaryTree::getMin(Node* curr)
{
    while (curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

void BinaryTree::del(int data)
{
    Node* parent = nullptr;
    Node* curr = root;
    search(curr, data, parent);
    if (curr == nullptr) {
        return;
    }
    if (curr->left == nullptr && curr->right == nullptr)
    {
        if (curr != root)
        {
            if (parent->left == curr) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
        }
        else {
            root = nullptr;
        }
        free(curr);
    }
    else if (curr->left && curr->right)
    {
        Node* successor = getMin(curr->right);
        int val = successor->data;
        del(successor->data);
        curr->data = val;
    }
    else {
        Node* child = (curr->left) ? curr->left : curr->right;
        if (curr != root)
        {
            if (curr == parent->left) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }
        }
        else {
            root = child;
        }
        free(curr);
    }
}

void BinaryTree::print()
{
    print_tree(root);
    cout << endl;
}

void BinaryTree::print_tree(Node* curr)
{
    if (curr)
    {
        print_tree(curr->left);
        cout << curr->data << " ";
        print_tree(curr->right);
    }
}

void main() {
    BinaryTree A=BinaryTree(6);
    A.add(8);
    A.add(10);
    A.add(1);
    A.add(3);
    A.add(4);
    A.add(13);
    A.del(10);
    A.del(6);
    A.print();
}

