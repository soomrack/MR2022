//
// Created by vihmavari on 30.03.2023.
//

#ifndef MY_VECTOR_CHAT_GPT_VECTOR_H
#define MY_VECTOR_CHAT_GPT_VECTOR_H

#include <iostream>
using namespace std;

class gptArray {
private:
    int size;       // текущий размер массива
    int capacity;   // максимальная вместимость массива
    int* arr;       // указатель на начало массива

public:
    // Конструктор, создающий массив с начальной вместимостью 1 элемент
    gptArray() {
        size = 0;
        capacity = 1;
        arr = new int[capacity];    // выделяем память под 1 элемент
    }

    // Метод для добавления элемента в массив
    void push(int element) {
        // Если текущий размер массива равен его максимальной вместимости, то нужно расширить массив
        if (size == capacity) {
            // Выделяем новую память с увеличенной в 2 раза вместимостью
            int* new_arr = new int[2 * capacity];
            // Копируем все элементы из старого массива в новый
            for (int i = 0; i < capacity; i++) {
                new_arr[i] = arr[i];
            }
            // Удаляем старый массив из памяти
            delete[] arr;
            // Переназначаем указатель на начало нового массива
            arr = new_arr;
            // Обновляем значение максимальной вместимости
            capacity *= 2;
        }
        // Добавляем элемент в конец массива
        arr[size] = element;
        // Обновляем текущий размер массива
        size++;
    }
};


#endif //MY_VECTOR_CHAT_GPT_VECTOR_H
