//
// Created by ivan on 03/04/23.
//

#ifndef ATD_GRAPH_H
#define ATD_GRAPH_H
#include "iostream"
#include "dynamic_array.h"


namespace graph_names {
    class graph_exceptions: public std::domain_error{
    public:
        graph_exceptions(const char* massage): std::domain_error(massage){}
    };

    graph_exceptions ZERO_SIZE("zero size error");
    graph_exceptions QUEUE_OUT_OF_TRE_RANGE("index out of the range");
    graph_exceptions QUEUE_POP_ERROR("can`t pop from empty queue");
    graph_exceptions QUEUE_SHOW_ERROR("can`t show zero size queue");

    class Node{
    public:
        double data;
        DynArr_names::dynamic_array neighbors;

        Node(double data);
    };

    class graph {
    private:
        DynArr_names::dynamic_array nodes;
    public:
        graph();
        graph(double value);

        void add_node(double data);
        void add_edge(double data_1, double data_2);
        void delete_node(double data);
        void delete_edge(double data_1, double data_2);

        void show();
        void clear();

        ~graph();
    };



} // graph_names

#endif //ATD_GRAPH_H
