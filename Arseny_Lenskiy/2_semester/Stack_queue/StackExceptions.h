#ifndef STACKEXCEPTIONS_H
#define STACKEXCEPTIONS_H

#include <exception>
#include "MyExtensions.h"

class StackException : public std::exception {
public:
    StackException(ExceptionType type);

    const char *what() const noexcept override { return reason; }

private:
    const char *reason;
};

StackException::StackException(ExceptionType type) {
    switch (type) {
        case OVERFLOW:
            reason = "Stack Overflow";
        case UNDERFLOW:
            reason = "Stack Underflow";
        case WRONGSIZE:
            reason = "Wrong Stack Size";
    }
}
#endif
