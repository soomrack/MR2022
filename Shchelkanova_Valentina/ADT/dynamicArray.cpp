#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;


class TwoDimArray {
private:
    int** data;
    int width;
    int height;
public:
    TwoDimArray(int row, int col) { // Конструктор для создания массива
        width = col;
        height = row;
        data = new int*[height];
        for (int idx = 0; idx < height; idx++) {
            data[idx] = new int[width];
        }
    }

    void randFill() { // Заполнение значениями от 0 до 99
        srand(time(NULL));
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                data[row][col] = rand() % 100;
            }
        }
    }

    void printArray() { // Вывод массива на экран
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                std::cout << data[row][col] << ' ';
            }
            std::cout << std::endl;
        }
    }

    void addElement(int row, int col, int value) { // Добавление элемента по индексу
        data[row][col] = value;
    }

    void deleteElement(int row, int col) { // Удаление элемента по индексу
        data[row][col] = 0;
    }

    int elementsNumber() { // Возврат числа элементов массива
        return width * height;
    }

    void deleteArray() { // Удаление всего массива
        for (int i = 0; i < height; i++) {
            delete [] data[i];
        }
        delete [] data;
    }
};

int main() {
    TwoDimArray arr(5, 5);
    arr.randFill();
    arr.printArray();
    cout << " \n";
    arr.addElement(4, 0, 99);
    arr.printArray();
    cout << " \n";
    arr.deleteElement(2, 3);
    arr.printArray();
    cout << " \n";
    std::cout << "Number of elements: " << arr.elementsNumber() << std::endl;
    arr.deleteArray();
    return 0;
}