#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// Определяем структуру элемента списка
struct Node
{
    int data;
    Node *next;
};

// Определяем класс списка
class List
{
private:
    Node *head;
    Node *tail;

public:
    List()
    {
        head = NULL;
        tail = NULL;
    }

    void push_tail(int value)  // Добавление элемента в конец списка
    {
        Node *temp = new Node;
        temp->data = value;
        temp->next = NULL;

        if(head == NULL)
        {
            head = temp;
            tail = temp;
            temp = NULL;
        }
        else
        {
            tail->next = temp;
            tail = temp;
        }
    }

    void display()  // Вывод списка
    {
        Node *temp = new Node;
        temp = head;
        while(temp != NULL)
        {
            cout << temp->data << "\t";
            temp = temp->next;
        }
    }

    void push_head(int value)
    {
        Node *temp = new Node;
        temp->data = value;
        temp->next = head;
        head = temp;
    }

    void push_position(int pos, int value)
    {
        Node *pre=new Node;
        Node *cur=new Node;
        Node *temp=new Node;
        cur=head;

        for(int i=1;i<pos;i++)
        {
            pre=cur;
            cur=cur->next;
        }

        temp->data=value;
        pre->next=temp;
        temp->next=cur;
    }

    void delete_head()
    {
        Node *temp = new Node;
        temp = head;
        head = head->next;
        delete temp;
    }

    void delete_tail()
    {
        Node *current = new Node;
        Node *previous = new Node;
        current = head;
        while(current->next != NULL)
        {
            previous = current;
            current = current->next;
        }
        tail = previous;
        previous->next = NULL;
        delete current;
    }

    void delete_position(int pos)
    {
        Node *current = new Node;
        Node *previous = new Node;
        current = head;
        for(int i=1;i<pos;i++)
        {
            previous = current;
            current = current->next;
        }
        previous->next = current->next;
    }

    void fillWithRandom()
    {
        srand(time(0));
        for (int el = 0; el < 5; el++)
        {
            push_tail(rand() % 20);
        }
    }

    void clearList()
    {
        head = NULL;
        tail = NULL;
    }
};

int main()
{
    List l;

    l.fillWithRandom();
    l.display();
    cout <<" \n";
    l.push_tail(55);
    l.display();
    cout <<" \n";
    l.push_head(50);
    l.display();
    cout <<" \n";
    l.push_position(5,60);
    l.display();
    cout <<" \n";
    l.delete_head();
    l.display();
    cout <<" \n";
    l.delete_tail();
    l.display();
    cout <<" \n";
    l.delete_position(4);
    l.display();
    l.clearList();
    return 0;
}