#include "Linked_list.h"

const int BASE_SIZE = 100;

template<typename T>
class Queue_on_LL: public Linked_list<T> {

private:
    size_t max_size;

public:
    explicit Queue_on_LL(int max_size = BASE_SIZE): max_size(max_size) {};

    void pop() {this->pop_head();}
    void push(T elem) {if ((this->size + 1) > max_size)
            throw Linked_list_exception("Queue is overflow!");
            this->push_tail(elem);}

    void print_queue() {this->print();}

};

int main() {
    Queue_on_LL<int> test(10);
    for (int idx = 0; idx < 10; idx++) {
        test.push(idx);
        test.print_queue();
    }
    test.print_queue();
    test.pop();
    test.push(100);
    test.print_queue();
    Queue_on_LL<int> test2(test);
    for (int idx = 0; idx < 10; idx++) {
        test2.pop();
        std::cout << test2.get_size() << std::endl;
        if (idx == 9) continue;
        test2.print_queue();
    }
    return 0;
}