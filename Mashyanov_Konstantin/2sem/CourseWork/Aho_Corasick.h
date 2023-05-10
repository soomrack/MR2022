#ifndef AHO_CORASICK_AHO_CORASICK_H  
#define AHO_CORASICK_AHO_CORASICK_H

#include <string>   
#include "vector"   
#include <map>      

using namespace std;    

typedef struct{     
    map<char, int> next_vertex;     // словарь, связывающий символ ребра с номером следующей вершины в дереве
    int pattern_number;     // номер строки-образца в дереве
    int suffix_link;        // суффиксная ссылка 
    map<char, int> move;    // словарь, связывающий символ ребра с номером следующей вершины в дереве для строки-образца
    int suffix_final_link;  // суффиксная ссылка на финальную вершину 
    int parent;     // номер родительской вершины
    char symbol;    // символ на ребре, соединяющем текущую вершину с родительской
    bool is_final;   // является ли вершина финальной
} tree_vertex;  

class AC{    
public:
    AC();   
    ~AC()= default;  
    void add_string(const string &str); // метод добавления строки-образца в дерево
    void find(const string &str);   // метод поиска всех строк-образцов в тексте
private:
    vector <tree_vertex> tree;  // вектор вершин дерева
    vector <string> pattern;    // вектор строк-образцов

    static tree_vertex make_vertex(int parent, char symbol);   // статический метод создания вершины дерева
    int get_suffix_link(int vertex);  // метод получения суффиксной ссылки для вершины дерева
    int get_move(int vertex, char character);     // метод получения следующей вершины в дереве по символу на ребре
    int get_final_suffix_link(int vertex);     // метод получения суффикcальной ссылки для вершины
    void check(int vertex, int i);  //  метод проверки суффиксальных ссылок для вершины
};

#endif //AHO_CORASICK_AHO_CORASICK_H
