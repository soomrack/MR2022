#include <iostream>
#include "dinamic_array.cpp"
#include "linked_list.h"



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
	List.push_tail('G');
	List.push_tail('H');
	List.push_tail('I');
	List.push_tail('J');
	List.push_tail('K');

	List.push_head('0');

	List[5]->push_next('5');
	List[7]->pop_next();

	List.pop_back();
	List.pop_front();

	List.push_tail('J');

	std::cout << "\nSize = " << List.size() << std::endl;
	for(int ind = 0; ind < List.size();ind++){
		std::cout << List[ind]->data;
	}
	std::cout << std::endl;

	std::cout << "\nHead = " << List.get_head()->data << std::endl;
	std::cout << "\nTail = " << List.get_tail()->data << std::endl;
}

int main() {

	check_DinArr();

	check_LinkedList();

	return 0;

}
