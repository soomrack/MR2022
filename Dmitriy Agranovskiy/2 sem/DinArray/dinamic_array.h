//
// Created by 79522 on 26.03.2023.
//

#ifndef UNTITLED8_DINAMIC_ARRAY_H
#define UNTITLED8_DINAMIC_ARRAY_H

#endif //UNTITLED8_DINAMIC_ARRAY_H

class DinArray{
    int reserve;
private:
    int real_size;
    int size;
    int *array;  // то же что и array[]
public:
    explicit  DinArray(int);
    void set(int, int);
    void resize(int);
    void push_back(int);
    void pop_back();
    void output();
};
