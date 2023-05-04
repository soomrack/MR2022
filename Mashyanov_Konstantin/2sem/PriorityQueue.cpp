class PriorityQueue {
private:
    int *data;  //  Массив элементов очереди
    int capacity;  //  Максимальная вместимость очереди
    int size;  //  Текущий размер очереди

public:
    PriorityQueue(int n);
    ~PriorityQueue();

    void enqueue(int value);  //  Добавление элемента в очередь
    void dequeue();  //  Удаление элемента из очереди
    int front();  
    int rear();
    bool is_empty();  //  Проверка, является ли очередь пустой
    bool is_full();  //  Проверка, является ли очередь полной
};

PriorityQueue::PriorityQueue(int n) {
    capacity = n;
    data = new int[capacity];
    size = 0;
}

PriorityQueue::~PriorityQueue() {
    delete[] data;
}

void PriorityQueue::enqueue(int value) {
    if (is_full()) {
        throw "PriorityQueue is full";
    } else {
        int i = 0;
        while (i < size && data[i] > value) {
            i++;
        }
        for (int j = size; j > i; j--) {
            data[j] = data[j - 1];
        }
        data[i] = value;
        size++;
    }
}

void PriorityQueue::dequeue() {
    if (is_empty()) {
        throw "PriorityQueue is empty";
    } else {
        for (int i = 0; i < size; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }
}

int PriorityQueue::front() {
    if (is_empty()) {
        throw "PriorityQueue is empty";
    } else {
        return data[size - 1];
    }
}

int PriorityQueue::rear() {
    if (is_empty()) {
        throw "PriorityQueue is empty";
    } else {
        return data[0];
    }
}

bool PriorityQueue::is_empty() {
    return (size == 0);
}

bool PriorityQueue::is_full() {
    return (size == capacity);
}

int main() {
    PriorityQueue pq(5);

    pq.enqueue(3);
    pq.enqueue(5);
    pq.enqueue(1);

    cout << "Front element of the priority queue: " << pq.front() << endl;
    cout << "Rear element of the priority queue: " << pq.rear() << endl;

    pq.dequeue();

    cout << "Front element of the priority queue after dequeue: " << pq.front() << endl;
    cout << "Rear element of the priority queue after dequeue: " << pq.rear() << endl;

    return 0;
}
