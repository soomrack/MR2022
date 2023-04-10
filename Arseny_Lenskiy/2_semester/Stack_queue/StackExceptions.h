#ifndef STACKEXCEPTIONS_H
#define STACKEXCEPTIONS_H

#include <exception>

// Классы StackOverflow и StackUnderflow представляют две основные
// исключительные ситуации, которые могут возникнуть при работе со стеком

class StackOverflow : public std::exception {
public:
    StackOverflow() : reason_("Stack Overflow") {}

    const char *what() const noexcept override { return reason_; }

private:
    const char *reason_;
};

class StackUnderflow : public std::exception {
public:
    StackUnderflow() : reason_("Stack Underflow") {}

    const char *what() const noexcept override { return reason_; }

private:
    const char *reason_;
};

class WrongStackSize : public std::exception {
public:
    WrongStackSize() : reason_("Wrong Stack Size") {}

    const char *what() const noexcept override { return reason_; }

private:
    const char *reason_;
};

#endif
