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
    Node<T> *first_el; // head
    Node<T> *last_el;  // tail
    unsigned int size;
public:
    List() : first_el(nullptr), last_el(nullptr), size(0) {}
    bool is_empty();
    void push_tale(T _data);
    void print();
    void push_head(T _data);
    void find(unsigned int id);
    void pop(unsigned int id);
    Node<T> loop(unsigned int id, auto *local);
    Node<T> *operator[](const int index);

    void remove_first();

    void remove_last();

    unsigned int get_size();
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
        size++;
        return;
    }
    last_el->next = local;
    last_el = local;
    size++;
}

template<typename T>
void List<T>::push_head(T _data){
    Node<T> *local = new Node<T>(_data);
    if (is_empty()) {
        first_el = local;
        last_el = local;
        size++;
        return;
    }
    local->next = first_el;
    first_el = local;
    size++;
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
   std::cout << local->data << std::endl;
}

template<typename T>
void List<T>::remove_first() {
    if (is_empty()) return;
    Node<T>* local = first_el;
    first_el = local->next;
    delete local;
    size--;
}

template<typename T>
void List<T>::remove_last() {
    if (is_empty()) return;
    if (first_el == last_el) {
        remove_first();
        return;
    }
    Node<T>* local = first_el;
    while (local->next != last_el) local = local->next;
    local->next = nullptr;
    delete last_el;
    last_el = local;
    size--;
}

template<typename T>
void List<T>::pop(unsigned int id) {
    if (is_empty()) return;
    if (id > size) return;
    if (0 == id ) {
        remove_first();
        return;
    }
    else if (id + 1 == size) {
        remove_last();
        return;
    }
    Node<T>* local = first_el;
    for (int idx = 0; idx < id - 1; idx++) {
        local = local->next;
    }
    local->next = local->next->next;
    size--;
}

template<typename T>
unsigned int List<T>::get_size() {
    return size;
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
    //Node *ptr = List.find("ff");
   //List.push_next(Node* ptr, "gg");
   // delete_next
    List.print();
    std::cout << List.get_size() << std::endl;
    List.find(4);
    List.pop(4);
    List.print();

    return 0;
}