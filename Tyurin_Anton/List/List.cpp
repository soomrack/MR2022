#include <iostream>

template<typename T>
class List;

template<typename T>
class Node {
    friend class List<T>;
protected:
    Node<T> *next;
    T data;
public:
    Node(T _data) : data(_data), next(nullptr){}
};

template<typename T>
class List {
protected:
    Node<T> *first_el;
    Node<T> *last_el;
public:
    List() : first_el(nullptr), last_el(nullptr) {}
    bool is_empty();
    void push_tale(T _data);
    void print();
    void push_head(T _data);
    void find(unsigned int id);
    void pop(unsigned int id);
    Node<T> loop(unsigned int id, auto *local);
};

template <typename T>
bool List<T>::is_empty() {
    return first_el == nullptr;
}

template <typename T>
void List<T>::push_tale(T _data){
    Node<T> *local = new Node<T>(_data);
    if (is_empty()) {
        first_el = local;
        last_el = local;
        return;
    }
    last_el->next = local;
    last_el = local;
}

template<typename T>
void List<T>::push_head(T _data){
    Node<T> *local = new Node<T>(_data);
    if (is_empty()) {
        first_el = local;
        last_el = local;
        return;
    }
    local->next = first_el;
    first_el = local;
}

template<typename T>
void List<T>::print() {
    if (is_empty()) {return;}
    Node<T> *local = first_el;
    while (local) {
        std::cout << local->data << " ";
        local = local->next;
    }
    std::cout << std::endl;
}

template<typename T>
void List<T>::find(unsigned int id) {
    if (is_empty()) {return;}
    auto *local = first_el;
    for(unsigned int idx; idx < id; idx++ ){
        local = local->next;
    }
   std::cout << local->data;
}

template<typename T>
Node<T> List<T>::loop(unsigned int id, auto *local) {
    for(unsigned int idx; idx < id; idx++ ){
        local = local->next;
    }
    return *local;
}


template<typename T>
void List<T>::pop(unsigned int id) {
    if (is_empty()) {return;}
    auto *local = first_el;
    auto *previous = first_el;
    auto *following = first_el;

    Node<T> _pop = loop(id,local);
    Node<T> _previous = loop(id - 1,previous);
    Node<T> _following = loop(id + 1,following);
    delete _pop;
    _previous.next = _following;
}

int main(){
    List<std::string> List;
    List.print();

    List.push_tale("he");
    List.push_tale("ll");
    List.push_tale("ow");
    List.push_tale(" ");
    List.push_tale("wo");
    List.push_tale("rl");
    List.push_tale("d");
    List.print();

    List.find(4);
    List.pop(4);
    return 0;
}