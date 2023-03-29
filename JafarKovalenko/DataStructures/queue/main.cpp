#include <iostream>
#include "queue.h"


int main()
{
  Queue<char> is_it_works;
  char str[] = "it works!";
  char* pstr = str;

  while (*pstr)
  {
    is_it_works.push(*pstr);
    ++pstr;
  }

  Queue<char> oper;
  oper.push('l'); oper.push('o'); oper.push('l');
  oper = is_it_works;
  Queue<char> copy(oper);

  while (!copy.empty())
  {
    std::cout << copy.pop();
  }

  std::cout << std::endl;
}

