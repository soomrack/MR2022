#include <iostream>
//#include "linked_list.h"
#include "dinamic_array.h"
#include "queue_data.h"
#include "binary_tree.h"
int main()
{
//  Vector<int> dinArray;
//  dinArray.append(3);
//  dinArray.append(1);
//  dinArray.append(2);
//  dinArray.append(8);
//
//  LinkedList<int> linkedList;
//  linkedList.push_tail(1);
//  linkedList.push_tail(2);
//  linkedList.push_tail(3);

//  QueueArray<int> queueArray(10);
//  for (int i = 0; i < 10; ++i)
//  {
//    queueArray.push(i);
//  }
//
//  for (int i = 0; i < 11; ++i)
//  {
//    queueArray.pop();
//  }

BSTree<int> bsTree;
bsTree.Insert(10);
bsTree.Insert(5);
bsTree.Insert(8);
bsTree.Insert(2);
bsTree.Insert(7);

bsTree.Erase(5);
bsTree.print();

//  std::cout << linkedList.pop_head();
//
//  for (int i = 0; i < 200; ++i)
//  {
//    dinArray.append(i);
//  }
  return 0;
}
