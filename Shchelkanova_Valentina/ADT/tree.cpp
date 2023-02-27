#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
int tabs = 0;


struct Node {
    int data;
    Node* leftChild;
    Node* rightChild;
};

class Tree {
    Node* root;
public:
    Tree() {
        root = 0;
    }

    void insert(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->leftChild = 0;
        newNode->rightChild = 0;

        if (root == 0) {
            root = newNode;
        }
        else {
            Node* tmp = root;
            while (tmp != 0) {
                if (value < tmp->data) {
                    if (tmp->leftChild == 0) {
                        tmp->leftChild = newNode;
                        break;
                    }
                    else
                        tmp = tmp->leftChild;
                }
                else {
                    if (tmp->rightChild == 0) {
                        tmp->rightChild = newNode;
                        break;
                    }
                    else
                        tmp = tmp->rightChild;
                }
            }
        }
    }

    void deleteNode(int value) {
        if (root == 0)
            return;
        else {
            Node* currNode = root;
            Node* parrentNode = 0;
            while (currNode != 0 && currNode->data != value) {
                parrentNode = currNode;
                if (value < currNode->data)
                    currNode = currNode->leftChild;
                else
                    currNode = currNode->rightChild;
            }
            if (currNode == 0)
                return;
            if (currNode->leftChild == 0 && currNode->rightChild == 0) {
                if (parrentNode == 0)
                    root = 0;
                else {
                    if (parrentNode->leftChild == currNode)
                        parrentNode->leftChild = 0;
                    else
                        parrentNode->rightChild = 0;
                }
                delete currNode;
            }
            else if (currNode->leftChild == 0 || currNode->rightChild == 0) {
                Node* tmp = 0;
                if (currNode->leftChild == 0)
                    tmp = currNode->rightChild;
                else
                    tmp = currNode->leftChild;
                if (parrentNode == 0)
                    root = tmp;
                else {
                    if (parrentNode->leftChild == currNode)
                        parrentNode->leftChild = tmp;
                    else
                        parrentNode->rightChild = tmp;
                }
                delete currNode;
            }
            else {
                Node* tmp = currNode->rightChild;
                Node* tmpParrent = currNode;
                while (tmp->leftChild != 0) {
                    tmpParrent = tmp;
                    tmp = tmp->leftChild;
                }
                currNode->data = tmp->data;
                if (tmpParrent->leftChild == tmp)
                    tmpParrent->leftChild = 0;
                else
                    tmpParrent->rightChild = 0;
                delete tmp;
            }
        }
    }

    void randomFill(int size) {
        srand(time(0));
        for (int i = 0; i < size; i++)
            insert(rand() % 100);
    }

    void print(Node* root) {
        if (root != 0) {
            tabs += 3;
            print(root->leftChild);
            for(int tab = 0; tab < tabs; tab++)cout << " ";
            cout << root->data << endl;
            print(root->rightChild);
            tabs -= 3;
            return;
        }
    }

    void printTree() {
        print(root);
        cout << endl;
    }

    void deleteTree(Node* root) {
        if (root != 0) {
            deleteTree(root->leftChild);
            deleteTree(root->rightChild);
            delete root;
        }
    }

    ~Tree() {
        deleteTree(root);
    }
};

int main() {
    Tree tree;
    tree.randomFill(5);
    tree.printTree();
    cout << endl;
    tree.insert(5);
    tree.printTree();
    int el;
    cin >> el;
    tree.deleteNode(el);
    tree.printTree();
    return 0;
}