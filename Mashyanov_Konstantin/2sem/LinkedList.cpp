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
		Node* next;

		Node(T t = T(), Node* n = nullptr);  //  Конструктор Класса 
		};
	Node* head;  //  Голова списка
	int size;  //  Количество элементов

public:
	List();  //  Конструктор 
	~List();  //  Деструктор
	void pushBack(T value);  //  Метод добавления элемента в конец списка 
	void pushFront(T value);  //  Метод добавления элемента в начало списка
	int getSize() const;  //  Метод для объявления размера
	T& operator[] (int);  //  Возврат элемента методом счётчика индекса
	void popFront();  //  Метод удаления первого элемента
	void popBack();   //  Метод удаления последнего элемента
	void clear();  //  Метод очистки данных 
	void insert(T value, int index);  //  Метод добавления элемента по конкретному индексу
	void removeAt(int index);  //  Метод удаления элемента из списка по указанному индексу
};

template<class T>
void show(List<T>&);

int main()
{
	setlocale(0, "");
	List<int> list;
	for (int i = 0; i < 5; i++) list.pushBack(i);
	show(list);
	list.popBack();
	list.popFront();
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
void List<T>::pushBack(T value)
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
void List<T>::pushFront(T value)
{
	head = new Node(value, head);
	size++;
}

template<class T>
int List<T>::getSize() const
{
	return size;
}

template<class T>
T& List<T>::operator[](int index)
{
	if (index > size - 1 || index < 0)
	{
		string message = "Недопустимый индекс ";
		message.append(to_string(index));
		throw out_of_range(message);
	}
	Node* current = head;
	for (int i = 0; i < index; i++)
		current = current->next;
	return current->data;
}

template<class T>
void List<T>::popFront()
{
	if (size <= 0) return;
	Node* temp = head;  //  Временная переменная temp
	head = head->next;
	delete temp;
	size--;  //  Декремент размера списка
}

template<class T>
void List<T>::popBack()
{
	removeAt(size - 1);
}

template<class T>
void List<T>::clear()
{
	while (size) popFront();
}

template<class T>
void List<T>::insert(T value, int index)
{
	if (index > size || index < 0)
	{
		string message = "Недопустимый индекс ";
		message.append(to_string(index));
		throw out_of_range(message);
	}
	if (index == 0) pushFront(value);
	else
	{
		Node* previous = head;  //  Цикл для нахождения предшествующего индекса
		for (int i = 0; i < index - 1; i++)
			previous = previous->next;
		previous->next = new Node(value, previous->next);
		size++;
	}
}

template<class T>
void List<T>::removeAt(int index)  //  Метод обратный insert
{
	if (index > size - 1 || index < 0)
	{
		string message = "Недопустимый индекс ";
		message.append(to_string(index));
		throw out_of_range(message);
	}
	if (index == 0) popFront();
	else
	{
		Node* previous = head;
		for (int i = 0; i < index - 1; i++)
			previous = previous->next;
		Node* temp = previous->next;
		previous->next = temp->next;
		delete temp;
		size--;
	}
}

template<class T>
void show(List<T>& list)
{
	cout << "size = " << list.getSize() << endl;
	for (int i = 0; i < list.getSize(); i++) cout << list[i] << "  ";
	cout << endl;
}
