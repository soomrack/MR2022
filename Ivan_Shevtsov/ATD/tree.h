//
// Created by ivan on 03/04/23.
//

#ifndef ATD_TREE_H
#define ATD_TREE_H
namespace tree_names {

    class Node {
    public:
        int key;
        double value;
        Node* right;
        Node* left;

        inline Node();
        inline Node(double value, int key, Node* right = nullptr, Node* left = nullptr);

        ~Node();
    };

    class tree {
    private:
        unsigned depth;
        Node* root;
    public:
        tree();
        tree(double value, int key);

        unsigned get_depth() {return depth;}
        void push(double value);
        void insert(Node* node, int key, double value);
        Node* find(Node* node, int key);
        Node* delete_node(Node* node, int key);

        Node* get_max(Node* node);
        //void clear();
        //void show();

/*         ;
        void remove_first() ;
        void remove_last();
        void remove(int data);
        Node* operator[] (const int idx);
        Node* get_max(Node* node);
        Node* get_min(Node* node);*/

        //~tree();
    };
}

#endif //ATD_TREE_H
