#ifndef MR2022_QUEUE_H
#define MR2022_QUEUE_H


class Queue {
private:
    int size;
    double* data;
    int first;
    int last;
    int items;
public:
    Queue(int size);
    ~Queue();

    void insert(int value);
    double remove();
    double getFirst();
    bool isEmpty();
    bool isFull();
    int getSize();

};


Queue::Queue(int my_size) {
    size = my_size;
    data = new double[size];
    first = 0;
    last = -1;
    items = 0;
};


Queue::~Queue() {
    delete[] data;
};


void Queue::insert(int value) {
    if (last == size - 1) {
        last = -1;
        items = 0;
    }
    data[++last] = value;
    ++items;
}


double Queue::remove() {
    double temp = data[++first];
    if (first == size)
        first == 0;
    --items;
    return temp;
}


double Queue::getFirst() {
    return data[first];
}


bool Queue::isEmpty() {
    return (items == 0);
};


bool Queue::isFull() {
    return (items == size);
};


int Queue::getSize() {
    return items;
}


#endif //MR2022_QUEUE_H
