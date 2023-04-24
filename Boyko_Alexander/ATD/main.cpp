#include <iostream>
#include "dinamic_array.cpp"
#include "linked_list.h"
#include "stack_data.h"
#include "queue_data.h"
#include "binary_tree.h"
#include "graph_data.h"

void check_DinArr(){
	DinArray<char> A;
	DinArray<char> B;

	A.append('A');
	A.append('C');
	A.append('D');
	A.append_at('B',1);
	A.append('E');
	A.append('F');
	A.append('G');
	A.append('H');
	A.append('I');
	A.append('G');
	A.append('K');
	A.append('L');
	std::cout << "\nSize = " << A.size() << std::endl;
	for(int ind = 0; ind < A.size();ind++){
		std::cout << A[ind];
	}
	std::cout << std::endl;

	B.append('1');
	B.append('2');
	B.append('3');
	std::cout << "\nSize = " << B.size() << std::endl;
	for(int ind = 0; ind < B.size();ind++){
		std::cout << B[ind];
	}
	std::cout << std::endl;

	A.append_at(B,2);
	std::cout << "\nSize = " << A.size() << std::endl;
	for(int ind = 0; ind < A.size();ind++){
		std::cout << A[ind];
	}
	std::cout << std::endl;
}

void check_LinkedList(){
	LinkedList<char> List;


	List.push_tail('A');
	List.push_tail('B');
	List.push_tail('C');
	List.push_tail('D');
	List.push_tail('E');
	List.push_tail('F');

	List.push_head('0');

	List.get(2)->push_next('2');
	List.get(3)->pop_next();

	List.get(10)->pop_next();

	List.pop_head();
	List.pop_tail();

	List.push_tail('J');

	std::cout << "\nSize = " << List.size() << std::endl;
	for(int ind = 0; ind < List.size();ind++){
		std::cout << List.get(ind)->data;
	}
	std::cout << std::endl;

	std::cout << "\nHead = ";
	std::cout << List.get_head()->data << std::endl;
	std::cout << "\nTail = " << List.get_tail()->data << std::endl;
}

void check_Stack(){
	Stack MyStack;
	MyStack.push('A');
	MyStack.push('B');
	MyStack.push('C');
	MyStack.push('D');
	MyStack.pop();

	std::cout << "\nSize = " << MyStack.size() << std::endl;
	for(int ind = 0; ind < MyStack.size();ind++){
		std::cout << MyStack.get(ind)->data;
	}
	std::cout << std::endl;
}


void check_Queue(){
	Queue MyQueue;
	MyQueue.push('A');
	MyQueue.push('B');
	MyQueue.push('C');
	MyQueue.push('D');
	MyQueue.pop();

	std::cout << "\nSize = " << MyQueue.size() << std::endl;
	for(int ind = 0; ind < MyQueue.size();ind++){
		std::cout << MyQueue.get(ind)->data;
	}
	std::cout << std::endl;
}


void check_Tree(){
	Binary_Tree my_tree;
	my_tree.add(10);
	my_tree.add(3);
	my_tree.add(1);
	my_tree.add(8);
	my_tree.add(7);
	my_tree.add(12);
	my_tree.add(15);
	my_tree.add(16);
	my_tree.add(6);

	preorder_print(my_tree.root);

	std::cout << std::endl;

	my_tree.del(8);

	preorder_print(my_tree.root);

	std::cout << my_tree.find(6);
}


void check_graph(){
	Graph my_graph;
	DinArray<GraphNode*> empt_arr;
	my_graph.add_node('A', empt_arr,empt_arr);
}


int main() {

	check_DinArr();

	check_LinkedList();

	check_Stack();

	check_Queue();

	check_Tree();

	check_graph();

	return 0;

}
