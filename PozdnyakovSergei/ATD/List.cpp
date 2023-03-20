#include <iostream>
using namespace std;

struct Node{
    int value;
    Node *next;
};

class list{
private:
    Node *first;
    Node *last;

public:
    list(){
        first = nullptr;
        last = nullptr;
    }

    void push_back(int val) {
        Node *temp = new Node;
        temp->value = val;
        temp->next = nullptr;

        if (first == nullptr) {

        } else {
            last->next = temp;
            last = temp;
        }
    }

    void push_first(int val) {
        Node *temp = new Node;
        temp->value = val;
        temp->next = first;
        first = temp;
    }

    void delete_last();
};

int main() {
}
