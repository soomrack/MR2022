#ifndef ATD_BINARY_TREE_H
#define ATD_BINARY_TREE_H

#include <iostream>

class TreeNode{
public:
	int data;
	TreeNode* child_left;
	TreeNode* child_right;
	TreeNode(int new_data);
};

class Binary_Tree{
private:
	TreeNode* get_tree_node(int find_data);
	TreeNode* get_parent_node(int find_data);
public:
	TreeNode* root;
	Binary_Tree(){root = nullptr;};
	void add(int new_data);
	bool find(int find_data);
	void del(int del_data);
};

void Binary_Tree::add(int new_data) {
	TreeNode** link = &root;
	while(*link != nullptr){
		link = new_data < (*link)->data ? &((*link)->child_left) : &((*link)->child_right);
	}
	*link = new TreeNode(new_data);
}

bool Binary_Tree::find(int find_data) {
	auto current_node = root;
	if(get_tree_node(find_data) != nullptr){
		return true;
	}
	return false;
}

TreeNode* get_right(TreeNode* start_node){
	auto current_node = start_node;
	while (current_node != nullptr) {
		if (current_node->child_right == nullptr) {
			break;
		}
		current_node = current_node->child_right;
	}
	return current_node;
}

TreeNode* get_left(TreeNode* start_node){
	auto current_node = start_node;
	while (current_node != nullptr) {
		if (current_node->child_left == nullptr) {
			break;
		}
		current_node = current_node->child_left;
	}
	return current_node;
}

void Binary_Tree::del(int del_data) {
	auto parent_node = get_parent_node(del_data);
	TreeNode* current_node;
	current_node = current_node
}

TreeNode *Binary_Tree::get_tree_node(int find_data) {
	TreeNode** link = &root;
	while(*link != nullptr){
		link = find_data < (*link)->data ? &((*link)->child_left) : &((*link)->child_right);
		if((*link)->data == find_data) return *link;
	}
	return nullptr;
}

TreeNode *Binary_Tree::get_parent_node(int find_data) {
	TreeNode** link = &root;
	TreeNode** parent_link = nullptr;
	while(*link != nullptr){
		parent_link = link;
		link = find_data < (*link)->data ? &((*link)->child_left) : &((*link)->child_right);
		if((*link)->data == find_data) return *parent_link;
	}
	return nullptr;
}


TreeNode::TreeNode(int new_data) {
	data = new_data;
	child_left = nullptr;
	child_right = nullptr;
}

void preorder_print(TreeNode *root)
{
	if (root == nullptr)   // Базовый случай
	{
		return;
	}
	std::cout << root->data << " ";
	preorder_print(root->child_left);   //рекурсивный вызов левого поддерева
	preorder_print(root->child_right);  //рекурсивный вызов правого поддерева
}
// Функция печатает значения бинарного дерева поиска в прямом порядке.
// Вместо печати первой инструкцией функции может быть любое действие
// с данным узлом

#endif //ATD_BINARY_TREE_H
