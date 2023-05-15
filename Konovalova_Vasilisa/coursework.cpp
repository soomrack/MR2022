//matrix - исходная матрица m на m.
//height, width - размеры исходной матрицы
//u, v - массивы размеров height и width соответственно, при помощи которых будут
//"эмулироваться" операции модификации строк и столбцов. Элемент (i, j) модифицированной
//матрицы вычисляется как matrix[i][j] - u[i] - v[j].
//markIndices - массив размера width, хранящий информацию о текущем максимальном
//независимом множестве нулевых элементов.
#include <vector>
#include <limits>
using namespace std;

typedef pair<int, int> PInt;
typedef vector<int> VInt;
typedef vector<VInt> VVInt;
typedef vector<PInt> VPInt;

const int inf = numeric_limits<int>::max();

VPInt hungarian(const VVInt &matrix) {

// Размеры матрицы
int height = matrix.size(), width = matrix[0].size();

// Значения, вычитаемые из строк (u) и столбцов (v)
VInt u(height, 0), v(width, 0);

// Индекс помеченной клетки в каждом столбце
VInt markIndices(width, -1);

// Будем добавлять строки матрицы одну за другой
for(int i = 0; i < height; i++) {
VInt links(width, -1);//Массив ссылок links[] из width элементов. Для построения цепочек, начинающихся в посещенных отмеченных элементах.
VInt mins(width, inf);//массив значений mins[] из width элементов
VInt visited(width, 0); //посещенные столбцы

// Разрешение столкновений (создание "чередующейся цепочки" из нулевых элементов)
int markedI = i, markedJ = -1, j;
while(markedI != -1) {
// Обновим информацию о минимумах в посещенных строках непосещенных столбцов
j = -1;
for(int j1 = 0; j1 < width; j1++)
if(!visited[j1]) {
if(matrix[markedI][j1] - u[markedI] - v[j1] < mins[j1]) {
mins[j1] = matrix[markedI][j1] - u[markedI] - v[j1];
links[j1] = markedJ;
}
if(j==-1 || mins[j1] < mins[j])
j = j1;
}

// Ищем элемент с индексами с индексами (markIndices[links[j]], j)
// Произведем манипуляции со строками и столбцами так, чтобы он обнулился
int delta = mins[j];
for(int j1 = 0; j1 < width; j1++)
if(visited[j1]) {
u[markIndices[j1]] += delta;
v[j1] -= delta;
} else {
mins[j1] -= delta;
}
u[i] += delta;

// Если столкновение не разрешено - перейдем к следующей итерации
visited[j] = 1;
markedJ = j;
markedI = markIndices[j];
}

// Пройдем по найденной чередующейся цепочке клеток, снимем отметки с
// отмеченных клеток и поставим отметки на неотмеченные
for(; links[j] != -1; j = links[j])
markIndices[j] = markIndices[links[j]];
markIndices[j] = i;
}

VPInt result;
for(int j = 0; j < width; j++)
if(markIndices[j] != -1)
result.push_back(PInt(markIndices[j], j));
return result;
}
