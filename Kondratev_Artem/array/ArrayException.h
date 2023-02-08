//
// Created by user on 08.02.23.
//

#ifndef HELLO_WORLD_ARRAYEXCEPTION_H
#define HELLO_WORLD_ARRAYEXCEPTION_H


#include <iostream>


class ArrayException: public std::exception {
private:
    std::string message;
public:
    explicit ArrayException(std::string input_message);
    ArrayException(const ArrayException &other) = default;
    ArrayException(ArrayException &&other) = default;
    ~ArrayException() override = default;

    std::string getMessage() const;
};


#endif //HELLO_WORLD_ARRAYEXCEPTION_H
