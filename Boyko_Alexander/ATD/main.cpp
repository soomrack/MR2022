#include <iostream>
#include "dinamic_array.cpp"
#include "linked_list.h"

DinArray<char> A;
DinArray<char> B;

LinkList<char> List;

int main() {
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
/*
	List.push_tail('A');
	std::cout<< List[0].get_data();
	return 0;
*/
}
