#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <exception>

using namespace std;

class ExceptError: public domain_error //в clion написана библиотека, где вместо exception используется domain_error
{
public:
    explicit ExceptError(const char* const msg): domain_error(msg) {}
};



