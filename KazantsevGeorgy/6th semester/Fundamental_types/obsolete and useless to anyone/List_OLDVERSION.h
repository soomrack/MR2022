#include <iostream>
using namespace std;


template <class Q>
class List;
// сделать структуру из ListNode
template <class Q>
class ListNode
        // private сделать
{
protected:
    Q element;
    class ListNode *next;
    friend class List<Q>;
};

template <class Q>
class List
{
private:
    ListNode<Q> *head;
    unsigned int number_of_elements = 0;
    ListNode<Q> *Prev(ListNode<Q>*);
public:
    List() {head = nullptr;}
    int getCount() {return number_of_elements;}
    bool isEmpty() {return head == nullptr;}
    static Q getValue(ListNode<Q> *value) {return value->element;}
    static void setValue(ListNode<Q> *s, Q val) {s->element = val;}
    ListNode<Q> *getFirst() {return head;}

    ListNode<Q> *getLast();
    void Clear();
    ListNode<Q>* Next(ListNode<Q>*);
    ListNode<Q>* Add(Q, ListNode<Q>*);
    ListNode<Q>* Delete(ListNode<Q>*);
    void Print();
    void Swap(ListNode<Q>*, ListNode<Q>*);
};

template <typename Q>
ListNode<Q>* List<Q>::Add(Q num, ListNode<Q>* node)
{
    auto *new_cell = new ListNode<Q>();
    new_cell->element = num;
    if (node == nullptr)
    {
        if (head == nullptr)
        {
            new_cell->next = nullptr;
            head = new_cell;
        }
        else
        {
            new_cell->next = head;
            head = new_cell;
        }
        return new_cell;
    }
    new_cell->next = node->next;
    node->next = new_cell;
    number_of_elements++;
    return new_cell;
}

template <typename Q>
ListNode<Q>* List<Q>::Delete(ListNode<Q>* node)
//1) список пуст, 2) удаление head, 3) удаление не head
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node == head)
    {
        head = node->next;
        delete node;
        return head;
    }

    ListNode<Q> *prev = Prev(node); //указатель на предыдущий узел
    prev->next = node->next; //перенос указателя на предыдущий узел
    delete node;
    number_of_elements--;
    return prev;
}

template <typename Q>
ListNode<Q>* List<Q>::Next(ListNode<Q>* node)
{
    // node != nullptr
    if (isEmpty())
    {
        return nullptr;
    }
    return node->next;
}

template <typename Q>
ListNode<Q>* List<Q>::Prev(ListNode<Q>* node)
{
    if (isEmpty())
        return nullptr;

    if (node == head)
        return nullptr;

    ListNode<Q> *p = head;  // начинаем цикл с головы списка, пока не дойдем до указателя node,
    //при этом храня указатель на предыдущий элемент. Если нашли node, возвращаем указатель p
    while (p->next != node)
        p = p->next;
    return p;
}

template <typename Q>
ListNode<Q>* List<Q>::getLast()
{
    ListNode<Q> *p = head; // начинаем цикл с головы списка. пробегаем по списку до тех пор, пока указатель
    // на следующий элемент не будет nullptr. В этом случае возвращаем элемент на котором остановились
    while (Next(p) != nullptr)
        p = Next(p);
    return p;
}

template <typename Q>
void List<Q>::Clear()
//1) пустой список, не пустой список
{
    ListNode<Q> *p = head; //начинаем удаление с головы
    if (p == nullptr)
        return;

    // идем по списку с головы, на каждой итерации удаляем сам элемент и перемещаем указатель
    do {
        ListNode<Q> *d = p;
        p = Next(p); //переходим к следующему элементу
        delete d;
    }
    while (p != nullptr);

    number_of_elements = 0;
    head = nullptr;
}

template <typename Q>
void List<Q>::Print()
{
    if (isEmpty())
    {
        cout << "list is empty" << endl;
        return;
    }
    ListNode<Q>*p = head; //начинаем вывод с головы списка
    do
    {
        cout << getValue(p) << "\t";
        p = Next(p); //переходим к следующему элементу
    }
    while (p != nullptr);
    cout << endl;
}

template <typename Q>
void List<Q>::Swap(ListNode<Q> *node1, ListNode<Q> *node2)
// 1) оба списка пустые, 2) списки одинаковые, 3)
{
    ListNode<Q>*prev1 = Prev(node1);
    ListNode<Q>*prev2 = Prev(node2);
    ListNode<Q>*next1 = Next(node1);
    ListNode<Q>*next2 = Next(node2);
    if (node1 == nullptr || node2 == nullptr)
        return;
    if (node1 == node2)
        return;
    if (next2 == node1) //обмен соседних узлов
    {
        ListNode<Q> *p = node1;
        node1 = node2;
        node2 = p;
    }

    if (next1 == node2) //обмен соседних узлов
    {
        if (prev1 != nullptr) // первый элемент не head
            prev1->next = node2;
        else // первый элемент head
            head = node2;
        node2->next = node1;
        node1->next = next2;
        return;
    }
    // обмен не соседних узлов
    if (prev1 != nullptr) //prev 1не head
        prev1->next = node2;
    else
        head = node2;
    if (prev2 != nullptr) //prev2 не head
        prev2->next = node1;
    else
        head = node1;

    node2->next = next1;
    node1->next = next2;
}

