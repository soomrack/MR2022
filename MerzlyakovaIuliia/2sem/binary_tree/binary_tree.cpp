#include <iostream>


class binary_tree_exception: public std::exception {
private:
    const char* message;
public:
    binary_tree_exception(const char* const msg) : message(msg) {}
    const char* what() const noexcept override {
        return message;
    }
};

binary_tree_exception element_does_not_exist("element does not exist");
binary_tree_exception element_already_exists("element already exists");

template<typename T>
class binary_tree  {
public:
    binary_tree() = default;
    ~binary_tree();

    void add(const T& value);
    void del(const T& value);
    bool contains(const T& value);
    void print_tree();

private:
    struct Node {
        ~Node();

        // print_subtree печатает значения в поддереве в порядке возрастания
        void print_subtree();

        T value;
        Node* left_branch;
        Node* right_branch;
    };

    Node* root;

    // функция traverse делает следующее: она берет значение value и спускается по дереву пока не случится одно из двух
    //   * либо настанет конец дерева, то есть следующий переход будет по nullptr. В таком случае мы возвращаем пару из последней вершины и его предка.
    //   * либо найдется вершина, у которой значение равно value. В таком случае мы возвращаем пару из этой вершины и его предка.
    // При спуске мы пользуемся структурой бинарного дерева, то есть если value больше текущего значения в вершине,
    // мы спускаемся в правое поддерево, иначе в левое.
    std::pair<Node*, Node*> traverse(Node* node, const T& value, Node* parent = nullptr);
};

template<typename T>
binary_tree<T>::Node::~Node() {
    delete left_branch;
    delete right_branch;
}

template<typename T>
void binary_tree<T>::Node::print_subtree() {
    if (left_branch != nullptr)
        left_branch->print_subtree();
    std::cout << value << " ";
    if (right_branch != nullptr)
        right_branch->print_subtree();
}

template<typename T>
binary_tree<T>::~binary_tree() {
    delete root;
}

template<typename T>
void binary_tree<T>::add(const T &value) {
    if (root == nullptr) {
        root = new Node{value, nullptr, nullptr};
        return;
    }

    auto [parent, _] = traverse(root, value);
    if (parent->value == value)
        throw element_already_exists;


    if (parent->value < value) {
        parent->right_branch = new Node{value, nullptr, nullptr};
    } else {
        parent->left_branch = new Node{value, nullptr, nullptr};
    }
}

template<typename T>
bool binary_tree<T>::contains(const T &value) {
    if (root == nullptr)
        return false;

    auto [candidate, _] = traverse(root, value);
    return (candidate->value == value);
}

template<typename T>
void binary_tree<T>::del(const T &value) {
    if (root == nullptr)
        throw element_does_not_exist;

    auto [node, parent] = traverse(root, value);
    if (node->value != value)
        throw element_does_not_exist;

    if (node->left_branch == nullptr) {
        if (parent == nullptr) {
            root = node->right_branch;
        } else {
            if (parent->value < value)
                parent->right_branch = node->right_branch;
            else
                parent->left_branch = node->right_branch;
        }
        node->left_branch = node->right_branch = nullptr;
        delete node;
        return;
    }

    auto [replacement, replacement_parent] = traverse(node->left_branch, value, node);
    node->value = replacement->value;
    if (replacement_parent == node)
        node->left_branch = replacement->left_branch;
    else
        replacement_parent->right_branch = replacement->left_branch;
    replacement->left_branch = replacement->right_branch = nullptr;
    delete replacement;
}

template<typename T>
void binary_tree<T>::print_tree() {
    if (root != nullptr)
        root->print_subtree();
    std::cout << std::endl;
}

template<typename T>
std::pair<typename binary_tree<T>::Node*, typename binary_tree<T>::Node*> binary_tree<T>::traverse(Node* node, const T& value, Node* parent) {
    if (node->value == value ||
        (node->value < value && node->right_branch == nullptr) ||
        (node->value > value && node->left_branch == nullptr)) {
        return {node, parent};
    }

    if (node->value > value)
        return traverse(node->left_branch, value, node);
    else
        return traverse(node->right_branch, value, node);
}
/*
int main() {
    binary_tree<int> tree;
    tree.add(0);
    tree.add(1);
    tree.add(-1);
    tree.add(-10);
    tree.add(-3);
    tree.add(-6);
    tree.add(-4);
    tree.print_tree();
    tree.del(-1);
    tree.print_tree();

    tree = binary_tree<int>();

    tree.add(1);
    tree.add(2);
    std::cout << tree.contains(1) << " " << tree.contains(3) << std::endl;
    tree.print_tree();

    tree.add(0);
    tree.add(5);
    tree.add(4);
    std::cout << tree.contains(2) << " " << tree.contains(5) << " " << tree.contains(7) << std::endl;
    tree.print_tree();

    tree.del(5);
    std::cout << tree.contains(4) << std::endl;
    tree.print_tree();

    tree.del(1);
    std::cout << tree.contains(2) << std::endl;
    tree.print_tree();
}*/
