//
// Created by sirbo on 19.03.2023.
//

#ifndef DYNAMIC_ARRAY_NODE_H
#define DYNAMIC_ARRAY_NODE_H


class Node {
public:
    int data;
    Node *next;
    Node(){
        data = 0;
        next = nullptr;
    }
    explicit Node(int new_data){
        data = new_data;
        next = nullptr;
    }

    void push_next();
    void pop_next();
};


#endif //DYNAMIC_ARRAY_NODE_H
