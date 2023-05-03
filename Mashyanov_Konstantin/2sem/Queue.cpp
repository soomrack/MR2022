#include <iostream>
using namespace std;

class Queue {
private:
  int* data;  
  int front;  // Индекс элемента, находящегося в начале очереди
  int rear;   // Индекс элемента, находящегося в конце очереди
  int size;   

public:
  Queue(int n);
  ~Queue();
  int get_front();  //  Метод для получения первый элемент очереди
  int get_rear();  //  Метод для получения последний элемент очереди
  void enqueue(int value);  //  Метод для добавления элемента в конец очереди
  void dequeue();  //  Метод для удаления элемента из начала очереди
  void display();  //  Метод для отображения элементов в очереди
  bool is_empty();  // Метод для проверки, пуста ли очередь
  bool is_full();  // Метод для проверки, полна ли очередь
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
  if (front == -1) { 
    throw "Queue is Empty";
  } else {
    return data[front];
  }
}

int Queue::get_rear() {
  if (rear == -1) { 
    throw "Queue is Empty";
  } else {
    return data[rear];
  }
}

void Queue::enqueue(int value) {
  if (rear == size - 1) { 
    throw "Queue is Full";
  } else {
    rear++;
    data[rear] = value;
    if (front == -1) { 
      front = 0;
    }
  }
}

void Queue::dequeue() {
  if (front == -1) { 
    throw "Queue is Empty";
  } else {
    front++;
    if (front > rear) { 
      front = rear = -1;
    }
  }
}

void Queue::display() {
  if (front == -1) { 
    cout << "Queue is Empty" << endl;
  } else {
    for (int i = front; i <= rear; i++) {
      cout << data[i] << " ";
    }
    cout << endl;
  }
}

bool Queue::is_empty() {
return (front == -1 && rear == -1);
}

bool Queue::is_full() {
return (rear == size - 1);
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

q.dequeue();

q.display();

return 0;
}
