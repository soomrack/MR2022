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
	TreeNode* get_node(int find_data);
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
	if(get_node(find_data) != nullptr){
		return true;
	}
	return false;
}

void Binary_Tree::del(int del_data) {
	auto parent_node = get_parent_node(del_data);
	auto current_node_link = del_data < parent_node->data ? &(parent_node->child_left) : &(parent_node->child_right);
	auto del_node = *current_node_link;

	if((*current_node_link)->child_right == nullptr){
		*current_node_link = (*current_node_link)->child_left;
		delete del_node;
		return;
	}
	if((*current_node_link)->child_left == nullptr) {
		*current_node_link = (*current_node_link)->child_right;
		delete del_node;
		return;
	}
	auto del_left_link = &((*current_node_link)->child_left);
	auto del_right_link = &((*current_node_link)->child_right);
	auto del_link = current_node_link;

	// Поиск самого левого справа
	auto most_left_link = del_right_link;
	auto next_node = (*most_left_link)->child_left;
	while (next_node != nullptr) {
		most_left_link = &((*most_left_link)->child_left);
		next_node = next_node->child_left;
	}

	auto most_left = *most_left_link;
	(*del_link) = most_left;
	most_left->child_left = (*del_left_link);
	auto mem_link = most_left->child_right;
	most_left->child_right = (*del_right_link);
	(*most_left_link) = mem_link;

	delete del_node;
}

TreeNode *Binary_Tree::get_node(int find_data) {
	TreeNode** link = &root;
	while(*link != nullptr){
		if((*link)->data == find_data) return *link;
		link = find_data < (*link)->data ? &((*link)->child_left) : &((*link)->child_right);
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
