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



int main(){
    List<std::string> List;
    List.print();


    List.push_tale("ending");
    List.print();

    List.push_head("begining");
    List.print();

    return 0;
}