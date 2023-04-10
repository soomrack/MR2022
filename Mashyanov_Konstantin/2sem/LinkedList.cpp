#include <iostream>
#include <string>
using namespace std;

template<class T>  //  Шаблон Клаcc List
class List
{
	class Node  //  Класс узла
	{
	public:
		T data;  //  Реализация объекта (без привязки к типу данных) 
		Node *next;

		Node(T t = T(), Node *n = nullptr);  //  Конструктор Класса 
		};
	Node *head;  //  Голова списка
	
public:
	List();  //  Конструктор 
	~List();  //  Деструктор
	void push_tail(T value);  //  Метод добавления элемента в конец списка 
	void push_head(T value);  //  Метод добавления элемента в начало списка
	void pop_tail();  //  Метод удаления первого элемента
	void pop_head();   //  Метод удаления последнего элемента
	void delete_head();  //  Удаление первого
        void delete_tail();  //  Удаление последнего 
	void clear();  //  Метод очистки данных 
        void delete_position(int pos);
};

template<class T>
void show(List<T>&);

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

template <class T>
List<T>::Node::Node(T t, Node* n)
{
	data = t;
	next = n;
}

template<class T>
List<T>::List()
{
	size = 0;
	head = nullptr;
}

template<class T>
List<T>::~List()
{
	clear();  //  Очистка всех элементов
}

template<class T>
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
}

template<class T>
void List<T>::push_head(T value)
{
	head = new Node(value, head);
	size++;
}


template<class T>
void List<T>::pop_head()
{
	if (size <= 0) return;
	Node *temp = head;  //  Временная переменная temp
	head = head->next;
	delete temp;
	size--;  //  Декремент размера списка
}

template<class T>
void List<T>::pop_tail()
{
	removeAt(size - 1);
}

template<class T>
void List<T>::clear()
{
	while (size) pop_head();
}

  void List::delete_head(){
        Node *temp = new Node;
        temp = head;
        head = head->next;
        delete temp;
    }

    void List::delete_tail()
    {
        Node *current = new Node;
        Node *previous = new Node;
        current = head;
        while(current->next != nullptr)
        {
            previous = current;
            current = current->next;
        }
        tail = previous;
        previous->next = NULL;
        delete current;
    }

    void List::delete_position(int pos){
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


template<class T>
void show(List<T>& list)
{
	cout << "size = " << list.getSize() << endl;
	for (int i = 0; i < list.getSize(); i++) cout << list[i] << "  ";
	cout << endl;
}
