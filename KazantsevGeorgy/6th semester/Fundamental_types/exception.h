//
// Created by delta on 18.02.2023.
//

#ifndef CLIONPROJECTS_EXCEPTION_H
#define CLIONPROJECTS_EXCEPTION_H

#endif //CLIONPROJECTS_EXCEPTION_H
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <exception>
using namespace std;

class Exception : public domain_error //в clion написана библиотека, где вместо exception используется domain_error
{
public:
    Exception(const char* const msg): domain_error(msg) {}
};

Exception DIVISIONBYZERO("DIV BY ZERO\n");

// stack exception
Exception STACKOVERFLOW("STACK IS FULL\n");

// Binary tree exception
Exception BINARYTREEFULL("BINARYTREEFULL\n");

