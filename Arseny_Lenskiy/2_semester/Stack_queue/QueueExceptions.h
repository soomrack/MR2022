#ifndef QUEUEEXCEPTIONS_H
#define QUEUEEXCEPTIONS_H

#include <exception>

class QueueOverflow : public std::exception {
public:
    QueueOverflow() : reason_("Queue Overflow") {}

    const char *what() const noexcept override { return reason_; }

private:
    const char *reason_;
};

class QueueUnderflow : public std::exception {
public:
    QueueUnderflow() : reason_("Queue Underflow") {}

    const char *what() const noexcept override { return reason_; }

private:
    const char *reason_;
};

class WrongQueueSize : public std::exception {
public:
    WrongQueueSize() : reason_("Wrong Queue Size") {}

    const char *what() const noexcept override { return reason_; }

private:
    const char *reason_;
};

#endif
