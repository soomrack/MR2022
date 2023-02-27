#include <iostream>

template<class T>
class Node 
{
    template<class TT> friend class LinkedList;
private:
    T data_;
    Node* prev, * next;

private:
    Node(T data) 
    {
        data_ = data;
        prev = next = nullptr;
    }
};

template<class T>
class LinkedList 
{
private:
    Node<T>* head, * tail;
    size_t size;

public:
    LinkedList() 
    {
        head = tail = nullptr;
        size = 0;
    }

    ~LinkedList() 
    {
        while (head != nullptr)
            pop_front();
        size = 0;
    }

    size_t getSize()
    {
        return size;
    }

    Node<T>* push_front(T data) 
    {
        auto ptr = new Node<T>(data);
        ++size;

        ptr->next = head;
        if (head != nullptr)
            head->prev = ptr;

        if (tail == nullptr)
            tail = ptr;

        head = ptr;
        return ptr;
    }


    Node<T>* push_back(T data) 
    {
        auto ptr = new Node<T>(data);
        ++size;

        ptr->prev = tail;
        if (tail != nullptr)
            tail->next = ptr;

        if (head == nullptr)
            head = ptr;

        tail = ptr;
        return ptr;
    }

    void pop_front() 
    {
        if (head == nullptr) return;

        auto ptr = head->next;
        if (ptr != nullptr)
            ptr->prev = nullptr;
        else
            tail = nullptr;
        
        --size;
        delete head;
        head = ptr;
    }


    void pop_back() 
    {
        if (tail == nullptr) return;

        auto ptr = tail->prev;
        if (ptr != nullptr)
            ptr->next = nullptr;
        else
            head = nullptr;
        
        --size;
        delete tail;
        tail = ptr;
    }

    Node<T>* getNode(int index) 
    {
        if (index < 0)
            return nullptr;

        auto ptr = head;

        for (int i = 0; i != index; ++i) {
            if (ptr == nullptr)
                return ptr;
            ptr = ptr->next;
        }

        return ptr;
    }


    T operator [] (int index) 
    {
        return getNode(index)->data_;
    }

    Node<T>* insert(int index, double data) 
    {
        auto right = getNode(index);
        if (right == nullptr)
            return push_back(data);

        auto left = right->prev;
        if (left == nullptr)
            return push_front(data);

        auto ptr = new Node<T>(data);
        ++size;

        ptr->prev = left;
        ptr->next = right;
        left->next = ptr;
        right->prev = ptr;

        return ptr;
    }

    void erase(int index) 
    {
        auto ptr = getNode(index);
        if (ptr == nullptr)
            return;

        if (ptr->prev == nullptr) {
            pop_front();
            return;
        }

        if (ptr->next == nullptr) {
            pop_back();
            return;
        }

        auto left = ptr->prev;
        auto right = ptr->next;
        left->next = right;
        right->prev = left;
        
        --size;
        delete ptr;
    }
};

int main()
{
    using namespace std;

    LinkedList<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_front(4); // 4 1 2 3
    
    lst.insert(2, 5); // 4 1 5 2 3
    
    lst.pop_back(); // 4 1 5 2
    lst.pop_front(); // 1 5 2
    lst.push_front(6); // 6 1 5 2
    lst.erase(3); // 6 1 5
    
    for (int i = 0; i < lst.getSize(); ++i)
        cout << lst[i] << " ";

    std::cout << std::endl;
}
