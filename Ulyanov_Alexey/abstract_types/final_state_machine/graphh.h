#ifndef FINAL_STATE_MACHINE_GRAPHH_H
#define FINAL_STATE_MACHINE_GRAPHH_H

#include <iostream>
#include "algorithm"
#include "dynamic_array.h"


template <typename T>
class Graph {

private:
    Dynamic_array<T> vertexs;


public:

    void add_node(const T new_node);
    void add_path(const unsigned int from, const unsigned int to, const bool add_reverse = false);

    bool contains(const unsigned int node_name);

    void del_node(const unsigned int name_to_del);
    void del_path(const unsigned int from, const unsigned int to);

    void output();

    T* get(const unsigned int node_name);

};


template <typename T>
void Graph<T>::add_node(const T new_node) {
    vertexs.push_back(new_node);
}


template <typename T>
void Graph<T>::add_path(const unsigned int from, const unsigned int to, const bool add_reverse) {
    if (!contains(from)) add_node(from);
    if (!contains(to)) add_node(to);

    T* node_from = get(from);
    T* node_to = get(to);

    unsigned int pos_of_to = node_from->neighbors.position(node_to);
    if (pos_of_to == 0) {
        node_from->neighbors.push_back(node_to);
    }

    if (add_reverse){
        add_path(to, from, false);
    }

}


template <typename T>
void Graph<T>::del_node(const unsigned int name_to_del) {
    T* node_to_del = get(name_to_del);

    unsigned int pos_node_to_del_in_vertex = vertexs.position(*node_to_del);
    if (pos_node_to_del_in_vertex == 0) return;

    for (unsigned int idx = 0; idx < vertexs.length(); idx++){
        unsigned int pos_node_to_del_in_neighbours = vertexs[idx].neighbors.position(node_to_del);
        if (pos_node_to_del_in_neighbours == 0) continue;

        vertexs[idx].neighbors.del(pos_node_to_del_in_neighbours - 1);
        vertexs[idx].weights.del(pos_node_to_del_in_neighbours - 1);
    }

    vertexs.del(pos_node_to_del_in_vertex - 1);
}


template <typename T>
void Graph<T>::del_path(const unsigned int from, const unsigned int to) {
    unsigned int pos_node_from_in_vertex = vertexs.position(*get(from));
    if (pos_node_from_in_vertex == 0) return;

    unsigned int pos_node_to_in_froms_neighbours = vertexs[pos_node_from_in_vertex - 1].neighbors.position(get(to));
    if (pos_node_to_in_froms_neighbours == 0) return;

    vertexs[pos_node_from_in_vertex - 1].neighbors.del(pos_node_to_in_froms_neighbours - 1);
    vertexs[pos_node_from_in_vertex - 1].weights.del(pos_node_to_in_froms_neighbours - 1);

}


template <typename T>
bool Graph<T>::contains(const unsigned int node_name) {
    if (vertexs.length() == 0) return false;

    for (unsigned int idx = 0; idx < vertexs.length(); idx++){
        if (vertexs[idx].value == node_name) return true;
    }
    return false;
}


template <typename T>
T* Graph<T>::get(const unsigned int node_name) {

    if (!contains(node_name)) return new T();

    for (unsigned int idx = 0; idx < vertexs.length(); idx++){
        if (vertexs[idx].value == node_name) return &vertexs[idx];
    }

    return new T();
}

#endif //FINAL_STATE_MACHINE_GRAPHH_H
