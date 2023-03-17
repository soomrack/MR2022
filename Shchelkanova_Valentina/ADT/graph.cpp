#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Graph {
private:
    int size;
    vector<vector<int>> adjMatrix;

public:
    Graph(int s) : size(s) {
        adjMatrix = vector<vector<int>>(size, vector<int>(size, 0));
    }

    void addEdge(int from, int to) {
        adjMatrix[from][to] = 1;
        adjMatrix[to][from] = 1;
    }

    void generateRandomEdges(float probability) {
        srand(time(NULL));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                float r = (float) rand() / RAND_MAX;
                if (r < probability) {
                    addEdge(i, j);
                }
            }
        }
    }

    void dfs(int start) {
        vector<bool> visited(size, false);
        dfsHelper(start, visited);
    }

    void dfsHelper(int current, vector<bool> &visited) {
        visited[current] = true;
        cout << current << " ";
        for (int i = 0; i < size; i++) {
            if (adjMatrix[current][i] == 1 && !visited[i]) {
                dfsHelper(i, visited);
            }
        }
    }

    void Matrix_print() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};
int main() {
    int size = 5;
    Graph g(size);
    g.generateRandomEdges(0.5);
    g.dfs(0);
    cout << "\n";
    g.Matrix_print();
    return 0;

}