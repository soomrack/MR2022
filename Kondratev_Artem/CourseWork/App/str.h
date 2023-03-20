//
// Created by user on 3/17/23.
//

#ifndef MANIPULATOR_STR_H
#define MANIPULATOR_STR_H


#include <iostream>
#include <utility>
#include <cstring>


class str {
private:
    std::string string;
    int curs;

public:
    str();

    void push(char symbol, int index);
    void pop(int index);
    void reset();
    uint64_t size();
    const char* get();
    void keyBackspace();
    void keyDelete();
    void setCurs(int CURS_X);
    int getCurs() const;
};


#endif //MANIPULATOR_STR_H
