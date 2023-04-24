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
	int del(int del_data);
};

void Binary_Tree::add(int new_data) {
	auto new_node = new TreeNode(new_data);
	if(root == nullptr){
		root = new_node;
		return;
	}
	auto current_node = root;
	while(current_node) {
		if(new_data > current_node->data) {
			if(current_node->child_right) {
				current_node = current_node->child_right;
			} else {
				current_node->child_right = new_node;
				return;
			}
		}
		else {
			if(current_node->child_left) {
				current_node = current_node->child_left;
			} else {
				current_node->child_left = new_node;
				return;
			}
		}
	}
	current_node = new_node;
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

int Binary_Tree::del(int del_data) {
	auto parent_node = get_parent_node(del_data);
	TreeNode *del_node = nullptr;
	if (del_data < parent_node->data) {
		del_node = parent_node->child_left;
	} else {
		del_node = parent_node->child_right;
	}
	TreeNode* current_node = nullptr;
	if (del_node->child_left) {
		current_node = del_node->child_left;
		current_node = get_right(current_node);
	}
	else{
		if(del_node->child_right){
			current_node = del_node->child_right;
			current_node = get_left(current_node);
		}
	}
	if (current_node->data < parent_node->data) {
		parent_node->child_left = current_node;
	} else {
		parent_node->child_right = current_node;
	}
	delete del_node;
	return del_data;
}

TreeNode *Binary_Tree::get_tree_node(int find_data) {
	auto current_node = root;
	while(current_node) {
		if(current_node->data == find_data){
			return current_node;
		}
		if(find_data > current_node->data) {
			current_node = current_node->child_right;
		}
		else {
			current_node = current_node->child_left;
		}
	}
	return nullptr;
}

TreeNode *Binary_Tree::get_parent_node(int find_data) {
	auto current_node = root;
	TreeNode* parent_node = nullptr;
	while(current_node) {
		if(current_node->data == find_data){
			return parent_node;
		}
		parent_node = current_node;
		if(find_data > current_node->data) {
			current_node = current_node->child_right;
		}
		else {
			current_node = current_node->child_left;
		}
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
