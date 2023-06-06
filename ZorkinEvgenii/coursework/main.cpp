
/// Реализация дерева Фенвика

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int N = 10;
int n;
int a[N];  //массив
int f[N];  //дерево Фенвика

// Функция нахождения суммы элементов от начала до элемента => на промежутке [0:x]
// Реализация формулы F(x) = x and (x+1) => (& - все 0 кроме 1&1=1)
int getSumTo(int x) {
    int result = 0;

    for (; x >= 0; x = (x & (x + 1)) - 1) {
        result += f[x];
    }

    return result;
}

// Функция обновления значения элемента массива
// H(x) = x or (x+1) => (| - все 1 кроме 0|0=0)
//увеличение a[idx] на delta (обновление ячейки массива)
void update(int idx, int delta) {
    a[idx] += delta;

    for (; idx < n; idx |= idx + 1) {
        f[idx] += delta;
    }
}

// Функция нахождения суммы элементов на промежутке [l:r]
int getSumFromTo(int l, int r) {
    if (l) {
        return getSumTo(r) - getSumTo(l - 1);
    } else {
        return getSumTo(r);
    }
}

// Функция вывода дерева (массива) Фенвика
void print_fenv() {
    for (auto& el: f) {
        cout << el << " ";
    }
    cout << "\n";
}


int main() {

    /// ^^^^ ввод массива и заполнение дерева Фенвика состоят из 2 блоков
    cout << "Enter the number of elements in the array => ";
    cin >> n;                            // ввод пользователем количества элементов в новом массиве

    for (int i = 0; i < n; i++) {
        int t;
        cout << "Enter an element in an array => ";
        cin >> t;                        // ввод пользователем по порядку каждого элемента нового массива
        update(i, t);
    }


    /// Обработка запросов для удовстоверенности работоспособности кода

    cout << "\nBuilding a Fenwick Tree => " << endl;
    print_fenv(); // вывыод дерева Фенвика из заданного массива

    cout << "\nSumma from 0 and up to #2 elemenents => " << getSumTo(2) << endl; // проверка функции суммы от 0 до х

    cout << "\nSumma from #2 and up to #4 elements => " << getSumFromTo(2,4) << endl;


    cout << "\nBuilding a Fenwick Tree before changes => " << endl;
    print_fenv(); // вывывод дерева Фенвика ДО зменения
    cout << "\nUpdate elements #0 => delta (-6) \n" << endl;
    update(0,-6);
    cout << "\nBuilding a Fenwick Tree after changes => " << endl;
    print_fenv(); // вывывод дерева Фенвика ПОСЛЕ зменения

}