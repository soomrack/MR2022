#ifndef MR2022_LINKED_LIST_H
#define MR2022_LINKED_LIST_H

template <typename T>
class List
{
public:

    List();
    ~List();

    void pop_front();
    void pop_back();
    void push_back(T data);
    void push_front(T data);
    void insert(T data, unsigned int idx);
    void clear();
    void remove(unsigned int);
    int get_size();
    T& operator[](const unsigned);
private:

    class Node
    {
    public:
        Node* next;
        T data;

        Node(T data = T(), Node* next = nullptr)
        {
            this -> data = data;
            this -> next = next;
        }
    };
    unsigned int size;
    Node *head;
};

template <typename T>
List<T>::List()
{
    size = 0;
    head = nullptr;
}

template<typename T>
List<T>::~List()
{
    clear();
}

template<typename T>
int List<T>::get_size() {return size;}

template<typename T>
T& List<T>::operator[](const unsigned idx)
{
    unsigned int i = 0;
    Node* current = this->head;
    while(current)
    {
        if (i == idx)
        {
            return current->data;
        }
        current = current->next;
        i++;
    }
}
template<typename T>
void List<T>::pop_front()
{
    Node* temp = head;
    head = head->next;
    delete temp;
    temp = nullptr;
    size--;
}

template<typename T>
void List<T>::push_back(T data)
{
    if(!head)
    {
        head = new Node(data);
    }
    else
    {
        Node* current = this->head;
        while (current->next != nullptr)
        {
          current = current -> next;
        }
        current->next = new Node(data);
    }
    size++;
}

template<typename T>
void List<T>::clear()
{
    while(size)
    {
        pop_front();
    }
}

template<typename T>
void List<T>::push_front(T data)
{
    head = new Node(data,head);
    size++;
}

template<typename T>
void List<T>::remove(unsigned int idx)
{
    Node* previous = this->head;
    for(unsigned int i = 0; i < idx - 1; i++)
    {
        previous = previous -> next;
    }
    Node* doDelete = previous -> next;
    previous -> next = doDelete -> next;
    delete doDelete;
    doDelete = nullptr;
    size--;
}

template<typename T>
void List<T>::pop_back()
{
    Node* current = head;
    Node* temp;
    while(current->next)
    {
        temp = current;
        current = current->next;
    }
    delete current;
    temp->next = nullptr;
    size--;
}

template<typename T>
void List<T>::insert(T data, unsigned int idx)
{
    if (idx == 0) push_front(data);
    else
    {
        size++;
        Node* previous = head;
        for(unsigned int i = 0; i < idx - 1; i++)
        {
            previous = previous -> next;
        }
        previous->next = new Node(data,previous->next);
    }
}


#endif //MR2022_LINKED_LIST_H
