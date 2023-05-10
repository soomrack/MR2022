#include <iostream>
using namespace std;

class Queue {
private:
int* data;
int front; // Индекс элемента, находящегося в начале очереди
int rear; // Индекс элемента, находящегося в конце очереди
int size;

public:
Queue(int n);
~Queue();
int get_front(); // Метод для получения первый элемент очереди
int get_rear(); // Метод для получения последнего элемента очереди
void enqueue(int value); // Метод для добавления элемента в конец очереди
void display(); // Метод для отображения элементов в очереди
bool is_empty(); // Метод для проверки, пуста ли очередь
bool is_full(); // Метод для проверки, полна ли очередь
void push(int value);  // Метод для добавления элемента в начало очереди
int pop(); // Метод для удаления и возврата элемента из начала очереди

};

Queue::Queue(int n) {
size = n;
data = new int[size];
front = -1;
rear = -1;
}

Queue::~Queue() {
delete[] data;
}

int Queue::get_front() {
return data[front];
}

int Queue::get_rear() {
return data[rear];
}

void Queue::enqueue(int value) {
rear++;
data[rear] = value;
if (front == -1) {
front = 0;
}
}



void Queue::display() {
  for (int i = front; i <= rear; i++) {
    cout << data[i] << " ";
  }
  cout << endl;
}

bool Queue::is_empty() {
return (front == -1 && rear == -1);
}

bool Queue::is_full() {
return (rear == size - 1);
}

void Queue::push(int value) {
  rear++;
  data[rear] = value;
  if (front == -1) {
    front = 0;
  }
}

int Queue::pop() {
  int value = data[front];
  front++;
  if (front > rear) {
    front = rear = -1;
  }
  return value;
}

int main() {
Queue q(4);

q.enqueue(1);
q.enqueue(2);
q.enqueue(3);
q.enqueue(4);

q.display();

cout << "Front: " << q.get_front() << endl;
cout << "Rear: " << q.get_rear() << endl;

q.pop();

q.display();

return 0;
}
