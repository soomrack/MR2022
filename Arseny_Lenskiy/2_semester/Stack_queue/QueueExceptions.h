#ifndef QUEUEEXCEPTIONS_H
#define QUEUEEXCEPTIONS_H

#include <exception>
#include "MyExtensions.h"

class QueueException : public std::exception {
public:
    QueueException(ExceptionType type);

    const char *what() const noexcept override { return reason; }

private:
    const char *reason;
};

QueueException::QueueException(ExceptionType type) {
    switch (type) {
        case OVERFLOW:
            reason = "Queue Overflow";
        case UNDERFLOW:
            reason = "Queue Underflow";
        case WRONGSIZE:
            reason = "Wrong Queue Size";
    }
}

#endif
