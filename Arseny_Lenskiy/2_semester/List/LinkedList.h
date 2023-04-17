template<typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node *next;

        Node(T data) : data(data), next(nullptr) {}
    };

private:
    Node *head;
    Node *tail;
    unsigned int size;

public:

    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList() { clear(); }

    void push_tail(T data);

    void push_head(T data);

    T pop_tail();

    T pop_head();

    int get_size() const { return size; }

    bool is_empty() const { return size == 0; }

    void clear();

    T get_item(unsigned int k);

    T get_tail() { return tail->data; }

    T get_head() {return head->data; }
};

template<typename T>
void LinkedList<T>::push_tail(T data) {
    Node *temp = new Node(data);
    if (tail == nullptr) {
        head = tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
    size++;
}

template<typename T>
void LinkedList<T>::push_head(T data) {
    Node *temp = new Node(data);
    if (head == nullptr) {
        head = tail = temp;
    } else {
        temp->next = head;
        head = temp;
    }
    size++;
}

template<typename T>
T LinkedList<T>::pop_tail() {
    if (tail == nullptr) throw std::underflow_error("List is empty!");

    T temp = tail->data;
    if (head == tail) {
        delete tail;
        head = tail = nullptr;
    } else {
        Node *prev_tail = head;
        while (prev_tail->next != tail) {
            prev_tail = prev_tail->next;
        }
        delete tail;
        tail = prev_tail;
        tail->next = nullptr;
    }
    size--;
    return temp;
}

template<typename T>
T LinkedList<T>::pop_head() {
    if (head == nullptr) throw std::underflow_error("List is empty!");

    T temp = head->data;
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node *old = head;
        head = head->next;
        delete old;
    }
    size--;
    return temp;
}

template<typename T>
void LinkedList<T>::clear() {
    while (head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

template<typename T>
T LinkedList<T>::get_item(unsigned int k) {
    if (k >= size) throw std::out_of_range("Index is out of range");

    Node *temp = head;
    for (int i = 0; i < k; i++) {
        temp = temp->next;
    }
    return temp->data;
}
