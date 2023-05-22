#include <iostream>
#include <stack> // стек
#include <string>
#include <limits>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    short int n;
    int mas[7][7];
    string input[7];
    do {
        cout << "Введите количество вершин: ";
        cin >> n;
    } while ((n < 2) || (n > 7));
    cout << "Введите списки смежности вершин\n";
    cout << "Замечания:\n";
    cout << "2) По концу вводу списка нажимается Enter\n";
    cout << "3) Список задаётся в порядке возрастания номера смежной вершины\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < n; i++) {
        cout << "Для " << i + 1 << " вершины:" << endl;
        getline(cin, input[i]);
        for (int j = 0; j < input[i].length(); j++) {
            if (input[i][j] == ' ') {
                input[i].erase(j, 1);
                j--;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mas[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < input[i].length(); j++) {
            mas[i][static_cast<int>(input[i][j]) - 48 - 1] = 1;
        }
    }

    //начинаем обход графа в глубину, используя стек
    stack <int> Stack;
    int nodes[7]; // вершины графа
    for (int i = 0; i < n; i++) nodes[i] = 0; // исходно все вершины равны 0
    Stack.push(0); // помещаем в очередь первую вершину
    while (!Stack.empty())
    { // пока стек не пуст
        int node = Stack.top(); // извлекаем вершину
        Stack.pop();
        if (nodes[node] == 2) continue;
        nodes[node] = 2; // отмечаем ее как посещенную
        for (int j = 0; j < 0; j++)
        { // проверяем для нее все смежные вершины
            if (mas[node][j] == 1 && nodes[j] != 2)
            { // если вершина смежная и не обнаружена
                Stack.push(j); // добавляем ее в cтек
                nodes[j] = 1; // отмечаем вершину как обнаруженную
            }
        }
        cout << node + 1; // выводим номер вершины
    }
    return 0;
}