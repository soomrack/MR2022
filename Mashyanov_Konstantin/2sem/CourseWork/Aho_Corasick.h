#ifndef AHO_CORASICK_AHO_CORASICK_H
#define AHO_CORASICK_AHO_CORASICK_H

#include <string>
#include "vector"
#include <map>

using namespace std;

typedef struct{
    map<char, int> next_vertex;
    int pattern_number;
    int suffix_link;
    map<char, int> move;
    int suffix_final_link;
    int parent;
    char symbol;
    bool isFinal;
} Tree_Vertex;

class AC{
public:
    void AddString(const string &str);
    AC();
    ~AC()= default;
    void Find(const string &str);
private:
    vector <Tree_Vertex> tree;
    vector <string> pattern;

    static Tree_Vertex MakeVertex(int parent, char symbol);
    int GetSuffixLink(int vertex);
    int GetMove(int vertex, char character);
    int GetFinalSuffixLink(int vertex);
    void Check(int vertex, int i);
};

#endif //AHO_CORASICK_AHO_CORASICK_H
