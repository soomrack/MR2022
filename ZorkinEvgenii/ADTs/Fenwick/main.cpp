#include <iostream>
using namespace std;

const int N = 100; // Максимальное количество элементов в исходном массиве
int fenwick[N-1];

// Функция обновления значения элемента массива
// Иными словами увеличить элемент а[i] на d - delta
// H(x) = x or (x+1) => (| - все 1 кроме 0|0=0)
 void update(int i, int d) {
    while (i <= N) {
        fenwick[i] += d;
        i |= i+1;
    }
}

// Реализация формулы F(x) = x and (x+1) => (& - все 0 кроме 1&1=1)
// Функция нахождения суммы на промежутке [0:x]
 int getSum(int x) {
    int result = 0;
    while (x >= 0) {
        result += fenwick[x];
        x &= x+1;
        x--;
    }
    return result;
}

// Функция расчета суммы диапазона элементов от x до y
int getDiapSum(int x, int y) {
    return getSum(y) - getSum(x-1);
}

int main() {
    // Исходный массив
    int array[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(array)/sizeof(array[0]);
    // Инициализируем дерево Фенвика
    for (int x = 0; x <= n; x++) {
        fenwick[x] = 0;
    }

// Обновляем значение элемента на позиции 1
    update(1, 5);

// Расчитываем сумму диапазона от 0 до 3
    int sum = getSum(3);
    cout << "Out summa from 0 to 3: " << sum << endl;

// Расчитываем сумму диапазона от 2 до 6
    int resultDiapSum = getDiapSum(1, 7);
    cout << "Out diap sum from 2 to 6: " << resultDiapSum << endl;

    return 0;
}




























