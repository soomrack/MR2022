#include <iostream>
#include <windows.h>
#include <exception>
#include <cstdlib>


class AtypesException : public std::domain_error //clion
{
public:
    AtypesException(const char* const msg): domain_error(msg) {}
};


