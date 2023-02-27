#include <iostream>
template<typename T>
class List;

template<typename T>
class Node {
    friend class List<T>;
protected:
    unsigned int adress;
    T *data;
public:
    Node(unsigned int newadress, T *newdata);
};

template<typename T>
Node<T>::Node(unsigned int newadress, T *newdata){
    adress = newadress;
    data = new T[adress];
    data = newdata;
}

template<typename T>
class List {
protected:
    unsigned int size;
    Node<T> first_el;
    Node<T> last_el;
public:
    //void print(const List<T> &List);
    List();
    void push_tale(unsigned int nadress, T ndata);
};

template<typename T>
List<T>::List(){
    Node<T> Node(0,0);
    size = 1;
    first_el = Node;
    last_el = Node;
}

/* template<typename T>
void List<T>::print(const List<T> &List){
    for (unsigned int idx = 0; idx < List.size; idx++){
        std::cout << List.data[idx] << ' ';
    }
    std::cout << std::endl;
} */

template<typename T>
void List<T>::push_tale(unsigned int nadress, T ndata){
    Node<T> Tale;
    Tale.adress = nadress;
    Tale.data = ndata;
    last_el = Tale;
}

int main(){
    List<double> List();
    List.push_tale(0,12);
    return 0;
}