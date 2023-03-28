struct Node {
    int value;
    Node** left;
    Node** right;
};

void insert(Node** node, int value) {
    if (*node == nullptr) {
        *node = new Node{value, nullptr, nullptr};
    } else if (value < (*node)->value) {
        insert(((*node)->left), value);
    } else {
        insert(((*node)->right), value);
    }
}