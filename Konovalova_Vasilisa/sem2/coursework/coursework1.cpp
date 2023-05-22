//matrix - исходная матрица m на m.
//height, width - размеры исходной матрицы
//u, v - массивы размеров height и width соответственно, при помощи которых будут
//"эмулироваться" операции модификации строк и столбцов. Элемент (i, j) модифицированной
//матрицы вычисляется как matrix[i][j] - u[i] - v[j].
//markIndices - массив размера width, хранящий информацию о текущем максимальном
//независимом множестве нулевых элементов.
#include <iostream>
#include <vector>
#include <limits>
#include <stdlib.h>
#include <chrono>
using namespace std;

typedef pair<int, int> PInt;
typedef vector<int> VInt;
typedef vector<VInt> VVInt;
typedef vector<PInt> VPInt;

const int inf = numeric_limits<int>::max();

VPInt hungarian(const VVInt& matrix) {

    // Размеры матрицы
    int height = matrix.size();
    int width = matrix[0].size();

    // Значения, вычитаемые из строк (u) и столбцов (v)
    VInt u(height, 0), v(width, 0);

    // Индекс помеченной клетки в каждом столбце
    VInt markIndices(width, -1);

    // Добавляем строки матрицы одну за другой
    for (int i = 0; i < height; i++) {
        VInt links(width, -1);
        VInt mins(width, inf);
        VInt visited(width, 0);

        // Создание "чередующейся цепочки" из нулевых элементов
        int markedI = i, markedJ = -1, j;
        while (markedI != -1) {
            // Обновим информацию о минимумах в посещенных строках непосещенных столбцов
            // Поместим в j индекс непосещенного столбца с самым маленьким из них
            j = -1;
            for (int j1 = 0; j1 < width; j1++)
                if (!visited[j1]) {
                    if (matrix[markedI][j1] - u[markedI] - v[j1] < mins[j1]) {
                        mins[j1] = matrix[markedI][j1] - u[markedI] - v[j1];
                        links[j1] = markedJ;
                    }
                    if (j == -1 || mins[j1] < mins[j])
                        j = j1;
                }

            //Обнуляем элемент с индексами (markIndices[links[j]], j)
            int delta = mins[j];
            for (int j1 = 0; j1 < width; j1++)
                if (visited[j1]) {
                    u[markIndices[j1]] += delta;
                    v[j1] -= delta;
                }
                else {
                    mins[j1] -= delta;
                }
            u[i] += delta;

            // Переход к следующей итерации
            visited[j] = 1;
            markedJ = j;
            markedI = markIndices[j];
        }

        // Пройдем по найденной чередующейся цепочке клеток, снимем отметки с отмеченных клеток и поставим отметки на неотмеченные
        for (; links[j] != -1; j = links[j])
            markIndices[j] = markIndices[links[j]];
        markIndices[j] = i;
    }

    // Возвращаем результат
    VPInt result;
    for (int j = 0; j < width; j++)
        if (markIndices[j] != -1)
            result.push_back(PInt(markIndices[j], j));
    return result;
}

void hungarian_app(VVInt array, int n, int m)
{
    VPInt Matrix = hungarian(array);
}

int main()
{
    int array[] = { 3, 30, 300, 600, 900, 1500,3000};

    for (int f = 0; f < 7; f++)
    {
        int Size = array[f];
        vector < vector <int> > a(Size, vector <int>(Size));
        VVInt NewMatrix = a;
        for (int i = 0; i < Size; i++)     // Цикл, который идёт по строкам
        {
            for (int j = 0; j < Size; j++) // Цикл, который идёт по элементам
            {
                NewMatrix[i][j] = rand() % 100;; // Заполнение вектора или массива
            }
        }
        auto begin = std::chrono::steady_clock::now();
        hungarian_app(NewMatrix, Size, Size);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        std::cout << "The time: " << elapsed_ms.count() << " ns\n";
    }
    return 0;
}


