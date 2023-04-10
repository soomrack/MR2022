#include <iostream>
#include <string>
using namespace std;

typedef double MyData;
class ListNode {
public:
	MyData data;
private:
	Node* next;
public:
	Node() = delete;
	Node(const MyData data, const Node* next = nullptr);
public: 
	void add_next(const MyData value);
	void del_next();
	Node* get_next();
};

class List {
private:
	Node *head;
public:
	List();
	~List(); 
public:
	void add_head(const MyData value);  
	void del_head();  
	Node* get_head();  
	void clear();  
    
};

// реализовать верхнюю часть!

List::List(){
        head = nullptr;
        tail = nullptr;
    }

void List::add_head(){
        Node *temp = new Node;
        temp->data = value;
        temp->next = head;
        head = temp;
    }

void List::del_head(){
        Node *temp = new Node;
        temp = head;
        head = head->next;
        delete temp;
    }



int main()
{
	setlocale(0, "");
	List<int> list;
	for (int i = 0; i < 5; i++) list.push_tail(i);
	show(list);
	list.pop_tail();
	list.pop_head();
	list[1] = 777;
	show(list);
	system("pause");
}


List<T>::Node::Node(T t, Node* n)
{
	data = t;
	next = n;
}


List<T>::List()
{
	size = 0;
	head = nullptr;
}


List<T>::~List()
{
	clear();  //  Очистка всех элементов
}

//template<class T>
void List<T>::push_tail(T value)
{
	if (head == nullptr)  //  Проверка вершины на null 
		head = new Node(value);
	else
	{
		for (Node* current = head; ; current = current->next)  //  Указатель узла (поиск вершины с адресом null) )
			if (current->next == nullptr)
			{
				current->next = new Node(value);
				break;
			}
	}
	size++;
}//

template<class T>
void List<T>::push_head(T value)
{
	head = new Node(value, head);
	size++;
}



    void List::display(){  // Вывод списка
        Node *temp = new Node;
        temp = head;
        while(temp != nullptr)
        {
            cout << temp->data << "\t";
            temp = temp->next;
        }
    }
