#include <iostream>
#include "Aho_Corasick.h"

AC::AC() {
    this->tree.push_back(make_vertex(0, '$'));
}

void AC::add_string(const string &str) {
    int num = 0;
    for (int i = 0; i < (int) str.length(); i++) {
        char symbol = str[i];
        if(this->tree[num].next_vertex.find(i) == this->tree[num].next_vertex.end()){
            this->tree.push_back(make_vertex(num, (char) symbol));
            this->tree[num].next_vertex[symbol] = (int) this->tree.size() - 1;
        }
        num = this->tree[num].next_vertex[symbol];
    }
    this->tree[num].is_final = true;
    this->pattern.push_back(str);
    this->tree[num].pattern_number = (int) this->pattern.size() - 1;
}

void AC::find(const string &str) {
    int u = 0;
    for (int i = 0; i < (int) str.length(); i++){
        u = get_move(u, (char) (str[i]));
        this->check(u, i + 1);
    }
}

tree_vertex AC::make_vertex(int parent, char symbol) {
    tree_vertex vertex;
    vertex.is_final = false;
    vertex.suffix_link = -1;
    vertex.suffix_final_link = -1;
    vertex.parent = parent;
    vertex.symbol = symbol;
    return vertex;
}

int AC::get_suffix_link(int vertex) {
    if(this->tree[vertex].suffix_link == -1) {
        if (vertex == 0 || this->tree[vertex].parent == 0)
            this->tree[vertex].suffix_link = 0;
        else
            this->tree[vertex].suffix_link = get_move(get_suffix_link(this->tree[vertex].parent), this->tree[vertex].symbol);
    }
    return this->tree[vertex].suffix_link;
}

int AC::get_move(int vertex, char symbol) {
      if(this->tree[vertex].move.find(symbol) == this->tree[vertex].move.end()){
        if(this->tree[vertex].next_vertex.find(symbol) != this->tree[vertex].next_vertex.end()){
            this->tree[vertex].move[symbol] = this->tree[vertex].next_vertex[symbol];
        } else {
            if (vertex == 0)
                this->tree[vertex].move[symbol] = 0;
            else
                this->tree[vertex].move[symbol] = get_move(get_suffix_link(vertex), (char) symbol);
        }
    }
    return this->tree[vertex].move[symbol];
}

int AC::get_final_suffix_link(int vertex) {
    if(this->tree[vertex].suffix_final_link == -1){
        int u = get_suffix_link(vertex);
        if (u == 0){
            this->tree[vertex].suffix_final_link = 0;
        }
        else{
            if(this->tree[u].isFinal)
                this->tree[vertex].suffix_final_link = u;
            else
                this->tree[vertex].suffix_final_link = get_final_suffix_link(u);
        }
    }
    return this->tree[vertex].suffix_final_link;
}

void AC::check(int vertex, int i) {
    for(int u = vertex; u != 0; u = get_final_suffix_link(u)){
        if(this->tree[u].isFinal){
            std::cout << i - this->pattern[this->tree[u].pattern_number].length() + 1 << " " << this->pattern[this->tree[u].pattern_number] << std::endl;
        }
    }
}
