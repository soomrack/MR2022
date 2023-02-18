//
// Created by user on 18.02.23.
//

#ifndef HELLO_WORLD_STACK_H
#define HELLO_WORLD_STACK_H


#include <cstdint>
#include <iostream>


class Exception: std::exception {
private:
    std::string message;
public:
    explicit Exception(std::string _message);

    std::string getMessage() const;
};


Exception::Exception(std::string _message) {
    message = std::move(_message);
}


std::string Exception::getMessage() const {
    return message;
}


#endif //HELLO_WORLD_STACK_H
