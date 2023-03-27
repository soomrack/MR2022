#include <iostream>
#include <string>
using namespace std;


template <typename T>
class List {
public:
    List();
    ~List();

    void push_back(T data);
    void pop_front();
    int getsize();
    void clear();

    T& operator[] (const int number);

private:

    template<typename T>
    class Node {
    public:
        Node *pNext;
        T data;
        Node (T data = T(), Node *pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
        }
    };
    int size;
    Node<T> *head;
};


template <typename T>
List<T>::List() {
    size = 0;
    head = nullptr;
}


template <typename T>
List<T>::~List() {
    clear();
}


template<typename T>
void List<T>::push_back(T data) {
    if (head == nullptr) {
        head = new Node<T>(data);
    }
    else {
        Node<T> *current = this->head;
        while (current->pNext != nullptr) {
            current = current->pNext;
        }
        current->pNext = new Node<T>(data);
    }
    size++;

}


template<typename T>
int List<T>::getsize() {
    return size;
}


template<typename T>
T &List<T>::operator[](const int number) {
    int counter = 0;
    Node<T> *current = this->head;
    while (current != nullptr) {
        if (counter = number) {
            return current->data;
        }
        current = current->pNext;
        counter++;
    }
}


template<typename T>
void List<T>::pop_front() {
    Node<T> *temp = head;
    head = head->pNext;
    delete temp;
    size--;
}


template<typename T>
void List<T>::clear() {
    while (size) {
        pop_front();
    }
}


int main() {

    List<int> lst;

    lst.push_back(5);
    lst.push_back(10);
    lst.push_back(12);
    cout << lst.getsize() << endl;
    cout << lst[2] << endl;

    /*int numCount;
    cin >> numCount;
    for (int i = 0; i < numCount; ++i) {
        lst.push_back(rand() % 10);
    }*/

    for (int i = 0; i < lst.getsize(); ++i) {
        cout << lst[i] << endl;
    }

    lst.pop_front();

    for (int i = 0; i < lst.getsize(); ++i) {
        cout << lst[i] << endl;
    }

    lst.clear();

    cout << lst.getsize() << endl;

    return 0;
}
