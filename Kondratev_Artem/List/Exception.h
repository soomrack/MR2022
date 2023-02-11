//
// Created by user on 08.02.23.
//

#ifndef HELLO_WORLD_EXCEPTION_H
#define HELLO_WORLD_EXCEPTION_H


#include <iostream>


class Exception: public std::exception {
private:
    std::string message;
public:
    explicit Exception(std::string input_message);
    Exception(const Exception &other) = default;
    Exception(Exception &&other) = default;
    ~Exception() override = default;

    std::string getMessage() const;
};


#endif //HELLO_WORLD_EXCEPTION_H
