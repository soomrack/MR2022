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

//  Контруктор узла
ListNode(const MyData data, const ListNode* next = nullptr) {
        this->data = data;
        this->next = next;
    }
};

public: 
	void add_next(const MyData value);
	void del_next();
	Node* get_next();
};

class List {
private:
	Node *head;  //  Указатель на первый узел списка
public:
	List() {
        head = nullptr;
    }
	
    ~List() {
        clear();
    } 

public:
	void add_head(const MyData value);  
	void del_head();  
	Node* get_head();  
	void clear();  
    
};

//  Добавление элемента в начало списка
  void add_head(const MyData value) {
        head = new ListNode(value, head);
    }

//  Удаление первого элемента списка
    void del_head() {
        if (head == nullptr) {
            return;
        }

        ListNode* temp = head;
        head = head->next;
        delete temp;
    }

//  Получение указателя на первый элемент списка
    Node* get_head() {
        return head;
    }

//  Удаление всех элементов списка
    void clear() {
        while (head != nullptr) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

//  Добавление узла
    void add_next(ListNode* node, const MyData value) {
        if (node == nullptr) {
            return;
        }

        node->next = new ListNode(value, node->next);
    }

//  Удаление узла
    void del_next(ListNode* node) {
        if (node == nullptr || node->next == nullptr) {
            return;
        }

        ListNode* temp = node->next;
        node->next = temp->next;
        delete temp;
    }
};
