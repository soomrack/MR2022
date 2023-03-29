#include <iostream>
#include "stack.h"


int main()
{
  Stack<char> is_it_works;
  char str[] = "!skrow ti";
  char* pstr = str;

  while (*pstr)
  {
    is_it_works.push(*pstr);
    ++pstr;
  }

  Stack<char> oper;
  oper.push('l'); oper.push('o'); oper.push('l');
  oper = is_it_works;
  Stack<char> copy(oper);

  while (!copy.empty())
  {
    std::cout << copy.pop();
  }

  std::cout << std::endl;
}

